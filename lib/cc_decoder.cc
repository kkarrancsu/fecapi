#include <cc_decoder.h>
#include <math.h>
#include <boost/assign/list_of.hpp>
#include <volk_fecapi/volk_fecapi_typedefs.h>
#include <volk_fecapi/volk_fecapi.h>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <fec_decoder.h>
#include <cc_common.h>


generic_decoder_sptr
cc_make_decoder(int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming)
{
    return generic_decoder_sptr(new cc_decoder(framebits, k, rate, polys, start_state, end_state, tailbiting, terminated, truncated, streaming));
}

cc_decoder::cc_decoder (int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming)
    : generic_decoder("cc_decoder"),
      d_framebits(framebits), 
      d_polys(polys), 
      d_k(k), 
      d_rate(rate),
      d_partial_rate(rate),
      d_start_state_nonchaining(start_state), 
      d_start_state_chaining(start_state), 
      d_end_state_nonchaining(end_state), 
      d_tailbiting(tailbiting), 
      d_terminated(terminated), 
      d_truncated(truncated), 
      d_streaming(streaming)
{

    d_vp = new struct v;
    
   

    d_numstates = 1 << (d_k - 1);
  
    d_decision_t_size = d_numstates/8; //packed bit array
  
    
    if(d_tailbiting) {
	d_end_state = &d_end_state_chaining;
	d_veclen = d_framebits + (6 * (d_k - 1));
	if(posix_memalign((void**)&d_managed_in, 16, d_veclen * d_rate * sizeof(COMPUTETYPE))){
	    printf("allocation failed\n");
	    exit(1);
	}
    }
    /*else if(d_trunc_intrinsic) {
	d_end_state = &d_end_state_nonchaining;
	d_veclen = d_framebits + d_k - 1;
	if(posix_memalign((void**)&d_managed_in, 16, d_veclen * d_rate * sizeof(COMPUTETYPE))){
	    printf("allocation failed\n");
	    exit(1);
	}
	int cnt = 0;
	for(int i = 0; i < d_rate; ++i) {
	    if (d_polys[i] != 1) {
		cnt++;
	    }
	}
	d_partial_rate = cnt;
	}*/
    else if(d_truncated) {
	d_end_state = &d_end_state_chaining;
	d_veclen = d_framebits;
    }
    else if(d_terminated) {
	d_end_state = (end_state == -1) ? &d_end_state_chaining : &d_end_state_nonchaining;
	d_veclen = d_framebits + d_k - 1;
    }
	
    //streaming
    else {
	d_end_state = &d_end_state_chaining;
	d_veclen = d_framebits + d_k - 1;
	
    }
  
    if(posix_memalign((void**)&d_vp->metrics, 16, 2 * d_numstates * sizeof(COMPUTETYPE))){
	printf("allocation failed\n");
	exit(1);
    }
  
    d_vp->metrics1.t = d_vp->metrics;
    d_vp->metrics2.t = d_vp->metrics + d_numstates;
    
    
  
    if(posix_memalign((void**)&d_vp->decisions, 16,d_veclen*d_decision_t_size)){
	printf("allocation failed\n");
	exit(1);
    }
  
    if (posix_memalign((void**)&Branchtab, 16, sizeof(COMPUTETYPE) * d_numstates/2*rate)){
	printf("allocation failed\n");
	exit(1);
    }

  
    create_viterbi();

  

    if (d_k-1<8) {
	d_ADDSHIFT = (8-(d_k-1));
	d_SUBSHIFT =  0;
    }
    else if (d_k-1>8) {
	d_ADDSHIFT = 0;
	d_SUBSHIFT =  ((d_k-1)-8);
    }
    else {
	d_ADDSHIFT = 0;
	d_SUBSHIFT = 0;
    }
    
    
    yp_kernel = boost::assign::map_list_of("k=7r=2", volk_fecapi_8u_x4_conv_k7_r2_f2048_8u);
  
    std::string k_ = "k=";
    std::string r_ = "r=";

    std::ostringstream kerneltype;
    kerneltype << k_ << d_k << r_ << d_rate;
  
    d_kernel = yp_kernel[kerneltype.str()];
  
    
}

int cc_decoder::get_output_size() {
    //unpacked bits
    return d_framebits;
}

int cc_decoder::get_input_size() {
    if(d_terminated) {
	return d_rate * (d_framebits + d_k - 1);
    }
    /*else if(d_trunc_intrinsic) {
	int cnt = 0;
	for(int i = 0; i < d_rate; ++i) {
	    if (d_polys[i] != 1) {
		cnt++;
	    }
	}
	return (d_rate * (d_framebits)) + (cnt * (d_k - 1));
	}*/
    else {
	return d_rate * d_framebits;
    }
}

int cc_decoder::get_input_item_size() {
    return 1;
}

int cc_decoder::get_history() {
    if(d_streaming) {
	return d_rate * (d_k - 1);
    }
    else {
	return 0;
    }
}

/*const char* cc_decoder::get_output_conversion() {
    return "unpack";
    }*/

float cc_decoder::get_shift() {
    return 128.0;
}

const char* cc_decoder::get_conversion() {
    return "uchar";
}

void cc_decoder::create_viterbi() {

    int state, i;
    partab_init();
    for(state=0;state < d_numstates/2;state++){
	for (i=0; i<d_rate; i++){
	    Branchtab[i*d_numstates/2+state] = (d_polys[i] < 0) ^ parity((2*state) & abs(d_polys[i])) ? 255 : 0;
	}
    }
    
  

    

    if(d_streaming) {
	//	printf("streaming\n");
	d_start_state = &d_start_state_chaining;
	init_viterbi_unbiased(d_vp);
    }
    else if(d_tailbiting) {
	//	printf("tailbiting\n");
	d_start_state = &d_start_state_nonchaining;
	init_viterbi_unbiased(d_vp);
    }	
    else {
	//	printf("other!\n");
	d_start_state = &d_start_state_nonchaining;
	init_viterbi(d_vp, *d_start_state);      
    }
    
    
    
    return;
    
}

int cc_decoder::parity(int x) {
    x ^= (x >> 16);
    x ^= (x >> 8);
    return parityb(x);
}

int cc_decoder::parityb(unsigned char x) {
    return Partab[x];
}

void cc_decoder::partab_init(void) {
    int i,cnt,ti;
    
    /* Initialize parity lookup table */
    for(i=0;i<256;i++){
	cnt = 0;
	ti = i;
	while(ti){
	    if(ti & 1)
		cnt++;
	    ti >>= 1;
	}
	Partab[i] = cnt & 1;
    }
}


int cc_decoder::init_viterbi(struct v* vp, int starting_state) {
    int i;
    
    if(vp == NULL)
	return -1;
    for(i=0;i<d_numstates;i++) {
	vp->metrics1.t[i] = 63;
    }
    
    vp->old_metrics = vp->metrics1;
    vp->new_metrics = vp->metrics2;
    vp->old_metrics.t[starting_state & (d_numstates-1)] = 0; /* Bias known start state */
    return 0;
}

int cc_decoder::init_viterbi_unbiased(struct v* vp) {
    int i;
    
    if(vp == NULL)
	return -1;
    for(i=0;i<d_numstates;i++)
	vp->metrics1.t[i] = 31;
    
    vp->old_metrics = vp->metrics1;
    vp->new_metrics = vp->metrics2;
    //no bias step
    return 0;
}



int cc_decoder::find_endstate() {
    COMPUTETYPE* met = (d_k%2 == 0)? d_vp->new_metrics.t : d_vp->old_metrics.t; 
    COMPUTETYPE min = met[0];
    int state = 0;
    for(int i = 1; i < d_numstates; ++i) {
	if(met[i] < min) {
	    min = met[i];
	    state = i;
	}
    }
    return state;
}


int cc_decoder::update_viterbi_blk(const COMPUTETYPE* syms, int nbits) {
 
    DECISIONTYPE *d;
    int s,i;
    
    
    d = d_vp->decisions;
    //going to have to use nbits for tailbiting?
    //memset(d,0,d_decision_t_size * (d_framebits+d_k-1));//use volk here?
    memset(d,0,d_decision_t_size * nbits);//use volk here?
    
    
    //d_kernel( d_vp->new_metrics.t, d_vp->old_metrics.t, syms, d, d_framebits, d_k - 1, Branchtab);
    d_kernel( d_vp->new_metrics.t, d_vp->old_metrics.t, syms, d, nbits - (d_k - 1), d_k -1, Branchtab);
    
    return 0;
}

int cc_decoder::chainback_viterbi(DECISIONTYPE* data, unsigned int nbits, unsigned int endstate, unsigned int tailsize) {
    DECISIONTYPE *d;
    
    /* ADDSHIFT and SUBSHIFT make sure that the thing returned is a byte. */
    
    
    
    d = d_vp->decisions;
    /* Make room beyond the end of the encoder register so we can
     * accumulate a full byte of decoded data
     */
    
    endstate = (endstate%d_numstates) << d_ADDSHIFT;
    
    
    /* The store into data[] only needs to be done every 8 bits.
     * But this avoids a conditional branch, and the writes will
     * combine in the cache anyway
     */
    
    d += tailsize * d_decision_t_size ; /* Look past tail */
    int retval;
    int dif = tailsize - (d_k - 1);
    //printf("break, %d, %d\n", dif, (nbits+dif)%d_framebits);
    decision_t dec;
    while(nbits-- > d_framebits - (d_k - 1)){
	int k;
	dec.t = &d[nbits * d_decision_t_size];
	k = (dec.w[(endstate>>d_ADDSHIFT)/32] >> ((endstate>>d_ADDSHIFT)%32)) & 1;
	
	endstate = (endstate >> 1) | (k << (d_k-2+d_ADDSHIFT));
	//data[((nbits+dif)%nbits)>>3] = endstate>>d_SUBSHIFT;
	//printf("%d, %d\n", k, (nbits+dif)%d_framebits);
	data[((nbits+dif)%d_framebits)] = k;
	
	retval = endstate;
    }
    nbits += 1;
    while(nbits-- != 0){
	
	int k;
	
	dec.t = &d[nbits * d_decision_t_size];
	
	k = (dec.w[(endstate>>d_ADDSHIFT)/32] >> ((endstate>>d_ADDSHIFT)%32)) & 1;
	
	endstate = (endstate >> 1) | (k << (d_k-2+d_ADDSHIFT));
	data[((nbits+dif)%d_framebits)] = k;
	
    }
    //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", data[4095],data[4094],data[4093],data[4092],data[4091],data[4090],data[4089],data[4088]);
    return retval >> d_ADDSHIFT;
}


void cc_decoder::set_framebits(int framebits){
    d_framebits = framebits;
    if(d_tailbiting) {
        d_veclen = d_framebits + (6 * (d_k - 1));
    } else if(d_truncated) {
        d_veclen = d_framebits;
    } else {
        d_veclen = d_framebits + d_k - 1;
    }
}

void cc_decoder::generic_work(void *inBuffer, void *outBuffer)   
{

  
    const COMPUTETYPE *in = (const COMPUTETYPE *) inBuffer;
    DECISIONTYPE *out = (DECISIONTYPE *) outBuffer;
    	
    if(d_tailbiting) {
	memcpy(d_managed_in, in, d_framebits * d_rate * sizeof(COMPUTETYPE));
	memcpy(d_managed_in + d_framebits * d_rate * sizeof(COMPUTETYPE), in, (d_veclen - d_framebits) * d_rate * sizeof(COMPUTETYPE));
	/*for(int i = 0; i < d_veclen * d_rate; ++i) {
	    printf("%u...%d\n", d_managed_in[i], i);
	    }*/
	update_viterbi_blk(d_managed_in, d_veclen);
	d_end_state_chaining = find_endstate();
	chainback_viterbi(&out[0], d_framebits, *d_end_state, d_veclen - d_framebits);
	init_viterbi_unbiased(d_vp);
    }

    /*else if(d_trunc_intrinsic) {
	memcpy(d_managed_in, in, d_framebits * d_rate * sizeof(COMPUTETYPE));
	for(int i = 0; i < (d_k - 1); ++i) {
	    int cnt = 0; 
	    for(int j = 0; j < d_rate; ++j) {
		if(d_polys[j] != 1) {

		    d_managed_in[(d_framebits * d_rate) + (i * d_rate) + j] =
			in[(d_framebits * d_rate) + (i * d_partial_rate) + cnt++];
		}
		else {

		    d_managed_in[(d_framebits * d_rate) + (i * d_rate) + j] =
			(((*d_end_state) >> (d_k - 2 - i)) & 1) * ((1 << (sizeof(COMPUTETYPE) * 8)) - 1);
		}
	    }
	}
	update_viterbi_blk(d_managed_in, d_veclen);
	d_end_state_chaining = find_endstate();
	chainback_viterbi(&out[0], d_framebits, *d_end_state, d_veclen - d_framebits);
	init_viterbi(d_vp, *d_start_state);
	}*/
    
    else if(d_truncated) {
	update_viterbi_blk(&in[0], d_veclen);
	d_end_state_chaining = find_endstate();
	//printf("...end %d\n", d_end_state_chaining);
	for(int i = 0; i < d_k -1; ++i) {
	    out[d_veclen - 1 - i] = ((*d_end_state) >> i) & 1;
	}
	d_start_state_chaining = chainback_viterbi(&out[0], d_framebits - (d_k - 1), *d_end_state, d_k - 1);
	init_viterbi(d_vp, *d_start_state);
	/*for(int i = d_framebits - 25; i < d_framebits; ++i) {
	    //for(int i = 0; i < 25; ++i) {
	    printf("%u... : %u\n", out[i], i);
	    }*/
    
    }
    //terminated or streaming
    else {
     
	update_viterbi_blk(&in[0], d_veclen);
	d_end_state_chaining = find_endstate();
	//printf("es: %d\n", d_end_state_chaining);
	d_start_state_chaining = chainback_viterbi(&out[0], d_framebits, *d_end_state, d_veclen - d_framebits);
    
	init_viterbi(d_vp, *d_start_state);
	/*for(int i = d_framebits * d_rate - 25; i < d_framebits * d_rate; ++i) {
	    printf("%u... : %u\n", in[i], i);
	    }*/
    }
}    
 

cc_decoder::~cc_decoder()
{
    free(d_vp->decisions);
    free(Branchtab);
    free(d_vp->metrics);
}



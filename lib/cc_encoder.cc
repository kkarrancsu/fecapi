#include <cc_encoder.h>
#include <math.h>
#include <boost/assign/list_of.hpp>
#include <volk_typedefs.h>
#include <volk.h>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <fec_encoder.h>
#include <cc_common.h>


generic_encoder_sptr
cc_make_encoder(int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming)
{
    return generic_encoder_sptr(new cc_encoder(framebits, k, rate, polys, start_state, end_state, tailbiting, terminated, truncated, streaming));
}

cc_encoder::cc_encoder (int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming)
    : d_framebits(framebits), d_polys(polys), d_rate(rate), d_k(k),
      d_start_state(start_state), d_tailbiting(tailbiting), d_terminated(terminated), d_truncated(truncated), d_streaming(streaming)
{
    partab_init();
     
}

int cc_encoder::get_output_size() {
 
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

int cc_encoder::get_input_size() {
    return d_framebits;
}




int cc_encoder::parity(int x) {
    x ^= (x >> 16);
    x ^= (x >> 8);
    return parityb(x);
}

int cc_encoder::parityb(unsigned char x) {
    return Partab[x];
}

void cc_encoder::partab_init(void) {
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






void cc_encoder::generic_work(void *inBuffer, void *outBuffer)   
{

  
    const unsigned char *in = (const unsigned char *) inBuffer;
    float *out = (float *) outBuffer;
    
    int my_state = d_start_state;
    //printf("ms: %d\n", my_state);
    
    if (d_tailbiting) {
	for(int i = 0; i < d_k - 1; ++i) {
	    my_state = (my_state << 1) | (in[d_framebits - (d_k - 1)  + i] & 1);
	    
	}
    }
    //printf("start... %d\n", my_state & ((1 << (d_k - 1)) - 1));
    
    for(int i = 0; i < d_framebits; ++i) {
	my_state = (my_state << 1) | (in[i] & 1);
	for(int j = 0; j < d_rate; ++j) {
	    out[i * d_rate + j] = parity(my_state & d_polys[j]) == 0 ? -1.0 : 1.0;
	}
    }
    
    
    if (d_terminated) {
	for(int i = 0; i < d_k - 1; ++i) {
	    my_state = (my_state << 1) | ((d_start_state >> d_k - 2 - i) & 1);
	    for(int j = 0; j < d_rate; ++j) {
		out[(i + d_framebits) * d_rate + j] = parity(my_state & d_polys[j]) == 0 ? -1.0 : 1.0;
	    }
	}
    }

    /*if (d_trunc_intrinsic) {
	for(int i = 0; i < d_k - 1; ++i) {
	    my_state = (my_state << 1) | ((d_start_state >> d_k - 2 - i) & 1);
	    int cnt = 0;
	    for(int j = 0; j < d_rate; ++j) {
		if(d_polys[j] != 1) {
		    out[(i + d_framebits) * d_rate + cnt] = parity(my_state & d_polys[j]) == 0 ? -1.0 : 1.0;
		    cnt++;
		}
	    }
	}
	}*/
    
    if(d_truncated) {
	//printf("end... %d\n", my_state & ((1 << (d_k - 1)) - 1));
	my_state = d_start_state;
    }
    
    d_start_state = my_state;
    //d_start_state = my_state & (1 << d_k -1) - 1;
    //printf("ms: %d\n", d_start_state);
    
    /*for(int i = d_framebits * d_rate - 25; i < d_framebits * d_rate; ++i) {
	//for(int i = 0; i < 25; ++i) {
	printf("...%f : %u\n", out[i], i);
	}*/
    
}    


cc_encoder::~cc_encoder()
{
 
}



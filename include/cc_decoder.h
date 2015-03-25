#ifndef INCLUDED_CC_DECODER_H
#define INCLUDED_CC_DECODER_H


#include <map>
#include <string>
#include <fec_decoder.h>
#include <cc_common.h>



typedef void(*conv_kernel)(unsigned char  *Y, unsigned char  *X, const unsigned char  *syms, unsigned char  *dec, unsigned int framebits, unsigned int excess, unsigned char  *Branchtab);




FEC_API generic_decoder_sptr
cc_make_decoder (int framebits, int k, int rate, std::vector<int> polys, int start_state = 0, int end_state = -1, bool tailbiting = false, bool terminated = false, bool truncated = false, bool streaming = false);


class FEC_API cc_decoder : public generic_decoder
{
    
    
    //befriend the global, swigged make function
    friend generic_decoder_sptr
	cc_make_decoder (int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming);

    //plug into the generic fec api
    int get_output_size();
    int get_input_size();
    int get_history();
    float get_shift();
    int get_input_item_size();
    const char* get_conversion();
    //const char* get_output_conversion();
    //everything else...
    void create_viterbi();
    int init_viterbi(struct v* vp, int starting_state);
    int init_viterbi_unbiased(struct v* vp);
    int update_viterbi_blk(const COMPUTETYPE* syms, int nbits);
    int chainback_viterbi(unsigned char* data, unsigned int nbits, unsigned int endstate, unsigned int tailsize);
    int find_endstate();
    int tester[12];

    COMPUTETYPE *Branchtab;
    unsigned char Partab[256];
  
  
    bool d_tailbiting;
    bool d_terminated;
    bool d_truncated;
    bool d_streaming;
    int d_ADDSHIFT;
    int d_SUBSHIFT;
    conv_kernel d_kernel;
    unsigned int d_framebits;
    unsigned int d_k;
    unsigned int d_rate;
    unsigned int d_partial_rate;
    std::vector<int> d_polys;
    struct v* d_vp;
    COMPUTETYPE* d_managed_in;
    int d_numstates;
    int d_decision_t_size;
    int *d_start_state;
    int d_start_state_chaining;
    int d_start_state_nonchaining;
    int *d_end_state;
    int d_end_state_chaining;
    int d_end_state_nonchaining;
    unsigned int d_veclen;
    int parity(int x);
    int parityb(unsigned char x);
    void partab_init(void);
    std::map<std::string, conv_kernel> yp_kernel;


 public:
    void set_framebits(int framebits);
    void generic_work(void *inBuffer, void *outbuffer);
    cc_decoder (int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming);
    ~cc_decoder ();
    
    
    
};

#endif /* INCLUDED_CC_DECODER_H */

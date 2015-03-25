#ifndef INCLUDED_CC_ENCODER_H
#define INCLUDED_CC_ENCODER_H


#include <map>
#include <string>
#include <fec_encoder.h>
#include <cc_common.h>


FEC_API generic_encoder_sptr
cc_make_encoder (int framebits, int k, int rate, std::vector<int> polys, int start_state = 0, int end_state = 0, bool tailbiting = false, bool terminated = false, bool truncated = false, bool streaming = true);


class FEC_API cc_encoder : public generic_encoder
{
    
    
    //befriend the global, swigged make function
    friend generic_encoder_sptr
	cc_make_encoder (int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming);

    //private ctor
    cc_encoder (int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming);

    //plug into the generic fec api
    void generic_work(void *inBuffer, void *outbuffer);
    int get_output_size();
    int get_input_size();


    //everything else...


    unsigned char Partab[256];
  
  
    
    unsigned int d_framebits;
    unsigned int d_rate;
    unsigned int d_k;
    std::vector<int> d_polys;
    struct v* d_vp;
    int d_numstates;
    int d_decision_t_size;
    int d_start_state;
    bool d_tailbiting;
    bool d_terminated;
    bool d_truncated;
    bool d_streaming;
    int parity(int x);
    int parityb(unsigned char x);
    void partab_init(void);



 public:
    ~cc_encoder ();
    
    
    
};

#endif /* INCLUDED_CC_ENCODER_H */

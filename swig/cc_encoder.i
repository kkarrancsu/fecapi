/* -*- c++ -*- */

%{
#include "cc_encoder.h"
%}





generic_encoder_sptr cc_make_encoder(int framebits, int k, int rate, std::vector<int> polys, int start_state = 0, int end_state = 0, bool tailbiting = false, bool terminated = false, bool truncated = false, bool streaming = false);

class cc_encoder {
 public:
    ~cc_encoder();
 private:
    cc_encoder(int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming);
};

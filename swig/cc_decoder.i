/* -*- c++ -*- */

%{
#include "cc_decoder.h"
%}





generic_decoder_sptr cc_make_decoder(int framebits, int k, int rate, std::vector<int> polys, int start_state = 0, int end_state = -1, bool tailbiting = false, bool terminated = false, bool truncated = false, bool streaming = false);

class cc_decoder {
 public:
    ~cc_decoder();
 private:
    cc_decoder(int framebits, int k, int rate, std::vector<int> polys, int start_state, int end_state, bool tailbiting, bool terminated, bool truncated, bool streaming);
};

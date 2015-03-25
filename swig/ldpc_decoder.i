/* -*- c++ -*- */

%{
#include "ldpc_decoder.h"
%}





generic_decoder_sptr ldpc_make_decoder(std::string alist_file, float sigma=0.5, int max_iterations=50);

class ldpc_decoder {
 public:
    ~ldpc_decoder();
 private:
    ldpc_decoder(std::string alist_file, float sigma, int max_iterations);
};

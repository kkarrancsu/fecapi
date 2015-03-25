/* -*- c++ -*- */

%{
#include "ldpc_encoder.h"
%}





generic_encoder_sptr ldpc_make_encoder(std::string alist_file );

class ldpc_encoder {
 public:
    ~ldpc_encoder();
 private:
    ldpc_encoder(std::string alist_file);
};

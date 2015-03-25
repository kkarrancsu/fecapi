/* -*- c++ -*- */

%{
#include "fec_gaussnoise_ff.h"
%}


GR_SWIG_BLOCK_MAGIC(fec,gaussnoise_ff);

fec_gaussnoise_ff_sptr fec_make_gaussnoise_ff(float EsNo);
		
class fec_gaussnoise_ff : public gr::sync_block
{
 private:
    fec_gaussoise_ff(float);
    
};

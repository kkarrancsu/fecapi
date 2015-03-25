/* -*- c++ -*- */

%{
#include "fec_puncture_ff.h"
%}


GR_SWIG_BLOCK_MAGIC(fec,puncture_ff);

fec_puncture_ff_sptr fec_make_puncture_ff(int delay, int puncpat, int puncholes, int puncsize);
		
class fec_puncture_ff : public gr::block
{
 private:
    fec_puncture_ff(int, int, int, int);
    
};

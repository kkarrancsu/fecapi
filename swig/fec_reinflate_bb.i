/* -*- c++ -*- */

%{
#include "fec_reinflate_bb.h"
%}


GR_SWIG_BLOCK_MAGIC(fec,reinflate_bb);

fec_reinflate_bb_sptr fec_make_reinflate_bb(int delay, int puncpat, int puncholes, int puncsize);
		
class fec_reinflate_bb : public gr::block
{
 private:
    fec_reinflate_bb(int, int, int, int);
    
};

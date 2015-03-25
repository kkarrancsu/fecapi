/* -*- c++ -*- */

%{
#include "tpc_decoder.h"
%}





generic_decoder_sptr tpc_make_decoder( std::vector<int> row_polys, std::vector<int> col_polys, int krow, int kcol, int bval, int qval, int max_iter, int decoder_type );

class tpc_decoder {
 public:
    ~tpc_decoder();
 private:
    tpc_decoder( std::vector<int> row_polys, std::vector<int> col_polys, int krow, int kcol, int bval, int qval, int max_iter, int decoder_type );
};

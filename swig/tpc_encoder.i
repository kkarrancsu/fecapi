/* -*- c++ -*- */

%{
#include "tpc_encoder.h"
%}





generic_encoder_sptr tpc_make_encoder( std::vector<int> row_polys, std::vector<int> col_polys, int krow, int kcol, int bval, int qval );

class tpc_encoder {
 public:
    ~tpc_encoder();
 private:
    tpc_encoder( std::vector<int> row_polys, std::vector<int> col_polys, int krow, int kcol, int bval, int qval );
};

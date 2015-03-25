/* -*- c++ -*- */

#define FEC_API

%include "runtime_swig.i"			// the common stuff
%include "std_vector.i"

namespace std {
  %template(IntVector) vector<int>;
  %template(ULLVector) vector<unsigned long long>;
  %template(UIntVector) vector<unsigned int>;
}



// the .i files
%include <fec_random_gen_b.i>
%include <fec_encoder.i>
%include <fec_gaussnoise_ff.i>
%include <fec_decoder.i>
%include <fec_ber_bb.i>
%include <fec_interleave.i>
%include <fec_deinterleave.i>
%include <cc_decoder.i>
%include <cc_encoder.i>
%include <fec_corr_bb.i>
%include <fec_reinflate_bb.i>
%include <fec_puncture_ff.i>
#if SWIGGUILE
%scheme %{
(load-extension-global "libguile-gnuradio-howto_swig" "scm_init_gnuradio_howto_swig_module")
%}

%goops %{
(use-modules (gnuradio gnuradio_core_runtime))
%}
#endif

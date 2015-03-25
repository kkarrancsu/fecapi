#ifndef INCLUDED_FEC_PUNCTURE_FF_H
#define INCLUDED_FEC_PUNCTURE_FF_H

#include <gnuradio/block.h>
#include <fec_api.h>

class fec_puncture_ff;
typedef boost::shared_ptr<fec_puncture_ff> fec_puncture_ff_sptr;





FEC_API fec_puncture_ff_sptr
fec_make_puncture_ff (int delay, int puncpat, int puncholes, int puncsize);


class FEC_API fec_puncture_ff : public gr::block
{
  
  int d_delay;
  int d_puncholes;
  int d_puncsize;
  int d_puncpat;
  friend fec_puncture_ff_sptr
    fec_make_puncture_ff (int delay, int puncpat, int puncholes, int puncsize);
  
  fec_puncture_ff (int delay, int puncpat, int puncholes, int puncsize);
  
  //void catch_msg(pmt::pmt_t msg);
  
 public:
  ~fec_puncture_ff ();
  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
  int fixed_rate_ninput_to_noutput(int ninput);
  int fixed_rate_noutput_to_ninput(int noutput);
  void forecast(int noutput_items,
		gr_vector_int& ninput_items_required);
};

#endif /* INCLUDED_FEC_PUNCTURE_FF_H */

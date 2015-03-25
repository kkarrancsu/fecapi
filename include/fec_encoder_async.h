#ifndef INCLUDED_FEC_ENCODER_ASYNC_H
#define INCLUDED_FEC_ENCODER_ASYNC_H

#include <gnuradio/block.h>
#include <fec_api.h>
#include <boost/shared_ptr.hpp>
#include <fec_encoder.h>


class fec_encoder_async;
typedef boost::shared_ptr<fec_encoder_async> fec_encoder_async_sptr;
FEC_API fec_encoder_async_sptr fec_make_encoder_async(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);

//FEC_API int fec_get_encoder_output_size(generic_encoder_sptr my_encoder);
//FEC_API int fec_get_encoder_input_size(generic_encoder_sptr my_encoder);

class FEC_API fec_encoder_async : public gr::block
{
  friend fec_encoder_async_sptr fec_make_encoder_async(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
  fec_encoder_async(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
  generic_encoder_sptr d_encoder;
  size_t d_input_item_size;
  size_t d_output_item_size;

 public:
  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
 private:
  void encode(pmt::pmt_t msg);

};



    
#endif /* INCLUDED_FEC_ENCODER_H */

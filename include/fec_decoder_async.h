#ifndef INCLUDED_FEC_DECODER_ASYNC_H
#define INCLUDED_FEC_DECODER_ASYNC_H

#include <gnuradio/block.h>
#include <fec_api.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/format.hpp>
#include <fec_decoder.h>

class fec_decoder_async;
typedef boost::shared_ptr<fec_decoder_async> fec_decoder_async_sptr;
FEC_API fec_decoder_async_sptr fec_make_decoder_async(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);


class FEC_API fec_decoder_async : public gr::block
{
  friend fec_decoder_async_sptr fec_make_decoder_async(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
  fec_decoder_async(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
  generic_decoder_sptr d_decoder;
  size_t d_input_item_size;
  size_t d_output_item_size;

 public:
  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
 private:
   void decode(pmt::pmt_t msg);
};



    
#endif /* INCLUDED_FEC_DECODER_H */

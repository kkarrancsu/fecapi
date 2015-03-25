#ifndef INCLUDED_FEC_ENCODER_H
#define INCLUDED_FEC_ENCODER_H

#include <gnuradio/block.h>
#include <fec_api.h>
#include <boost/shared_ptr.hpp>



class FEC_API generic_encoder{
 protected:
    friend class fec_encoder;
    friend class fec_encoder_async;
    virtual void generic_work(void *inBuffer, void *outBuffer) = 0;
 public:
    virtual int get_input_size() = 0;
    virtual int get_output_size() = 0;
    virtual ~generic_encoder();
 
    
};

typedef boost::shared_ptr<generic_encoder> generic_encoder_sptr;

class fec_encoder;
typedef boost::shared_ptr<fec_encoder> fec_encoder_sptr;

FEC_API fec_encoder_sptr fec_make_encoder(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
FEC_API int fec_get_encoder_output_size(generic_encoder_sptr my_encoder);
FEC_API int fec_get_encoder_input_size(generic_encoder_sptr my_encoder);


class FEC_API fec_encoder : public gr::block
{
  friend fec_encoder_sptr fec_make_encoder(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
  fec_encoder(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
  generic_encoder_sptr d_encoder;
  size_t d_input_item_size;
  size_t d_output_item_size;

 public:
  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
  int fixed_rate_ninput_to_noutput(int ninput);
  int fixed_rate_noutput_to_ninput(int noutput);
  void forecast(int noutput_items,
		gr_vector_int& ninput_items_required);
};



    
#endif /* INCLUDED_FEC_ENCODER_H */

#ifndef INCLUDED_FEC_DECODER_H
#define INCLUDED_FEC_DECODER_H

#include <gnuradio/block.h>
#include <fec_api.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/format.hpp>


class FEC_API generic_decoder {
 protected:
    friend class fec_decoder;
    friend class fec_decoder_async;
    virtual void generic_work(void *inBuffer, void *outBuffer) = 0;
    static int base_unique_id;
    int my_id;
    int unique_id();
    std::string d_name;
    std::string alias(){ return (boost::format("%s%d")%d_name%unique_id()).str(); }

 public:
    virtual int get_input_size() = 0;
    virtual int get_output_size() = 0;
    virtual int get_history();
    virtual float get_shift();
    virtual const char* get_conversion();
    virtual int get_input_item_size();
    virtual int get_output_item_size();
    virtual const char* get_output_conversion();
    virtual ~generic_decoder();
    void forecast(int noutput_items,
		  gr_vector_int& ninput_items_required);
    generic_decoder(std::string name);
    
};

typedef boost::shared_ptr<generic_decoder> generic_decoder_sptr;
typedef boost::shared_array<unsigned char> buf_sptr;
class fec_decoder;
typedef boost::shared_ptr<fec_decoder> fec_decoder_sptr;

FEC_API fec_decoder_sptr fec_make_decoder(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
FEC_API int fec_get_decoder_output_size(generic_decoder_sptr my_decoder);
FEC_API int fec_get_decoder_input_size(generic_decoder_sptr my_decoder);
FEC_API float fec_get_shift(generic_decoder_sptr my_decoder);
FEC_API int fec_get_history(generic_decoder_sptr my_decoder);
FEC_API int fec_get_decoder_output_item_size(generic_decoder_sptr my_decoder);
FEC_API int fec_get_decoder_input_item_size(generic_decoder_sptr my_decoder);
FEC_API const char* fec_get_conversion(generic_decoder_sptr my_decoder);
FEC_API const char* fec_get_output_conversion(generic_decoder_sptr my_decoder);



class FEC_API fec_decoder : public gr::block
{
  friend fec_decoder_sptr fec_make_decoder(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
  fec_decoder(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
  generic_decoder_sptr d_decoder;
  size_t d_input_item_size;
  size_t d_output_item_size;
  buf_sptr d_inbuf;

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



    
#endif /* INCLUDED_FEC_DECODER_H */

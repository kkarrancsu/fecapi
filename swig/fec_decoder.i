/* -*- c++ -*- */

%{
#include "fec_decoder.h"
#include "fec_decoder_async.h"

%}



class generic_decoder;
typedef boost::shared_ptr<generic_decoder> generic_decoder_sptr;
%template(generic_decoder_sptr) boost::shared_ptr<generic_decoder>;

%nodefaultctor generic_decoder;
class generic_decoder : public angry_fop_interface {
 public:
    ~generic_decoder();

};
 

%rename(get_decoder_output_size) fec_get_decoder_output_size(generic_decoder_sptr);
%rename(get_decoder_input_size) fec_get_decoder_input_size(generic_decoder_sptr);
%rename(get_decoder_output_item_size) fec_get_decoder_output_item_size(generic_decoder_sptr);
%rename(get_decoder_input_item_size) fec_get_decoder_input_item_size(generic_decoder_sptr);
%rename(get_conversion) fec_get_conversion(generic_decoder_sptr);
%rename(get_shift) fec_get_shift(generic_decoder_sptr);
%rename(get_output_conversion) fec_get_output_conversion(generic_decoder_sptr);
%rename(get_history) fec_get_history(generic_decoder_sptr);

int fec_get_decoder_output_size(generic_decoder_sptr my_decoder);
int fec_get_decoder_input_size(generic_decoder_sptr my_decoder);
int fec_get_decoder_output_item_size(generic_decoder_sptr my_decoder);
int fec_get_decoder_input_item_size(generic_decoder_sptr my_decoder);
int fec_get_history(generic_decoder_sptr my_decoder);
float fec_get_shift(generic_decoder_sptr my_decoder);
const char* fec_get_conversion(generic_decoder_sptr my_decoder);
const char* fec_get_output_conversion(generic_decoder_sptr my_decoder);

GR_SWIG_BLOCK_MAGIC(fec,decoder);

fec_decoder_sptr fec_make_decoder(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
		
class fec_decoder : public gr::block
{
 private:
    fec_decoder(generic_decoder_sptr, size_t, size_t);
    
};

GR_SWIG_BLOCK_MAGIC(fec,decoder_async);

fec_decoder_async_sptr fec_make_decoder_async(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size);
		
class fec_decoder_async : public gr::block
{
 private:
    fec_decoder_async(generic_decoder_sptr, size_t, size_t);
    
};

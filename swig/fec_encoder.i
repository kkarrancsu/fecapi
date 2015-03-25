/* -*- c++ -*- */

%{
#include "fec_encoder.h"
#include "fec_encoder_async.h"
%}

%nodefaultctor generic_encoder;
class generic_encoder {
 public:
    ~generic_encoder();
    
};
 
typedef boost::shared_ptr<generic_encoder> generic_encoder_sptr;
%template(generic_encoder_sptr) boost::shared_ptr<generic_encoder>;
%rename(get_encoder_output_size) fec_get_encoder_output_size(generic_encoder_sptr);
%rename(get_encoder_input_size) fec_get_encoder_input_size(generic_encoder_sptr);



int fec_get_encoder_output_size(generic_encoder_sptr my_encoder);
int fec_get_encoder_input_size(generic_encoder_sptr my_encoder);



GR_SWIG_BLOCK_MAGIC(fec,encoder);

fec_encoder_sptr fec_make_encoder(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
		
class fec_encoder : public gr::block
{
 private:
    fec_encoder(generic_encoder_sptr, size_t, size_t);
    
};

GR_SWIG_BLOCK_MAGIC(fec,encoder_async);

fec_encoder_async_sptr fec_make_encoder_async(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size);
		
class fec_encoder_async : public gr::block
{
 private:
    fec_encoder_async(generic_encoder_sptr, size_t, size_t);
    
};

#ifndef INCLUDED_LDPC_ENCODER_H
#define INCLUDED_LDPC_ENCODER_H

#include <map>
#include <string>
#include <fec_encoder.h>
#include <vector>

#include <ldpc/cldpc.h>
#include <ldpc/alist.h>

FEC_API generic_encoder_sptr
ldpc_make_encoder (std::string alist_file);


class FEC_API ldpc_encoder : public generic_encoder {
    //befriend the global, swigged make function
    friend generic_encoder_sptr
    ldpc_make_encoder (std::string alist_file);

    //private constructor
    ldpc_encoder (std::string alist_file);

    //plug into the generic fec api
    void generic_work(void *inBuffer, void *outbuffer);
    int get_output_size();
    int get_input_size();

    // memory allocated for processing
    int outputSize;
    int inputSize;
    alist d_list;
    cldpc d_code;   

 public:
    ~ldpc_encoder ();

};

#endif /* INCLUDED_LDPC_ENCODER_H */

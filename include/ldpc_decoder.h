#ifndef INCLUDED_LDPC_DECODER_H
#define INCLUDED_LDPC_DECODER_H

typedef float INPUT_DATATYPE;
typedef unsigned char OUTPUT_DATATYPE;

#include <map>
#include <string>
#include <fec_decoder.h>
#include <vector>

#include <ldpc/cldpc.h>
#include <ldpc/alist.h>
#include <ldpc/awgn_bp.h>

FEC_API generic_decoder_sptr
ldpc_make_decoder (std::string alist_file, float sigma=0.5, int max_iterations=50);

#define MAXLOG 1e7

class FEC_API ldpc_decoder : public generic_decoder {
    //befriend the global, swigged make function
    friend generic_decoder_sptr
    ldpc_make_decoder (std::string alist_file, float sigma, int max_iterations);

    //private constructor
    ldpc_decoder (std::string alist_file, float sigma, int max_iterations);

    //plug into the generic fec api
    int get_history();
	float get_shift();
	int get_input_item_size();
	int get_output_item_size();
	const char* get_conversion();
    void generic_work(void *inBuffer, void *outbuffer);
    int get_output_size();
    int get_input_size();

    int inputSize, outputSize;

      alist d_list;
      cldpc d_code;
      awgn_bp d_spa;

 public:
    ~ldpc_decoder ();

};

#endif /* INCLUDED_LDPC_DECODER_H */

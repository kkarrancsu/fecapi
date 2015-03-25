/* -*- c++ -*- */
/*
 * Copyright 2006 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */



#include <fec_encoder_async.h>
#include <gnuradio/io_signature.h>
#include <stdio.h>


fec_encoder_async_sptr
fec_make_encoder_async(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size)
{
    return gnuradio::get_initial_sptr( new fec_encoder_async(my_encoder, input_item_size, output_item_size));
}

fec_encoder_async::fec_encoder_async(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size)
  : gr::block("fec_encoder_async",
	       gr::io_signature::make(0,0,0),
	       gr::io_signature::make(0,0,0)),
      d_input_item_size(input_item_size), d_output_item_size(output_item_size)
{
    //printf(" I/O size = %d / %d\n", input_item_size, output_item_size);
    d_encoder = my_encoder;
    message_port_register_in(pmt::mp("pdus"));
    message_port_register_out(pmt::mp("pdus"));
    set_msg_handler(pmt::mp("pdus"), boost::bind( &fec_encoder_async::encode, this ,_1) );
}

void
fec_encoder_async::encode(pmt::pmt_t msg)
{   
    // extract input pdu 
    pmt::pmt_t meta(pmt::car(msg));
    pmt::pmt_t bits(pmt::cdr(msg));
    
    int nbits = pmt::length(bits);
    int blksize_in = d_encoder->get_input_size();
    int blksize_out = d_encoder->get_output_size();
    int nblocks = nbits/blksize_in;
    //printf("encoder :: blksize_in = %d, blksize_out = %d nblocks=%d\n", blksize_in, blksize_out, nblocks);

    pmt::pmt_t outvec(pmt::make_u8vector(blksize_out * nblocks, 0xFF));
    //printf("encoder :: outvec len = %d\n", blksize_out * nblocks);

    // get pmt buffer pointers
    size_t o0(0);
    const uint8_t* u8in = pmt::u8vector_elements(bits,o0);
    uint8_t* u8tmp = pmt::u8vector_writable_elements(bits,o0);

    uint8_t* u8out = pmt::u8vector_writable_elements(outvec,o0);      
        
    // alloc float playspace
    std::vector<float> flt_out(blksize_out);

    // loop over n fec blocks
    for(int i = 0; i < nblocks; i++) {
        size_t offset_in = i * blksize_in;
        size_t offset_out = i * blksize_out;

        // print out the values here ... why are we segfaulting??
        for(int jj=0; jj<blksize_in; jj++) {
        	u8tmp[offset_in + jj] = 0x01 & u8in[offset_in + jj];
//        	printf("in[%zd]=%u ", offset_in+jj, u8tmp[offset_in + jj]);
//        	fflush(stdout);
        }
//        printf("done --> \n");
        //fflush(stdout);
 
        // ENCODE!
	    d_encoder->generic_work((void*) &u8tmp[offset_in], (void*) &flt_out[0]);

        // convert float -> u8
        for(int j=0; j<blksize_out; j++){
            u8out[offset_out + j] = (flt_out[j] > 0);
        }

    }

    message_port_pub(pmt::mp("pdus"),  pmt::cons( meta, outvec ) );
}

int
fec_encoder_async::general_work (int noutput_items,
			   gr_vector_int& ninput_items,
			   gr_vector_const_void_star &input_items,
			   gr_vector_void_star &output_items)
{
    return noutput_items;
}


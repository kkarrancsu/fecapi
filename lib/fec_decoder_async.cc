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



#include <fec_decoder_async.h>
#include <gnuradio/io_signature.h>
#include <stdio.h>


fec_decoder_async_sptr
fec_make_decoder_async(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size)
{
	//printf("decoder_make :: inputItemSize=%d >> outputItemSize=%d\n",
	//		input_item_size, output_item_size);
	//fflush(stdout);

    return gnuradio::get_initial_sptr( new fec_decoder_async(my_decoder, input_item_size, output_item_size));
}

fec_decoder_async::fec_decoder_async(generic_decoder_sptr my_decoder, size_t input_item_size, size_t output_item_size)
  : gr::block("fec_decoder_async",
	       gr::io_signature::make(0,0,0),
	       gr::io_signature::make(0,0,0)),
      d_input_item_size(input_item_size), d_output_item_size(output_item_size)
{
    //printf("decoder :: I/O size = %d / %d\n", input_item_size, output_item_size);
    //fflush(stdout);
    d_decoder = my_decoder;
    message_port_register_in(pmt::mp("fpdus"));
    message_port_register_out(pmt::mp("pdus"));
    set_msg_handler(pmt::mp("fpdus"), boost::bind( &fec_decoder_async::decode, this ,_1) );
    //printf("decoder :: constructor done!\n");
    //fflush(stdout);
}

void
fec_decoder_async::decode(pmt::pmt_t msg)
{
	//printf("decoder :: in DECODE main routine!\n");
	//fflush(stdout);

    // extract input pdu
    pmt::pmt_t meta(pmt::car(msg));
    pmt::pmt_t bits(pmt::cdr(msg));

    //printf("decoder :: extracted input MPDU!\n");
	//fflush(stdout);

    int nbits = pmt::length(bits);
    int blksize_in = d_decoder->get_input_size();
    int blksize_out = d_decoder->get_output_size();
    int nblocks = nbits/blksize_in;

    //printf("decoder :: did initial calculations!\n");
	//fflush(stdout);

    // nbits sanity check
    if(nbits % blksize_in != 0){
        throw std::runtime_error((boost::format("nbits_in %% blksize_in != 0 in fec_decoder_asyn! %d bits in, %d blksize")%nbits%blksize_in).str());
        }

    //printf("decoder :: blksize_in = %d, blksize_out = %d\n", blksize_in, blksize_out);
    //fflush(stdout);

    pmt::pmt_t outvec(pmt::make_u8vector(blksize_out * nblocks, 0xFF));
    //printf("decoder :: outvec len = %d (%d blks)\n", blksize_out * nblocks, nblocks);
    //fflush(stdout);

    // get pmt buffer pointers
    size_t o0(0);
    const float* f32in = pmt::f32vector_elements(bits,o0);
    uint8_t* u8out = pmt::u8vector_writable_elements(outvec,o0);

    // loop over n fec blocks
    for(int i = 0; i < nblocks; i++) {
        size_t offset_in = i * blksize_in;
        size_t offset_out = i * blksize_out;

        // DECODE!
	    d_decoder->generic_work((void*) &f32in[offset_in], (void*) &u8out[offset_out]);
    }

    message_port_pub(pmt::mp("pdus"),  pmt::cons( meta, outvec ) );
}

int
fec_decoder_async::general_work (int noutput_items,
			   gr_vector_int& ninput_items,
			   gr_vector_const_void_star &input_items,
			   gr_vector_void_star &output_items)
{
	//printf("decoder :: in general_work\n");
	//fflush(stdout);
    return noutput_items;
}


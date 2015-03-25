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



#include <fec_encoder.h>
#include <gnuradio/io_signature.h>
#include <stdio.h>

generic_encoder::~generic_encoder() {;}


fec_encoder_sptr
fec_make_encoder(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size)
{
    return gnuradio::get_initial_sptr( new fec_encoder(my_encoder, input_item_size, output_item_size));
}

int
fec_get_encoder_output_size(generic_encoder_sptr my_encoder)
{
    return my_encoder->get_output_size();
}

int
fec_get_encoder_input_size(generic_encoder_sptr my_encoder)
{
    return my_encoder->get_input_size();
}



fec_encoder::fec_encoder(generic_encoder_sptr my_encoder, size_t input_item_size, size_t output_item_size)
  : gr::block("fec_encoder",
	       gr::io_signature::make(1, 1, input_item_size),
	       gr::io_signature::make(1, 1, output_item_size)),
      d_input_item_size(input_item_size), d_output_item_size(output_item_size)
{
    set_fixed_rate(true);
    set_relative_rate((double)my_encoder->get_output_size()/my_encoder->get_input_size());
    set_output_multiple(my_encoder->get_output_size());
    d_encoder = my_encoder;
    
}


int
fec_encoder::fixed_rate_ninput_to_noutput(int ninput) {
    return (int)(((d_encoder->get_output_size()/(double)d_encoder->get_input_size()) * ninput) + .5);
}

int
fec_encoder::fixed_rate_noutput_to_ninput(int noutput) {
    return (int)(((d_encoder->get_input_size()/(double)d_encoder->get_output_size()) * noutput) + .5);
}

void 
fec_encoder::forecast(int noutput_items, 
		      gr_vector_int& ninput_items_required) {
    ninput_items_required[0] = (int)(((d_encoder->get_input_size()/(double)d_encoder->get_output_size()) * noutput_items) + .5);
    return;
}



int
fec_encoder::general_work (int noutput_items,
			   gr_vector_int& ninput_items,
			   gr_vector_const_void_star &input_items,
			   gr_vector_void_star &output_items)
{

    char *inBuffer = (char*) input_items[0];
    char *outBuffer = (char*)output_items[0];
    for(int i = 0; i < noutput_items/output_multiple(); ++i) {
	
	//printf("%u inp %u oup\n", d_input_item_size, d_output_item_size);
	//printf("%u, %u\n", (i*d_encoder->get_input_size()*d_input_item_size), (i*d_encoder->get_output_size()*d_output_item_size));
	
	d_encoder->generic_work((void*) (inBuffer+(i*d_encoder->get_input_size()*d_input_item_size)), (void*) (outBuffer+(i*d_encoder->get_output_size()*d_output_item_size)));
    } 
    
    //printf("%d, %u, %u\n", (int)(((1.0/relative_rate()) * noutput_items) + .5), noutput_items, output_multiple()); 
    
    consume_each((int)(((1.0/relative_rate()) * noutput_items) + .5));
    return noutput_items;
}


/* -*- c++ -*- */
/*
 * Copyright 2004,2010 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fec_interleave.h>
#include <gnuradio/io_signature.h>
#include <string.h>




fec_interleave_sptr
fec_make_interleave (size_t itemsize, unsigned int blocksize)
{
    return gnuradio::get_initial_sptr(new fec_interleave (itemsize, blocksize));
}

fec_interleave::fec_interleave (size_t itemsize, unsigned int blocksize)
  : gr::block ("interleave",
	       gr::io_signature::make (1, gr::io_signature::IO_INFINITE, itemsize),
	      gr::io_signature::make (1, 1, itemsize)),
    d_itemsize (itemsize), d_blocksize(blocksize)
{
    set_fixed_rate(true);
    set_output_multiple(d_blocksize);
}

fec_interleave::~fec_interleave ()
{
  // NOP
}

bool
fec_interleave::check_topology (int ninputs, int noutputs)
{
    set_relative_rate((double)ninputs);
    d_ninputs = ninputs;
    set_output_multiple(d_blocksize * d_ninputs);
    return true;
}

int
fec_interleave::fixed_rate_ninput_to_noutput(int ninput) {
    return ninput * d_ninputs;
}

int
fec_interleave::fixed_rate_noutput_to_ninput(int noutput) {
    return (int) ((noutput / d_ninputs) + .5);
}

void 
fec_interleave::forecast(int noutput_items, 
			 gr_vector_int& ninput_items_required) {
    for(int i = 0; i < ninput_items_required.size(); ++i) {
	ninput_items_required[i] = (int) ((noutput_items / ninput_items_required.size()) + .5);
    }
    return;
}



int
fec_interleave::general_work (int noutput_items,
			      gr_vector_int& ninput_items,
			      gr_vector_const_void_star &input_items,
			      gr_vector_void_star &output_items)
{
    
    
    
    size_t noutput_blocks = (size_t) ((noutput_items/d_blocksize) + .5);
    const char **in = (const char **) &input_items[0];
    char *out = (char *) output_items[0];
    
    for (int i = 0; i < noutput_blocks; i += d_ninputs){
	for (unsigned int n = 0; n < d_ninputs; n++){
	    memcpy (out, in[n], d_itemsize * d_blocksize);
	    out += d_itemsize * d_blocksize;
	    in[n] += d_itemsize * d_blocksize;
	}
    }
    consume_each((int)((noutput_items/d_ninputs) + .5));
    return noutput_items;
}

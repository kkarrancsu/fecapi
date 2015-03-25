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

#include <fec_deinterleave.h>
#include <gnuradio/io_signature.h>
#include <string.h>
#include <stdio.h>



fec_deinterleave_sptr
fec_make_deinterleave (size_t itemsize, unsigned int blocksize)
{
    return gnuradio::get_initial_sptr(new fec_deinterleave (itemsize, blocksize));
}

fec_deinterleave::fec_deinterleave (size_t itemsize, unsigned int blocksize)
  : gr::block ("deinterleave",
	      gr::io_signature::make (1, 1, itemsize),
	       gr::io_signature::make (1, gr::io_signature::IO_INFINITE, itemsize)),
    d_itemsize (itemsize), d_blocksize(blocksize), d_current_output(0)
{

    set_output_multiple(d_blocksize);
}

fec_deinterleave::~fec_deinterleave ()
{
  // NOP
}

bool
fec_deinterleave::check_topology (int ninputs, int noutputs)
{
    set_relative_rate((double)noutputs);
    d_noutputs = noutputs;
    return true;
}




int
fec_deinterleave::general_work (int noutput_items,
				gr_vector_int& ninput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items)
{

    const char *in = (const char *) input_items[0];
    char **out = (char **) &output_items[0];
    
    
    
    memcpy(out[d_current_output], in, d_itemsize * d_blocksize);
    consume_each(d_blocksize);
    produce(d_current_output, d_blocksize);
    d_current_output = (d_current_output + 1) % d_noutputs;
    return WORK_CALLED_PRODUCE;
    
}



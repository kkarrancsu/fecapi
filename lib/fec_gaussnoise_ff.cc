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
 * Boston, MA 02110-1301, USA.z
 */



#include <fec_gaussnoise_ff.h>
#include <gnuradio/io_signature.h>
#include <libbertools.h>
#include <math.h>


fec_gaussnoise_ff_sptr
fec_make_gaussnoise_ff(float EsNo)
{
    return gnuradio::get_initial_sptr(new fec_gaussnoise_ff(EsNo));
}

fec_gaussnoise_ff::fec_gaussnoise_ff(float EsNo)
  : gr::sync_block("fec_gaussnoise_ff",
		  gr::io_signature::make(1, 1, sizeof(float)),
		  gr::io_signature::make(1, 1, sizeof(float)))
{ 
    d_sigma = pow(10,-0.1*EsNo);
    d_sigma = d_sigma/(2.0);
    d_sigma = sqrt(d_sigma); 
}



int
fec_gaussnoise_ff::work (int noutput_items,
			 gr_vector_const_void_star &input_items,
			 gr_vector_void_star &output_items)
{
    float *outBuffer = (float *)output_items[0];
    float *inBuffer = (float *)input_items[0];

    memcpy(outBuffer, inBuffer, sizeof(float)*noutput_items);
    
    gaussnoise(outBuffer, noutput_items, d_sigma);
    
    return noutput_items;
}


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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fec_random_gen_b.h>
#include <gnuradio/io_signature.h>
#include <libbertools.h>
#include <math.h>
#include <time.h>

fec_random_gen_b_sptr
fec_make_random_gen_b(long int randSeed)
{
    return gnuradio::get_initial_sptr(new fec_random_gen_b(randSeed));
}

fec_random_gen_b::fec_random_gen_b(long int randSeed)
  : gr::sync_block("fec_random_gen_b",
		   gr::io_signature::make(0,0,0),
		   gr::io_signature::make(1, 1, sizeof(unsigned char)))
{
    if (randSeed == 0) {
	d_randSeed = 0xfff & (long int)time(NULL);
	srand48(randSeed);
    }
    else {
	d_randSeed = randSeed;
    }
    
}



int
fec_random_gen_b::work (int noutput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items)
{
  unsigned char *outBuffer = (unsigned char *)output_items[0];

  
  
  randBuffer(outBuffer, noutput_items, 1);
  
  

  return noutput_items;
}


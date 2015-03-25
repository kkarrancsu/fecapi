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
#ifndef INCLUDED_FEC_GAUSSNOISE_FF_H
#define INCLUDED_FEC_GAUSSNOISE_FF_H

#include <gnuradio/sync_block.h>
#include <fec_api.h>


class fec_gaussnoise_ff;
typedef boost::shared_ptr<fec_gaussnoise_ff> fec_gaussnoise_ff_sptr;


FEC_API fec_gaussnoise_ff_sptr fec_make_gaussnoise_ff(float EsNo);


class FEC_API fec_gaussnoise_ff : public gr::sync_block
{
  friend fec_gaussnoise_ff_sptr fec_make_gaussnoise_ff(float EsNo);
  float d_sigma; //callback opportunity
  fec_gaussnoise_ff(float EsNo);
  
 public:
  int work (int noutput_items, 
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
};


#endif /* INCLUDED_FEC_GAUSSNOISE_FF_H */

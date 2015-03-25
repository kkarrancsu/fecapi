/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
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

#ifndef INCLUDED_FEC_INTERLEAVE_H
#define INCLUDED_FEC_INTERLEAVE_H

#include <fec_api.h>
#include <gnuradio/block.h>

class fec_interleave;
typedef boost::shared_ptr<fec_interleave> fec_interleave_sptr;

FEC_API fec_interleave_sptr fec_make_interleave (size_t itemsize, unsigned int blocksize);

/*!
 * \brief interleave N coding blocks to a single output
 */
class FEC_API fec_interleave : public gr::block
{
    friend fec_interleave_sptr fec_make_interleave (size_t itemsize, unsigned int blocksize);

    size_t d_itemsize;
    unsigned int d_blocksize;
    unsigned int d_ninputs;
    fec_interleave (size_t itemsize, unsigned int blocksize);

public:
  ~fec_interleave ();

  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
  int fixed_rate_ninput_to_noutput(int ninput);
  int fixed_rate_noutput_to_ninput(int noutput);
  void forecast(int noutput_items,
		gr_vector_int& ninput_items_required);
  bool check_topology (int ninputs, int noutputs);

};

#endif /* INCLUDED_FEC_INTERLEAVE_H */

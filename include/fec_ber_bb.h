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
#ifndef INCLUDED_FEC_BER_BB_H
#define INCLUDED_FEC_BER_BB_H

#include <gnuradio/block.h>
#include <fec_api.h>


class fec_ber_bb;
typedef boost::shared_ptr<fec_ber_bb> fec_ber_bb_sptr;


FEC_API fec_ber_bb_sptr fec_make_ber_bb(int berminerrors = 100, float berLimit = -7.0);


class FEC_API fec_ber_bb : public gr::block
{
    friend fec_ber_bb_sptr fec_make_ber_bb(int berminerrors, float berLimit);
    int d_totalErrors;
    int d_berminerrors;
    float d_berLimit;
    int d_total;
    fec_ber_bb(int berminerrors = 100, float berLimit = -7.0);
    
 public:
    int general_work (int noutput_items,
		      gr_vector_int& ninput_items,
		      gr_vector_const_void_star &input_items,
		      gr_vector_void_star &output_items);
    void forecast(int noutput_items,
		  gr_vector_int& ninput_items_required);
};


#endif /* INCLUDED_FEC_BER_BB_H */

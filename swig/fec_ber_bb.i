/* -*- c++ -*- */
/*
 * Copyright 2008 Free Software Foundation, Inc.
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access gr_example_square_ff from python as howto.square_ff
 */

%{
#include "fec_ber_bb.h"
%}

GR_SWIG_BLOCK_MAGIC(fec,ber_bb);

fec_ber_bb_sptr fec_make_ber_bb(int BERMINERRORS = 100, float berLimit = -7.0);

class fec_ber_bb : public gr::block
{
private:
    fec_ber_bb(int BERMINERRORS = 100, float berLimit = -7.0);

};

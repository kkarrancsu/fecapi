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



#include <fec_ber_bb.h>
#include <gnuradio/io_signature.h>
#include <libbertools.h>
#include <math.h>


fec_ber_bb_sptr
fec_make_ber_bb(int berminerrors, float berLimit)
{
    return gnuradio::get_initial_sptr(new fec_ber_bb(berminerrors, berLimit));
}

fec_ber_bb::fec_ber_bb(int berminerrors, float berLimit)
  : gr::block("fec_ber_bb",
	       gr::io_signature::make(2, 2, sizeof(unsigned char)),
	       gr::io_signature::make(1, 1, sizeof(float))),
      d_berminerrors(berminerrors), d_berLimit(berLimit), 
      d_totalErrors(0), d_total(0)
{
    
}



void fec_ber_bb::forecast(int noutput_items,
	      gr_vector_int& ninput_items_required) {
    ninput_items_required[0] = 1<<10 * noutput_items;
    ninput_items_required[1] = 1<<10 * noutput_items;
    return;
}

int
fec_ber_bb::general_work (int noutput_items,
			 gr_vector_int& ninput_items,
			 gr_vector_const_void_star &input_items,
			 gr_vector_void_star &output_items)
{

    if (d_totalErrors >= d_berminerrors) {
	return -1;
    }
    
    else {
	    
	unsigned char *inBuffer0 = (unsigned char *)input_items[0];
	unsigned char *inBuffer1 = (unsigned char *)input_items[1];
	float *outBuffer = (float *)output_items[0];
    
	int items = ninput_items[0] <= ninput_items[1] ? ninput_items[0] : ninput_items[1];
    
	if(items > 0) {
	    /*for(int i = 0; i < items; ++i) {
            if(inBuffer0[i] != inBuffer1[i]) {
                printf("%d/%d:   %u versus %u\n", i, items, inBuffer0[i], inBuffer1[i]);
            }
        }
	    printf("%d errors\n", compBER(inBuffer0, inBuffer1, items));*/
	    d_totalErrors += compBER(inBuffer0, inBuffer1, items);
	    d_total += items;
	}
	consume_each(items);
    
    

	if(d_totalErrors >= d_berminerrors) {
	    printf("    %u over %d\n", d_totalErrors, d_total * 8);
	    outBuffer[0] = log10(((double)d_totalErrors)/(d_total * 8.0));
	    return 1;
	}
	else if(log10(((double)d_berminerrors)/(d_total * 8.0)) < d_berLimit) {
	    printf("crapout\n");
	    outBuffer[0] = d_berLimit;
	    d_totalErrors = d_berminerrors + 1;
	    return 1;
	}
	else {
	    return 0;
	}
    }
}


#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Threaded Decoder Template Test
# Generated: Tue Jan 24 19:16:53 2012
##################################################

from gnuradio import gr

import fec


class threaded_decoder(gr.hier_block2):
        
	def __init__(self, decoder_list_0, input_size, output_size):
		gr.hier_block2.__init__(
			self, "Threaded Decoder",
			gr.io_signature(1, 1, input_size*1),
			gr.io_signature(1, 1, output_size*1),
		)

		##################################################
		# Parameters
		##################################################
		self.decoder_list_0 = decoder_list_0

		##################################################
		# Variables
		##################################################
		

		##################################################
		# Blocks
		##################################################
		self.fec_deinterleave_0 = fec.deinterleave(input_size, fec.get_decoder_input_size(decoder_list_0[0]))
		
		self.generic_decoders_0 = [];
		for i in range(len(decoder_list_0)):
			self.generic_decoders_0.append(fec.decoder(decoder_list_0[i], input_size, output_size))
                
		self.fec_interleave_0 = fec.interleave(output_size, fec.get_decoder_output_size(decoder_list_0[0]))

		##################################################
		# Connections
		##################################################
		

		
		
		for i in range(len(decoder_list_0)):		
			self.connect((self.fec_deinterleave_0, i), (self.generic_decoders_0[i], 0))

		for i in range(len(decoder_list_0)):		
			self.connect((self.generic_decoders_0[i], 0), (self.fec_interleave_0, i))
		

		self.connect((self, 0), (self.fec_deinterleave_0, 0))
		self.connect((self.fec_interleave_0, 0), (self, 0))
		

	def get_decoder_list_0(self):
		return self.decoder_list_0

	def set_decoder_list_0(self, decoder_list_0):
		self.decoder_list_0 = decoder_list_0

	


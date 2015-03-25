#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Threaded Decoder Template Test
# Generated: Tue Jan 24 19:16:53 2012
##################################################

from gnuradio import gr

import fec


class threaded_encoder(gr.hier_block2):

	def __init__(self, encoder_list_0, input_size, output_size):
		gr.hier_block2.__init__(
			self, "Threaded Encoder",
			gr.io_signature(1, 1, input_size*1),
			gr.io_signature(1, 1, output_size*1),
		)

		##################################################
		# Parameters
		##################################################
		self.encoder_list_0 = encoder_list_0

		##################################################
		# Variables
		##################################################
		

		##################################################
		# Blocks
		##################################################
		self.fec_deinterleave_0 = fec.deinterleave(input_size, fec.get_encoder_input_size(encoder_list_0[0]))
		
		self.generic_encoders_0 = [];
		for i in range(len(encoder_list_0)):
			self.generic_encoders_0.append(fec.encoder(encoder_list_0[i], input_size, output_size))
		
		self.fec_interleave_0 = fec.interleave(output_size, fec.get_encoder_output_size(encoder_list_0[0]))

		##################################################
		# Connections
		##################################################
		

		
		
		for i in range(len(encoder_list_0)):		
			self.connect((self.fec_deinterleave_0, i), (self.generic_encoders_0[i], 0))

		for i in range(len(encoder_list_0)):		
			self.connect((self.generic_encoders_0[i], 0), (self.fec_interleave_0, i))
		

		self.connect((self, 0), (self.fec_deinterleave_0, 0))
		self.connect((self.fec_interleave_0, 0), (self, 0))
		

	def get_encoder_list_0(self):
		return self.encoder_list_0

	def set_encoder_list_0(self, encoder_list_0):
		self.encoder_list_0 = encoder_list_0

	


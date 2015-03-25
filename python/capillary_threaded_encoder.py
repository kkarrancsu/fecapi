#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Threaded Encoder Template Test
# Generated: Tue Jan 24 19:16:53 2012
##################################################

from gnuradio import gr
import fec
import math

class capillary_threaded_encoder(gr.hier_block2):

	def __init__(self, encoder_list_0, input_size=gr.sizeof_char, output_size=gr.sizeof_float):
		gr.hier_block2.__init__(
			self, "Capillary Threaded Encoder",
			gr.io_signature(1, 1, input_size),
			gr.io_signature(1, 1, output_size),
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
		self.fec_deinterleaves_0 = [];
		for i in range(int(math.log(len(encoder_list_0), 2))):
			for j in range(int(math.pow(2, i))):
				self.fec_deinterleaves_0.append(fec.deinterleave(input_size, fec.get_encoder_input_size(encoder_list_0[0])))
		
		self.generic_encoders_0 = [];
		for i in range(len(encoder_list_0)):
			self.generic_encoders_0.append(fec.encoder(encoder_list_0[i], input_size, output_size))
			
			
		self.fec_interleaves_0 = [];
		for i in range(int(math.log(len(encoder_list_0), 2))):
			for j in range(int(math.pow(2, i))):
				self.fec_interleaves_0.append(fec.interleave(output_size, fec.get_encoder_output_size(encoder_list_0[0])))

		##################################################
		# Connections
		##################################################
		
		rootcount = 0;
		branchcount = 1;
		for i in range(int(math.log(len(encoder_list_0), 2)) - 1):
			for j in range(int(math.pow(2, i))):
				self.connect((self.fec_deinterleaves_0[rootcount], 0), (self.fec_deinterleaves_0[branchcount], 0))
				self.connect((self.fec_deinterleaves_0[rootcount], 1), (self.fec_deinterleaves_0[branchcount + 1], 0))
				rootcount += 1;
				branchcount += 2;
					 
		codercount = 0;
		for i in range(len(encoder_list_0)/2):		
			self.connect((self.fec_deinterleaves_0[rootcount], 0), (self.generic_encoders_0[codercount], 0))
			self.connect((self.fec_deinterleaves_0[rootcount], 1), (self.generic_encoders_0[codercount + 1], 0))
			rootcount += 1;
			codercount += 2;
		
		
		rootcount = 0;
		branchcount = 1;
		for i in range(int(math.log(len(encoder_list_0), 2)) - 1):
			for j in range(int(math.pow(2, i))):
				self.connect((self.fec_interleaves_0[branchcount], 0), (self.fec_interleaves_0[rootcount], 0))
				self.connect((self.fec_interleaves_0[branchcount + 1], 0), (self.fec_interleaves_0[rootcount], 1))
				rootcount += 1;
				branchcount += 2;


		codercount = 0;
		for i in range(len(encoder_list_0)/2):		
			self.connect((self.generic_encoders_0[codercount], 0), (self.fec_interleaves_0[rootcount], 0))
			self.connect((self.generic_encoders_0[codercount + 1], 0), (self.fec_interleaves_0[rootcount], 1))
			rootcount += 1;
			codercount += 2;

		if ((len(self.encoder_list_0)) > 1):
			self.connect((self, 0), (self.fec_deinterleaves_0[0], 0))
			self.connect((self.fec_interleaves_0[0], 0), (self, 0))
		else:
			self.connect((self, 0), (self.generic_encoders_0[0], 0))
			self.connect((self.generic_encoders_0[0], 0), (self, 0))
	
	def set_max_output_buffer(self,m):
		block_lists = [self.fec_deinterleaves_0, self.generic_encoders_0, self.fec_interleaves_0];
		for bl in block_lists:
			for b in bl:
				b.set_max_output_buffer(m);

	def get_encoder_list_0(self):
		return self.encoder_list_0

	def set_encoder_list_0(self, encoder_list_0):
		self.encoder_list_0 = encoder_list_0

	


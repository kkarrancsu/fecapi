#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Bercurve
# Generated: Thu Jan 19 11:31:13 2012
##################################################


from gnuradio import gr, blocks

import fec, numpy
from fec.ber_generator import ber_generator

class bercurve_generator(gr.hier_block2):

	def __init__(self, esno=numpy.arange(0.0, 3.0, .25), samp_rate=32000, encoder_list=0, decoder_list=0, berminerrors=100, berlimit=-7.0, threading='capillary', puncpat='11'):
		gr.hier_block2.__init__(
			self, "Bercurve",
			gr.io_signature(0, 0, 0),
			gr.io_signature(1, 1, gr.sizeof_float*1),
		)
		
		##################################################
		# Parameters
		##################################################
		self.esno = esno
		self.samp_rate = samp_rate
		self.encoder_list = encoder_list
		self.decoder_list = decoder_list
		self.berminerrors = berminerrors
		self.berlimit = berlimit
		self.puncpat = puncpat

		##################################################
		# Blocks
		##################################################
		self.gr_interleave_0 = blocks.interleave(gr.sizeof_float*1)
		self.ber_generators = []
		for i in range(0, len(esno)):
			ber_generator_temp = ber_generator(
				generic_encoder=encoder_list[i],
				generic_decoder=decoder_list[i],
				esno=esno[i],
				samp_rate=samp_rate,
				berminerrors=berminerrors,
				berlimit=berlimit,
				threading=threading,
				puncpat=puncpat
				);
			self.ber_generators.append(ber_generator_temp);
		##################################################
		# Connections
		##################################################
		for i in range(0, len(esno)):			
			self.connect((self.ber_generators[i], 0), (self.gr_interleave_0, i));
		self.connect((self.gr_interleave_0, 0), (self, 0))

	def get_esno(self):
		return self.esno

	def set_esno(self, esno):
		self.esno = esno
		self.ber_generator_0.set_esno(self.esno)

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.ber_generator_0.set_samp_rate(self.samp_rate)

	def get_encoder_list(self):
		return self.encoder_list

	def set_encoder_list(self, encoder_list):
		self.encoder_list = encoder_list
		self.ber_generator_0.set_generic_encoder(self.encoder_list)

	def get_decoder_list(self):
		return self.decoder_list

	def set_decoder_list(self, decoder_list):
		self.decoder_list = decoder_list
		self.ber_generator_0.set_generic_decoder(self.decoder_list)

	def get_puncpat(self):
		return self.puncpat

	def set_puncpat(self, puncpat):
		self.puncpat = puncpat


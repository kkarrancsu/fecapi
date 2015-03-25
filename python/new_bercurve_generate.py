#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Qt Bercurve
##################################################


from gnuradio import gr, blocks

import fec, numpy
from fec.fec_test import fec_test


class new_bercurve_generator(gr.hier_block2):

	def __init__(self, encoder_list, decoder_list, esno=numpy.arange(0.0, 3.0, .25), samp_rate=3200000, threading='capillary', puncpat='11'):
		gr.hier_block2.__init__(
			self, "New Bercurve",
			gr.io_signature(0, 0, 0),
			gr.io_signature(len(esno) * 2, len(esno) * 2, gr.sizeof_char*1),
		)

		##################################################
		# Parameters
		##################################################
		self.esno = esno
		self.samp_rate = samp_rate
		self.encoder_list = encoder_list
		self.decoder_list = decoder_list
		self.puncpat = puncpat

		##################################################
		# Blocks
		##################################################
		self.random_gen_b_0 = fec.random_gen_b(0)
		self.deinterleave = blocks.deinterleave(gr.sizeof_char*1)
		self.connect(self.random_gen_b_0, self.deinterleave);
		self.ber_generators = []
		for i in range(0, len(esno)):
			ber_generator_temp = fec_test(
				generic_encoder=encoder_list[i],
				generic_decoder=decoder_list[i],
				esno=esno[i],
				samp_rate=samp_rate,
				threading=threading,
				puncpat=puncpat
				);
			self.ber_generators.append(ber_generator_temp);
		
		##################################################
		# Connections
		##################################################
		for i in range(0, len(esno)):
			self.connect((self.deinterleave, i), (self.ber_generators[i]))
			self.connect((self.ber_generators[i], 0), (self, i*2));
			self.connect((self.ber_generators[i], 1), (self, i*2 + 1));
		

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


#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: BER Generator
# Generated: Thu Feb 16 17:22:31 2012
##################################################

from fec.bitflip import read_bitlist
from fec.extended_decoder_interface import extended_decoder_interface
from fec.extended_encoder_interface import extended_encoder_interface
from gnuradio import gr, blocks
import fec

class ber_generator(gr.hier_block2):

	def __init__(self, generic_encoder=0, generic_decoder=0, esno=0, berminerrors=100, samp_rate=32000, berlimit=-5.0, threading="capillary", puncpat='11'):
		gr.hier_block2.__init__(
			self, "BER Generator",
			gr.io_signature(0, 0, 0),
			gr.io_signature(1, 1, gr.sizeof_float*1),
		)
                
		##################################################
		# Parameters
		##################################################
		self.generic_encoder = generic_encoder
		self.generic_decoder = generic_decoder
		self.esno = esno
		self.berminerrors = berminerrors
		self.samp_rate = samp_rate
		self.berlimit = berlimit
		self.threading = threading
		self.puncpat = puncpat

		##################################################
		# Blocks
		##################################################
		self.random_gen_b_0 = fec.random_gen_b(0)
		#self.puncture_ff_0 = fec.puncture_ff(0, read_bitlist(puncpat), puncpat.count('0'), len(puncpat))
		self.gr_unpacked_to_packed_xx_0_0 = blocks.unpacked_to_packed_bb(1, gr.GR_LSB_FIRST)
		self.gr_unpacked_to_packed_xx_0 = blocks.unpacked_to_packed_bb(1, gr.GR_LSB_FIRST)
		self.gr_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate)
		#self.generic_encoder_0 = fec.encoder(generic_encoder, gr.sizeof_char, gr.sizeof_float)
                self.encoder_interface_0 = extended_encoder_interface(encoder_obj_list=generic_encoder, threading='capillary', puncpat=puncpat);
		self.gaussnoise_ff_0 = fec.gaussnoise_ff(esno)
		self.decoder_interface_0 = extended_decoder_interface(decoder_obj_list=generic_decoder, threading='capillary', ann=None, puncpat=puncpat, integration_period=10000, rotator=None)
		self.ber_bb_0_0 = fec.ber_bb(berminerrors, berlimit)

		##################################################
		# Connections
		##################################################
		self.connect((self.gr_unpacked_to_packed_xx_0_0, 0), (self.ber_bb_0_0, 0))
		self.connect((self.gr_unpacked_to_packed_xx_0, 0), (self.ber_bb_0_0, 1))
		#self.connect((self.gr_throttle_0, 0), (self.generic_encoder_0, 0))
		self.connect((self.gr_throttle_0, 0), (self.gr_unpacked_to_packed_xx_0, 0))
		self.connect((self.ber_bb_0_0, 0), (self, 0))
		self.connect((self.decoder_interface_0, 0), (self.gr_unpacked_to_packed_xx_0_0, 0))
		#self.connect((self.generic_encoder_0, 0), (self.puncture_ff_0, 0))
		#self.connect((self.puncture_ff_0, 0), (self.gaussnoise_ff_0, 0))
		self.connect((self.gaussnoise_ff_0, 0), (self.decoder_interface_0, 0))
		self.connect((self.random_gen_b_0, 0), (self.gr_throttle_0, 0))
                self.connect((self.gr_throttle_0, 0), (self.encoder_interface_0, 0))
                self.connect((self.encoder_interface_0, 0), (self.gaussnoise_ff_0, 0))

	def get_generic_encoder(self):
		return self.generic_encoder

	def set_generic_encoder(self, generic_encoder):
		self.generic_encoder = generic_encoder

	def get_generic_decoder(self):
		return self.generic_decoder

	def set_generic_decoder(self, generic_decoder):
		self.generic_decoder = generic_decoder

	def get_esno(self):
		return self.esno

	def set_esno(self, esno):
		self.esno = esno

	def get_berminerrors(self):
		return self.berminerrors

	def set_berminerrors(self, berminerrors):
		self.berminerrors = berminerrors

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate

	def get_berlimit(self):
		return self.berlimit

	def set_berlimit(self, berlimit):
		self.berlimit = berlimit

	def get_threading(self):
		return self.threading

	def set_threading(self, threading):
		self.threading = threading

	def get_puncpat(self):
		return self.puncpat

	def set_puncpat(self, puncpat):
		self.puncpat = puncpat



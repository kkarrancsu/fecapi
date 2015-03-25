#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: TPC Encode & Decode Test
# Generated: 
##################################################

from gnuradio import gr, gr_unittest
from gnuradio import blocks
from fec.extended_encoder_interface import extended_encoder_interface
from fec.extended_decoder_interface import extended_decoder_interface
import fec

import os

class qa_tpc_encode_decode(gr_unittest.TestCase):
    def setUp(self):
        self.tb = gr.top_block()
        self.testFilesDir = os.path.join(os.environ['srcdir'], '..', 'testdata')
    
    def tearDown(self):
        self.tb = None
        
    def test_001(self):
        print 'Running TPC_ENCODE_DECODE_TEST1'
        
if __name__=='__main__':
    gr_unittest.run(qa_tpc_encode_decode)
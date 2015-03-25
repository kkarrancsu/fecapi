#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: TPC Encoder Test
# Generated: 
##################################################

from gnuradio import gr, gr_unittest
from gnuradio import blocks
from fec.extended_encoder_interface import extended_encoder_interface
import fec

import os

class qa_tpc_encoder(gr_unittest.TestCase):
    def setUp(self):
        self.tb = gr.top_block()
        self.testFilesDir = os.path.join(os.environ['srcdir'], '..', 'testdata')
    
    def tearDown(self):
        self.tb = None
    
    def readBinaryFile(self, filename):
        fileData = ()
        f = open(filename, 'rb')
        try:
            # read the file, this function is expecting a binary file and will
            # read the file as unsigned chars
            byte = f.read(1)
            while byte != "":
                # put the byte into the return vector
                fileData = fileData + (byte,)
                byte = f.read(1)
        finally:
            f.close()
            
        return map(ord, fileData)
    
    def runIt(self, inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q):
        inputData = self.readBinaryFile(os.path.join(self.testFilesDir, inputFilename))
        expectedOutputData = self.readBinaryFile(os.path.join(self.testFilesDir, outputFilename))
                
        # define the required components
        self.variable_cc_def_fecapi_tpc_encoder_def_0 = \
            variable_cc_def_fecapi_tpc_encoder_def_0 = \
                map( (lambda a: fec.tpc_make_encoder((rowPoly), (colPoly), kRow, kCol, B, Q)), range(0,1) ); 
        self.encoder_interface_0 = \
            extended_encoder_interface(encoder_obj_list=variable_cc_def_fecapi_tpc_encoder_def_0, 
                                       threading='capillary', 
                                       puncpat='11', )
        
        # setup connections of flowgraph
        self.blocks_vector_source_x_0 = blocks.vector_source_b(inputData, False, 1, [])
        self.blocks_vector_sink_x_0 = blocks.vector_sink_f(1)
        
        self.tb.connect((self.blocks_vector_source_x_0, 0), (self.encoder_interface_0, 0))
        self.tb.connect((self.encoder_interface_0, 0), (self.blocks_vector_sink_x_0, 0))
        
        # run the block
        self.tb.run()
        
        # check output versus expectedOutputData
        actualOutputData = self.blocks_vector_sink_x_0.data()
        
        outputLen = len(expectedOutputData)
        self.assertFloatTuplesAlmostEqual(expectedOutputData, actualOutputData, outputLen)
        
    
    def test_001_tpc_encoder(self):
        inputFilename = 'test_1_input.bin'
        outputFilename = 'test_1_output.bin'
                
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_002_tpc_encoder(self):
        inputFilename = 'test_2_input.bin'
        outputFilename = 'test_2_output.bin'
        
        rowPoly = [3]
        colPoly = [123]
        kRow = 3
        kCol = 18
        B = 0
        Q = 6
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_003_tpc_encoder(self):
        inputFilename = 'test_3_input.bin'
        outputFilename = 'test_3_output.bin'
    
        rowPoly = [3]
        colPoly = [3]
        kRow = 9
        kCol = 9
        B = 4
        Q = 5
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_004_tpc_encoder(self):
        inputFilename = 'test_4_input.bin'
        outputFilename = 'test_4_output.bin'
        
        rowPoly = [3]
        colPoly = [43]
        kRow = 17
        kCol = 6
        B = 6
        Q = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_005_tpc_encoder(self):
        inputFilename = 'test_5_input.bin'
        outputFilename = 'test_5_output.bin'
        
        rowPoly = [3]
        colPoly = [3]
        kRow = 13
        kCol = 13
        B = 4
        Q = 5
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_006_tpc_encoder(self):
        inputFilename = 'test_6_input.bin'
        outputFilename = 'test_6_output.bin'
        
        rowPoly = [3]
        colPoly = [163]
        kRow = 5
        kCol = 41
        B = 0
        Q = 5
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_007_tpc_encoder(self):
        inputFilename = 'test_7_input.bin'
        outputFilename = 'test_7_output.bin'
        
        rowPoly = [123]
        colPoly = [43]
        kRow = 22
        kCol = 9
        B = 8
        Q = 6
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_008_tpc_encoder(self):
        inputFilename = 'test_8_input.bin'
        outputFilename = 'test_8_output.bin'
        
        rowPoly = [123]
        colPoly = [3]
        kRow = 26
        kCol = 11
        B = 0
        Q = 6
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_009_tpc_encoder(self):
        inputFilename = 'test_9_input.bin'
        outputFilename = 'test_9_output.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 16
        kCol = 16
        B = 4
        Q = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
    def test_010_tpc_encoder(self):
        inputFilename = 'test_10_input.bin'
        outputFilename = 'test_10_output.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 18
        kCol = 18
        B = 0
        Q = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q)
    
if __name__=='__main__':
    gr_unittest.run(qa_tpc_encoder)
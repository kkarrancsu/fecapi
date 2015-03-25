#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: TPC Encoder Test
# Generated: 
##################################################

from gnuradio import gr, gr_unittest
from gnuradio import blocks
from fec.extended_decoder_interface import extended_decoder_interface
import fec
import struct

import os

class qa_tpc_decoder_withnoise(gr_unittest.TestCase):
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
    
    def readFloatFile(self, filename):
        f = open(filename, 'rb')
        n = 288
        fileData = struct.unpack('f'*n, f.read(4*n))
        f.close()
        
        return fileData
    
    def runIt(self, decoderInputFilename, decoderOutputFilename, rowPoly, colPoly, kRow, kCol, B, Q, 
              numIter, decType):
        decoderInputLLR = self.readFloatFile(os.path.join(self.testFilesDir, decoderInputFilename))
        decoderExpectedOutput = self.readBinaryFile(os.path.join(self.testFilesDir, decoderOutputFilename))
        
        # define the required components
        self.variable_cc_def_fecapi_tpc_decoder_def_0 = \
            variable_cc_def_fecapi_tpc_decoder_def_0 = \
                map( (lambda a: fec.tpc_make_decoder((rowPoly), (colPoly), kRow, kCol, B, Q, numIter, decType)), range(0,1) ); 
        self.variable_decoder_interface_0 = \
            variable_decoder_interface_0 = \
                extended_decoder_interface(decoder_obj_list=variable_cc_def_fecapi_tpc_decoder_def_0, 
                                           threading='capillary', 
                                           ann=None, 
                                           puncpat='11', 
                                           integration_period=10000)
        
        # setup connections of flowgraph
        self.blocks_vector_source_x_0 = blocks.vector_source_f(decoderInputLLR, False, 1, [])
        self.blocks_vector_sink_x_0 = blocks.vector_sink_b(1)
        
        self.tb.connect((self.blocks_vector_source_x_0, 0), (self.variable_decoder_interface_0, 0))
        self.tb.connect((self.variable_decoder_interface_0, 0), (self.blocks_vector_sink_x_0, 0))
        
        # run the block
        self.tb.run()
        
        # check output versus expectedOutputData
        actualOutputData = self.blocks_vector_sink_x_0.data()
        actualOutputDataList = list(actualOutputData)
        actualOutputDataList_int = map(int, actualOutputDataList)
        
        print type(decoderExpectedOutput)
        print type(actualOutputDataList_int)
        
        print '******** DECODER EXPECTED OUTPUT *********'
        print decoderExpectedOutput
        print '******** DECODER ACTUAL OUTPUT ***********'
        print actualOutputDataList_int
        
        outputLen = len(decoderExpectedOutput)
        
        self.assertFloatTuplesAlmostEqual(decoderExpectedOutput, actualOutputDataList_int, outputLen)
        
    def test_004_tpc_decoder(self):
        print 'RUNNING NOISE TEST 4'
        inputFilename = 'snrtest_4_input.bin'
        outputFilename = 'snrtest_4_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
     
    def test_005_tpc_decoder(self):
        print 'RUNNING NOISE TEST 5'
        inputFilename = 'snrtest_5_input.bin'
        outputFilename = 'snrtest_5_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
     
    def test_006_tpc_decoder(self):
        print 'RUNNING NOISE TEST 6'
        inputFilename = 'snrtest_6_input.bin'
        outputFilename = 'snrtest_6_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
     
    def test_007_tpc_decoder(self):
        print 'RUNNING NOISE TEST 7'
        inputFilename = 'snrtest_7_input.bin'
        outputFilename = 'snrtest_7_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
     
    def test_008_tpc_decoder(self):
        print 'RUNNING NOISE TEST 8'
        inputFilename = 'snrtest_8_input.bin'
        outputFilename = 'snrtest_8_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
     
    def test_009_tpc_decoder(self):
        print 'RUNNING NOISE TEST 9'
        inputFilename = 'snrtest_9_input.bin'
        outputFilename = 'snrtest_9_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
     
    def test_010_tpc_decoder(self):
        print 'RUNNING NOISE TEST 10'
        inputFilename = 'snrtest_10_input.bin'
        outputFilename = 'snrtest_10_output.bin'
         
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 2
         
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
if __name__=='__main__':
    gr_unittest.run(qa_tpc_decoder_withnoise)
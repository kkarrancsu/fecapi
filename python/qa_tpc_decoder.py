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

import os

class qa_tpc_decoder(gr_unittest.TestCase):
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
    
    def runIt(self, decoderInputFilename, decoderOutputFilename, rowPoly, colPoly, kRow, kCol, B, Q, 
              numIter, decType):
        decoderInputBits = self.readBinaryFile(os.path.join(self.testFilesDir, decoderInputFilename))
        decoderExpectedOutput = self.readBinaryFile(os.path.join(self.testFilesDir, decoderOutputFilename))
        
        # convert decoderInputBits into a "modulated" BPSK signal
        decoderInputSignal = ()
        for decoderInputBit in decoderInputBits:
            sigVal = 2*decoderInputBit-1
            decoderInputSignal = decoderInputSignal + (sigVal,)
        
        # define the required components

        self.variable_cc_def_fecapi_tpc_decoder_def_0 = \
            variable_cc_def_fecapi_tpc_decoder_def_0 = \
                map( (lambda a: fec.tpc_make_decoder((rowPoly), (colPoly), kRow, kCol, B, Q, numIter, 0)), range(0,1) ); 
        self.variable_decoder_interface_0 = \
            variable_decoder_interface_0 = \
                extended_decoder_interface(decoder_obj_list=variable_cc_def_fecapi_tpc_decoder_def_0, 
                                           threading='capillary', 
                                           ann=None, 
                                           puncpat='11', 
                                           integration_period=10000)
        
        # setup connections of flowgraph
        self.blocks_vector_source_x_0 = blocks.vector_source_f(decoderInputSignal, False, 1, [])
        self.blocks_vector_sink_x_0 = blocks.vector_sink_b(1)
        
        self.tb.connect((self.blocks_vector_source_x_0, 0), (self.variable_decoder_interface_0, 0))
        self.tb.connect((self.variable_decoder_interface_0, 0), (self.blocks_vector_sink_x_0, 0))
        
        # run the block
        self.tb.run()
        
        # check output versus expectedOutputData
        actualOutputData = self.blocks_vector_sink_x_0.data()
        
        outputLen = len(decoderExpectedOutput)
        
        self.assertFloatTuplesAlmostEqual(decoderExpectedOutput, actualOutputData, outputLen)
        
    
    def test_001_tpc_decoder(self):
        inputFilename = 'test_1_output.bin'
        outputFilename = 'test_1_input.bin'
        
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_002_tpc_decoder(self):
        inputFilename = 'test_1_output.bin'
        outputFilename = 'test_1_input.bin'
        
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_003_tpc_decoder(self):
        inputFilename = 'test_1_output.bin'
        outputFilename = 'test_1_input.bin'
        
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
    
    def test_004_tpc_decoder(self):
        inputFilename = 'test_1_output.bin'
        outputFilename = 'test_1_input.bin'
        
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_005_tpc_decoder(self):
        inputFilename = 'test_1_output.bin'
        outputFilename = 'test_1_input.bin'
        
        # the definitions below MUST match the octave test script
        rowPoly = [3]
        colPoly = [43]
        kRow = 26
        kCol = 6
        B = 9
        Q = 3
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    
    def test_006_tpc_decoder(self):
        inputFilename = 'test_2_output.bin'
        outputFilename = 'test_2_input.bin'
        
        rowPoly = [3]
        colPoly = [123]
        kRow = 3
        kCol = 18
        B = 0
        Q = 6
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_007_tpc_decoder(self):
        inputFilename = 'test_2_output.bin'
        outputFilename = 'test_2_input.bin'
        
        rowPoly = [3]
        colPoly = [123]
        kRow = 3
        kCol = 18
        B = 0
        Q = 6
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_008_tpc_decoder(self):
        inputFilename = 'test_2_output.bin'
        outputFilename = 'test_2_input.bin'
        
        rowPoly = [3]
        colPoly = [123]
        kRow = 3
        kCol = 18
        B = 0
        Q = 6
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_009_tpc_decoder(self):
        inputFilename = 'test_2_output.bin'
        outputFilename = 'test_2_input.bin'
        
        rowPoly = [3]
        colPoly = [123]
        kRow = 3
        kCol = 18
        B = 0
        Q = 6
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_010_tpc_decoder(self):
        inputFilename = 'test_2_output.bin'
        outputFilename = 'test_2_input.bin'
        
        rowPoly = [3]
        colPoly = [123]
        kRow = 3
        kCol = 18
        B = 0
        Q = 6
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_011_tpc_decoder(self):
        inputFilename = 'test_3_output.bin'
        outputFilename = 'test_3_input.bin'
    
        rowPoly = [3]
        colPoly = [3]
        kRow = 9
        kCol = 9
        B = 4
        Q = 5
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_012_tpc_decoder(self):
        inputFilename = 'test_3_output.bin'
        outputFilename = 'test_3_input.bin'
    
        rowPoly = [3]
        colPoly = [3]
        kRow = 9
        kCol = 9
        B = 4
        Q = 5
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_013_tpc_decoder(self):
        inputFilename = 'test_3_output.bin'
        outputFilename = 'test_3_input.bin'
    
        rowPoly = [3]
        colPoly = [3]
        kRow = 9
        kCol = 9
        B = 4
        Q = 5
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_014_tpc_decoder(self):
        inputFilename = 'test_3_output.bin'
        outputFilename = 'test_3_input.bin'
    
        rowPoly = [3]
        colPoly = [3]
        kRow = 9
        kCol = 9
        B = 4
        Q = 5
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_015_tpc_decoder(self):
        inputFilename = 'test_3_output.bin'
        outputFilename = 'test_3_input.bin'
    
        rowPoly = [3]
        colPoly = [3]
        kRow = 9
        kCol = 9
        B = 4
        Q = 5
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_016_tpc_decoder(self):
        inputFilename = 'test_4_output.bin'
        outputFilename = 'test_4_input.bin'
        
        rowPoly = [3]
        colPoly = [43]
        kRow = 17
        kCol = 6
        B = 6
        Q = 0
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_017_tpc_decoder(self):
        inputFilename = 'test_4_output.bin'
        outputFilename = 'test_4_input.bin'
        
        rowPoly = [3]
        colPoly = [43]
        kRow = 17
        kCol = 6
        B = 6
        Q = 0
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_018_tpc_decoder(self):
        inputFilename = 'test_4_output.bin'
        outputFilename = 'test_4_input.bin'
        
        rowPoly = [3]
        colPoly = [43]
        kRow = 17
        kCol = 6
        B = 6
        Q = 0
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_019_tpc_decoder(self):
        inputFilename = 'test_4_output.bin'
        outputFilename = 'test_4_input.bin'
        
        rowPoly = [3]
        colPoly = [43]
        kRow = 17
        kCol = 6
        B = 6
        Q = 0
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_020_tpc_decoder(self):
        inputFilename = 'test_4_output.bin'
        outputFilename = 'test_4_input.bin'
        
        rowPoly = [3]
        colPoly = [43]
        kRow = 17
        kCol = 6
        B = 6
        Q = 0
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_021_tpc_decoder(self):
        inputFilename = 'test_5_output.bin'
        outputFilename = 'test_5_input.bin'
        
        
        rowPoly = [3]
        colPoly = [3]
        kRow = 13
        kCol = 13
        B = 4
        Q = 5
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_022_tpc_decoder(self):
        inputFilename = 'test_5_output.bin'
        outputFilename = 'test_5_input.bin'
        
        
        rowPoly = [3]
        colPoly = [3]
        kRow = 13
        kCol = 13
        B = 4
        Q = 5
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_023_tpc_decoder(self):
        inputFilename = 'test_5_output.bin'
        outputFilename = 'test_5_input.bin'
        
        
        rowPoly = [3]
        colPoly = [3]
        kRow = 13
        kCol = 13
        B = 4
        Q = 5
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_024_tpc_decoder(self):
        inputFilename = 'test_5_output.bin'
        outputFilename = 'test_5_input.bin'
        
        
        rowPoly = [3]
        colPoly = [3]
        kRow = 13
        kCol = 13
        B = 4
        Q = 5
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_025_tpc_decoder(self):
        inputFilename = 'test_5_output.bin'
        outputFilename = 'test_5_input.bin'
        
        
        rowPoly = [3]
        colPoly = [3]
        kRow = 13
        kCol = 13
        B = 4
        Q = 5
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_026_tpc_decoder(self):
        inputFilename = 'test_6_output.bin'
        outputFilename = 'test_6_input.bin'
        
        rowPoly = [3]
        colPoly = [163]
        kRow = 5
        kCol = 41
        B = 0
        Q = 5
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_027_tpc_decoder(self):
        inputFilename = 'test_6_output.bin'
        outputFilename = 'test_6_input.bin'
        
        rowPoly = [3]
        colPoly = [163]
        kRow = 5
        kCol = 41
        B = 0
        Q = 5
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_028_tpc_decoder(self):
        inputFilename = 'test_6_output.bin'
        outputFilename = 'test_6_input.bin'
        
        rowPoly = [3]
        colPoly = [163]
        kRow = 5
        kCol = 41
        B = 0
        Q = 5
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_029_tpc_decoder(self):
        inputFilename = 'test_6_output.bin'
        outputFilename = 'test_6_input.bin'
        
        rowPoly = [3]
        colPoly = [163]
        kRow = 5
        kCol = 41
        B = 0
        Q = 5
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_030_tpc_decoder(self):
        inputFilename = 'test_6_output.bin'
        outputFilename = 'test_6_input.bin'
        
        rowPoly = [3]
        colPoly = [163]
        kRow = 5
        kCol = 41
        B = 0
        Q = 5
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_031_tpc_decoder(self):
        inputFilename = 'test_7_output.bin'
        outputFilename = 'test_7_input.bin'
        
        rowPoly = [123]
        colPoly = [43]
        kRow = 22
        kCol = 9
        B = 8
        Q = 6
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_032_tpc_decoder(self):
        inputFilename = 'test_7_output.bin'
        outputFilename = 'test_7_input.bin'
        
        rowPoly = [123]
        colPoly = [43]
        kRow = 22
        kCol = 9
        B = 8
        Q = 6
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_033_tpc_decoder(self):
        inputFilename = 'test_7_output.bin'
        outputFilename = 'test_7_input.bin'
        
        rowPoly = [123]
        colPoly = [43]
        kRow = 22
        kCol = 9
        B = 8
        Q = 6
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_034_tpc_decoder(self):
        inputFilename = 'test_7_output.bin'
        outputFilename = 'test_7_input.bin'
        
        rowPoly = [123]
        colPoly = [43]
        kRow = 22
        kCol = 9
        B = 8
        Q = 6
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_035_tpc_decoder(self):
        inputFilename = 'test_7_output.bin'
        outputFilename = 'test_7_input.bin'
        
        rowPoly = [123]
        colPoly = [43]
        kRow = 22
        kCol = 9
        B = 8
        Q = 6
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_036_tpc_decoder(self):
        inputFilename = 'test_8_output.bin'
        outputFilename = 'test_8_input.bin'
        
        rowPoly = [123]
        colPoly = [3]
        kRow = 26
        kCol = 11
        B = 0
        Q = 6
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_037_tpc_decoder(self):
        inputFilename = 'test_8_output.bin'
        outputFilename = 'test_8_input.bin'
        
        rowPoly = [123]
        colPoly = [3]
        kRow = 26
        kCol = 11
        B = 0
        Q = 6
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_038_tpc_decoder(self):
        inputFilename = 'test_8_output.bin'
        outputFilename = 'test_8_input.bin'
        
        rowPoly = [123]
        colPoly = [3]
        kRow = 26
        kCol = 11
        B = 0
        Q = 6
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_039_tpc_decoder(self):
        inputFilename = 'test_8_output.bin'
        outputFilename = 'test_8_input.bin'
        
        rowPoly = [123]
        colPoly = [3]
        kRow = 26
        kCol = 11
        B = 0
        Q = 6
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_040_tpc_decoder(self):
        inputFilename = 'test_8_output.bin'
        outputFilename = 'test_8_input.bin'
        
        rowPoly = [123]
        colPoly = [3]
        kRow = 26
        kCol = 11
        B = 0
        Q = 6
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_041_tpc_decoder(self):
        inputFilename = 'test_9_output.bin'
        outputFilename = 'test_9_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 16
        kCol = 16
        B = 4
        Q = 4
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_042_tpc_encoder(self):
        inputFilename = 'test_9_output.bin'
        outputFilename = 'test_9_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 16
        kCol = 16
        B = 4
        Q = 4
        numIters = 6
        decoderType = 1
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_043_tpc_decoder(self):
        inputFilename = 'test_9_output.bin'
        outputFilename = 'test_9_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 16
        kCol = 16
        B = 4
        Q = 4
        numIters = 6
        decoderType = 2
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_044_tpc_decoder(self):
        inputFilename = 'test_9_output.bin'
        outputFilename = 'test_9_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 16
        kCol = 16
        B = 4
        Q = 4
        numIters = 6
        decoderType = 3
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_045_tpc_decoder(self):
        inputFilename = 'test_9_output.bin'
        outputFilename = 'test_9_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 16
        kCol = 16
        B = 4
        Q = 4
        numIters = 6
        decoderType = 4
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
    
    def test_046_tpc_decoder(self):
        inputFilename = 'test_10_output.bin'
        outputFilename = 'test_10_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 18
        kCol = 18
        B = 0
        Q = 4
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_047_tpc_decoder(self):
        inputFilename = 'test_10_output.bin'
        outputFilename = 'test_10_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 18
        kCol = 18
        B = 0
        Q = 4
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_048_tpc_decoder(self):
        inputFilename = 'test_10_output.bin'
        outputFilename = 'test_10_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 18
        kCol = 18
        B = 0
        Q = 4
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_049_tpc_decoder(self):
        inputFilename = 'test_10_output.bin'
        outputFilename = 'test_10_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 18
        kCol = 18
        B = 0
        Q = 4
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
    def test_050_tpc_decoder(self):
        inputFilename = 'test_10_output.bin'
        outputFilename = 'test_10_input.bin'
        
        rowPoly = [123]
        colPoly = [123]
        kRow = 18
        kCol = 18
        B = 0
        Q = 4
        numIters = 6
        decoderType = 0
        
        self.runIt(inputFilename, outputFilename, rowPoly, colPoly, kRow, kCol, B, Q, numIters, decoderType)
        
if __name__=='__main__':
    gr_unittest.run(qa_tpc_decoder)
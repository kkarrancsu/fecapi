#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Mon Dec 16 15:55:52 2013
##################################################

from PyQt4 import Qt
from fec.extended_decoder_interface import extended_decoder_interface
from fec.extended_encoder_interface import extended_encoder_interface
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import fec
import numpy
import sip
import sys

class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Top Block")
        try:
             self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
             pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())


        ##################################################
        # Variables
        ##################################################
        None
        
        
        self.variable_cc_def_fecapi_encoder_def_0 = variable_cc_def_fecapi_encoder_def_0 = map( (lambda a: fec.cc_make_encoder(2048, 7, 2, ([79,109]), 0, -1,  False, False, False, True )), range(0,1) ); 
        
        
        self.variable_cc_def_fecapi_decoder_def_0 = variable_cc_def_fecapi_decoder_def_0 = map( (lambda a: fec.cc_make_decoder(2048, 7, 2, ([79,109]), 0, -1,  False, False, False, True )), range(0,1) ); 
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.variable_decoder_interface_0 = variable_decoder_interface_0 = extended_decoder_interface(decoder_obj_list=variable_cc_def_fecapi_decoder_def_0, threading='capillary', ann=None, puncpat='11', integration_period=10000)
        self.qtgui_time_sink_x_1 = qtgui.time_sink_f(
        	1024, #size
        	samp_rate, #samp_rate
        	"QT GUI Plot", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_1.set_update_time(0.10)
        self.qtgui_time_sink_x_1.set_y_axis(-1, 1)
        self.qtgui_time_sink_x_1.enable_tags(-1, True)
        self.qtgui_time_sink_x_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self._qtgui_time_sink_x_1_win = sip.wrapinstance(self.qtgui_time_sink_x_1.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_1_win)
        self.encoder_interface_0 = extended_encoder_interface(encoder_obj_list=variable_cc_def_fecapi_encoder_def_0, threading='capillary', puncpat='11', )
        self.blocks_uchar_to_float_0 = blocks.uchar_to_float()
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 2, 4096)), False)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_random_source_x_0, 0), (self.encoder_interface_0, 0))
        self.connect((self.encoder_interface_0, 0), (self.variable_decoder_interface_0, 0))
        self.connect((self.variable_decoder_interface_0, 0), (self.blocks_uchar_to_float_0, 0))
        self.connect((self.blocks_uchar_to_float_0, 0), (self.qtgui_time_sink_x_1, 0))


# QT sink close method reimplementation
    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_variable_decoder_interface_0(self):
        return self.variable_decoder_interface_0

    def set_variable_decoder_interface_0(self, variable_decoder_interface_0):
        self.variable_decoder_interface_0 = variable_decoder_interface_0

    def get_variable_cc_def_fecapi_encoder_def_0(self):
        return self.variable_cc_def_fecapi_encoder_def_0

    def set_variable_cc_def_fecapi_encoder_def_0(self, variable_cc_def_fecapi_encoder_def_0):
        self.variable_cc_def_fecapi_encoder_def_0 = variable_cc_def_fecapi_encoder_def_0

    def get_variable_cc_def_fecapi_decoder_def_0(self):
        return self.variable_cc_def_fecapi_decoder_def_0

    def set_variable_cc_def_fecapi_decoder_def_0(self, variable_cc_def_fecapi_decoder_def_0):
        self.variable_cc_def_fecapi_decoder_def_0 = variable_cc_def_fecapi_decoder_def_0

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_time_sink_x_1.set_samp_rate(self.samp_rate)

if __name__ == '__main__':
    import ctypes
    import os
    if os.name == 'posix':
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    qapp = Qt.QApplication(sys.argv)
    tb = top_block()
    tb.start()
    tb.show()
    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()
    tb = None #to clean up Qt widgets


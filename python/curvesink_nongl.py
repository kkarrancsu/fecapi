#!/usr/bin/env python
#
# Copyright 2003,2004,2005,2006,2007,2009,2010 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#  that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, writ%e to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gru, blocks
from gnuradio.fft import window
from gnuradio.wxgui import stdgui2
import wx
from gnuradio.wxgui import plot
import numpy
import math    

COLOR_LIST = ['BLUE', 'RED', 'GREEN', 'BLACK', 'SLATEGREY', 'POWDERBLUE', 'ORANGE', 'PALEGREEN', 'VIOLET', 'BROWN']
DIV_LEVELS = (1, 2, 5, 10, 20)
default_curvesink_size = (640,640)

class curve_sink_base(object):
    def __init__(self, input_is_real=True, 
                 y_per_div=1, y_divs=8, ref_level=50,
                 title='', x_units='', y_units=''):

        # initialize common attributes
        self.x_units=x_units
        self.y_units=y_units
        self.y_per_div=y_per_div
        self.y_divs = y_divs
        self.ref_level = ref_level
        self.title = title
        self.input_is_real = input_is_real
        self.msgq = gr.msg_queue(2)         # queue that holds a maximum of 2 messages

    def set_y_per_div(self, y_per_div):
        self.y_per_div = y_per_div

    def set_ref_level(self, ref_level):
        self.ref_level = ref_level

    

    #def _set_n(self):
     #   self.one_in_n.set_n(max(1, int(self.sample_rate/self.fft_size/self.fft_rate)))
        

class curve_sink_f(gr.hier_block2, curve_sink_base):
    def __init__(self, parent,
                 y_per_div=1, y_divs=8, ref_level=50, x_vals=numpy.arange(10), ninputs=1,
                 size=default_curvesink_size,
                 title='', x_units='', y_units='', legends=[], **kwargs):
        self.x_vals=x_vals;
        self.legends=legends
        gr.hier_block2.__init__(self, "curve_sink_f",
                                gr.io_signature(ninputs, ninputs, gr.sizeof_float),
                                gr.io_signature(0,0,0))

        curve_sink_base.__init__(self, input_is_real=True,
                                 y_per_div=y_per_div, y_divs=y_divs, ref_level=ref_level,
                                 title=title, x_units=x_units, y_units=y_units)
                               
        self.s2p = [];
        
        for i in range(0, ninputs):
            self.s2p.append(blocks.stream_to_vector(gr.sizeof_float, len(x_vals)))
        #self.one_in_n = gr.keep_one_in_n(gr.sizeof_float * self.fft_size,
         #                                max(1, int(self.sample_rate/self.fft_size/self.fft_rate)))
        self.interleave = blocks.interleave(gr.sizeof_float * len(x_vals));
        
        self.s2v = blocks.stream_to_vector(gr.sizeof_float * len(x_vals), ninputs);
        
        self.sink = blocks.message_sink(gr.sizeof_float * len(x_vals) * ninputs, self.msgq, True);
        
        for i in range(0, ninputs):
            self.connect((self, i), self.s2p[i], (self.interleave, i))
        self.connect(self.interleave, self.s2v, self.sink);

        self.win=curve_window(self, parent, size=size, x_units=self.x_units, y_units=self.y_units, ninputs=ninputs)



# ------------------------------------------------------------------------

myDATA_EVENT = wx.NewEventType()
EVT_DATA_EVENT = wx.PyEventBinder (myDATA_EVENT, 0)


class DataEvent(wx.PyEvent):
    def __init__(self, data, ninputs):
        wx.PyEvent.__init__(self)
        self.SetEventType (myDATA_EVENT)
        self.data = data
        self.ninputs = ninputs

    def Clone (self): 
        self.__class__ (self.GetId())


class input_watcher (gru.msgq_runner):
    def __init__ (self, msgq, fft_size, event_receiver, ninputs, **kwds):
        self.fft_size = fft_size
        self.event_receiver = event_receiver
        self.ninputs = ninputs
        gru.msgq_runner.__init__(self, msgq, self.handle_msg)
        
    def handle_msg(self, msg):
        itemsize = int(msg.arg1())
        nitems = int(msg.arg2())

        s = msg.to_string() # get the body of the msg as a string

        # There may be more than one FFT frame in the message.
        # If so, we take only the last one
        if nitems > 1:
            start = itemsize * (nitems - 1)
            s = s[start:start+itemsize]

        complex_data = numpy.fromstring (s, numpy.float32)
        de = DataEvent (complex_data, self.ninputs)
        wx.PostEvent (self.event_receiver, de)
        self.event_receiver.de = de
        del de
        
class control_panel(wx.Panel):
    
    class LabelText(wx.StaticText):    
        def __init__(self, window, label):
            wx.StaticText.__init__(self, window, -1, label)
            font = self.GetFont()
            font.SetWeight(wx.FONTWEIGHT_BOLD)
            font.SetUnderlined(True)
            self.SetFont(font)
    
    def __init__(self, parent):
        self.parent = parent
        wx.Panel.__init__(self, parent, -1, style=wx.SIMPLE_BORDER)    
        control_box = wx.BoxSizer(wx.VERTICAL)
        
        #checkboxes for average and peak hold
        control_box.AddStretchSpacer()
        control_box.Add(self.LabelText(self, 'Options'), 0, wx.ALIGN_CENTER)
        
        
        
       
        #radio buttons for div size
        control_box.AddStretchSpacer()
        control_box.Add(self.LabelText(self, 'Set Y units/div'), 0, wx.ALIGN_CENTER)
        radio_box = wx.BoxSizer(wx.VERTICAL)
        self.radio_buttons = list()
        for y_per_div in DIV_LEVELS:
            if y_per_div == 1:
                radio_button = wx.RadioButton(self, -1, "%d Y unit/div"%y_per_div)
            else:
                radio_button = wx.RadioButton(self, -1, "%d Y units/div"%y_per_div)
            radio_button.Bind(wx.EVT_RADIOBUTTON, self.on_radio_button_change)
            self.radio_buttons.append(radio_button)
            radio_box.Add(radio_button, 0, wx.ALIGN_LEFT)
        control_box.Add(radio_box, 0, wx.EXPAND)
        
        #ref lvl buttons
        control_box.AddStretchSpacer()
        control_box.Add(self.LabelText(self, 'Adj Ref Lvl'), 0, wx.ALIGN_CENTER)
        control_box.AddSpacer(2)
        button_box = wx.BoxSizer(wx.HORIZONTAL)        
        self.ref_plus_button = wx.Button(self, -1, '+', style=wx.BU_EXACTFIT)
        self.ref_plus_button.Bind(wx.EVT_BUTTON, parent.on_incr_ref_level)
        button_box.Add(self.ref_plus_button, 0, wx.ALIGN_CENTER)
        self.ref_minus_button = wx.Button(self, -1, ' - ', style=wx.BU_EXACTFIT)
        self.ref_minus_button.Bind(wx.EVT_BUTTON, parent.on_decr_ref_level)
        button_box.Add(self.ref_minus_button, 0, wx.ALIGN_CENTER)
        control_box.Add(button_box, 0, wx.ALIGN_CENTER)
        control_box.AddStretchSpacer()
        #set sizer
        self.SetSizerAndFit(control_box)
        #update
        self.update()
        
    def update(self):
        """
        Read the state of the fft plot settings and update the control panel.
        """
        #update checkboxes
        
        #update radio buttons    
        try:
            index = list(DIV_LEVELS).index(self.parent.curvesink.y_per_div)
            self.radio_buttons[index].SetValue(True)
        except: pass
        
    def on_radio_button_change(self, evt):
        selected_radio_button = filter(lambda rb: rb.GetValue(), self.radio_buttons)[0] 
        index = self.radio_buttons.index(selected_radio_button)
        self.parent.curvesink.set_y_per_div(DIV_LEVELS[index])
        if hasattr(self.parent, 'de'):
            wx.PostEvent(self.parent, self.parent.de);

class curve_window (wx.Panel):
    def __init__ (self, curvesink, parent, id = -1,
                  pos = wx.DefaultPosition, size = wx.DefaultSize,
                  style = wx.DEFAULT_FRAME_STYLE, name = "", x_units='', y_units='', ninputs=1):
        
        self.x_units=x_units
        self.y_units=y_units
        self.curvesink = curvesink
        #init panel and plot 
        wx.Panel.__init__(self, parent, -1)                  
        self.plot = plot.PlotCanvas(self, id, pos, size, style, name)       
        #setup the box with plot and controls
        self.control_panel = control_panel(self)
        main_box = wx.BoxSizer (wx.HORIZONTAL)
        main_box.Add (self.plot, 1, wx.EXPAND)
        main_box.Add (self.control_panel, 0, wx.EXPAND)
        self.SetSizerAndFit(main_box)
        
        

        
        
        self.plot.SetEnableGrid (True)
        if ninputs > 1:
            self.plot.SetEnableLegend(True)
        # self.SetEnableZoom (True)
        # self.SetBackgroundColour ('black')
        
        self.build_popup_menu()
        self._format = "%3.6f"

        EVT_DATA_EVENT (self, self.set_data)
        wx.EVT_CLOSE (self, self.on_close_window)
        self.plot.Bind(wx.EVT_RIGHT_UP, self.on_right_click)
        self.plot.Bind(wx.EVT_MOTION, self.evt_motion)
        
        self.input_watcher = input_watcher(curvesink.msgq, len(curvesink.x_vals), self, ninputs)

        
    def on_close_window (self, event):
        print "fft_window:on_close_window"
        self.keep_running = False


    def set_data (self, evt):
        dB = evt.data
        num_curves = evt.ninputs
        L = len (dB) / num_curves
        

        self._points = [];
        for i in range(0, num_curves):
            self._points.append(numpy.zeros((L, 2), numpy.float64))
        for i in range(0, num_curves):
            self._points[i][:,0] = self.curvesink.x_vals
            self._points[i][:,1] = dB[i * L: (i * L) +L]

        

        lines = [];
        for i in range(0, num_curves):
            lines.append(plot.PolyLine (self._points[i], colour=COLOR_LIST[i%num_curves], legend=self.curvesink.legends[i]) )
        
        graphics = plot.PlotGraphics (lines,
                                      title=self.curvesink.title,
                                      xLabel = self.x_units, yLabel = self.y_units)
        x_range = self.curvesink.x_vals[0], self.curvesink.x_vals[-1]
        ymax = self.curvesink.ref_level
        ymin = self.curvesink.ref_level - self.curvesink.y_per_div * self.curvesink.y_divs
        y_range = ymin, ymax
        self.plot.Draw (graphics, xAxis=x_range, yAxis=y_range, step=self.curvesink.y_per_div)        

    

    def on_incr_ref_level(self, evt):
        # print "on_incr_ref_level"
        self.curvesink.set_ref_level(self.curvesink.ref_level
                                   + self.curvesink.y_per_div)
        if hasattr(self, 'de'):
            wx.PostEvent(self, self.de);

    def on_decr_ref_level(self, evt):
        # print "on_decr_ref_level"
        self.curvesink.set_ref_level(self.curvesink.ref_level
                                   - self.curvesink.y_per_div)
        if hasattr(self, 'de'):
            wx.PostEvent(self, self.de);

    def on_incr_y_per_div(self, evt):
        # print "on_incr_y_per_div"
        self.curvesink.set_y_per_div(next_up(self.curvesink.y_per_div, DIV_LEVELS))
        self.control_panel.update()
        if hasattr(self, 'de'):
            wx.PostEvent(self, self.de);

    def on_decr_y_per_div(self, evt):
        # print "on_decr_y_per_div"
        self.curvesink.set_y_per_div(next_down(self.curvesink.y_per_div, DIV_LEVELS))
        self.control_panel.update()
        if hasattr(self, 'de'):
            wx.PostEvent(self, self.de);

    def on_y_per_div(self, evt):
        # print "on_y_per_div"
        Id = evt.GetId()
        if Id == self.id_y_per_div_1:
            self.curvesink.set_y_per_div(1)
        elif Id == self.id_y_per_div_2:
            self.curvesink.set_y_per_div(2)
        elif Id == self.id_y_per_div_5:
            self.curvesink.set_y_per_div(5)
        elif Id == self.id_y_per_div_10:
            self.curvesink.set_y_per_div(10)
        elif Id == self.id_y_per_div_20:
            self.curvesink.set_y_per_div(20)
        self.control_panel.update()
        if hasattr(self, 'de'):
            wx.PostEvent(self, self.de);

    def on_right_click(self, event):
        menu = self.popup_menu
        for id, pred in self.checkmarks.items():
            item = menu.FindItemById(id)
            item.Check(pred())
        self.plot.PopupMenu(menu, event.GetPosition())
        

    def evt_motion(self, event):
        if not hasattr(self, "_points"):
            return # Got here before first window data update
            
        # Clip to plotted values
        (ux, uy) = self.plot.GetXY(event)      # Scaled position
        x_vals = numpy.array(self._points[0][:,0])
        if ux < x_vals[0] or ux > x_vals[-1]:
            tip = self.GetToolTip()
            if tip:
                tip.Enable(False)
            return

        # Get nearest X value (is there a better way)?
        ind = numpy.argmin(numpy.abs(x_vals-ux))
        x_val = x_vals[ind]
        db_val = self._points[0][ind, 1]
        text = (self._format+" %s Y units=%3.3f") % (x_val, self.y_units, db_val)

        # Display the tooltip
        tip = wx.ToolTip(text)
        tip.Enable(True)
        tip.SetDelay(0)
        self.SetToolTip(tip)
        
    def build_popup_menu(self):
        self.id_incr_ref_level = wx.NewId()
        self.id_decr_ref_level = wx.NewId()
        self.id_incr_y_per_div = wx.NewId()
        self.id_decr_y_per_div = wx.NewId()
        self.id_y_per_div_1 = wx.NewId()
        self.id_y_per_div_2 = wx.NewId()
        self.id_y_per_div_5 = wx.NewId()
        self.id_y_per_div_10 = wx.NewId()
        self.id_y_per_div_20 = wx.NewId()
        
        self.plot.Bind(wx.EVT_MENU, self.on_incr_ref_level, id=self.id_incr_ref_level)
        self.plot.Bind(wx.EVT_MENU, self.on_decr_ref_level, id=self.id_decr_ref_level)
        self.plot.Bind(wx.EVT_MENU, self.on_incr_y_per_div, id=self.id_incr_y_per_div)
        self.plot.Bind(wx.EVT_MENU, self.on_decr_y_per_div, id=self.id_decr_y_per_div)
        self.plot.Bind(wx.EVT_MENU, self.on_y_per_div, id=self.id_y_per_div_1)
        self.plot.Bind(wx.EVT_MENU, self.on_y_per_div, id=self.id_y_per_div_2)
        self.plot.Bind(wx.EVT_MENU, self.on_y_per_div, id=self.id_y_per_div_5)
        self.plot.Bind(wx.EVT_MENU, self.on_y_per_div, id=self.id_y_per_div_10)
        self.plot.Bind(wx.EVT_MENU, self.on_y_per_div, id=self.id_y_per_div_20)
        
        # make a menu
        menu = wx.Menu()
        self.popup_menu = menu
        menu.Append(self.id_incr_ref_level, "Incr Ref Level")
        menu.Append(self.id_decr_ref_level, "Decr Ref Level")
        # menu.Append(self.id_incr_y_per_div, "Incr dB/div")
        # menu.Append(self.id_decr_y_per_div, "Decr dB/div")
        menu.AppendSeparator()
        # we'd use RadioItems for these, but they're not supported on Mac
        menu.AppendCheckItem(self.id_y_per_div_1, "1 Y unit/div")
        menu.AppendCheckItem(self.id_y_per_div_2, "2 Y units/div")
        menu.AppendCheckItem(self.id_y_per_div_5, "5 Y units/div")
        menu.AppendCheckItem(self.id_y_per_div_10, "10 Y units/div")
        menu.AppendCheckItem(self.id_y_per_div_20, "20 Y units/div")

        self.checkmarks = {
            self.id_y_per_div_1 : lambda : self.curvesink.y_per_div == 1,
            self.id_y_per_div_2 : lambda : self.curvesink.y_per_div == 2,
            self.id_y_per_div_5 : lambda : self.curvesink.y_per_div == 5,
            self.id_y_per_div_10 : lambda : self.curvesink.y_per_div == 10,
            self.id_y_per_div_20 : lambda : self.curvesink.y_per_div == 20,
            }


def next_up(v, seq):
    """
    Return the first item in seq that is > v.
    """
    for s in seq:
        if s > v:
            return s
    return v

def next_down(v, seq):
    """
    Return the last item in seq that is < v.
    """
    rseq = list(seq[:])
    rseq.reverse()

    for s in rseq:
        if s < v:
            return s
    return v


# ----------------------------------------------------------------
# Standalone test app
# ----------------------------------------------------------------

class test_app_block (stdgui2.std_top_block):
    def __init__(self, frame, panel, vbox, argv):
        stdgui2.std_top_block.__init__ (self, frame, panel, vbox, argv)

     

def main ():
    app = stdgui2.stdapp (test_app_block, "FFT Sink Test App")
    app.MainLoop ()

if __name__ == '__main__':
    main ()

/* -*- c++ -*- */
/*
 * Copyright 2006 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */



#include "ber_sink_b_impl.h"
#include <gnuradio/io_signature.h>
#include <libbertools.h>
#include <gnuradio/fft/fft.h>
#include <math.h>



fec_ber_sink_b_sptr
fec_make_ber_sink_b(std::vector<float> esnos, int curves, int berminerrors, float berLimit, std::vector<std::string> curvenames, QWidget *parent)
{
  return gnuradio::get_initial_sptr(new fec_ber_sink_b_impl(esnos, curves, berminerrors, berLimit, curvenames, parent));
}

fec_ber_sink_b_impl::fec_ber_sink_b_impl(std::vector<float> esnos, int curves, int berminerrors, float berLimit, std::vector<std::string> curvenames, QWidget *parent)
  : gr::block("fec_ber_sink_b",
	      gr::io_signature::make(curves * esnos.size() * 2, curves * esnos.size() * 2, sizeof(unsigned char)),
	      gr::io_signature::make(0, 0, 0)),
    d_berminerrors(berminerrors), 
    d_berLimit(berLimit), 
    d_parent(parent),
    d_nconnections(esnos.size()),
    d_last_time(0)
{
  d_main_gui = NULL;
  
  
  d_residbufs_real.reserve(curves);
  d_residbufs_imag.reserve(curves);
  d_total.reserve(curves * esnos.size());
  d_totalErrors.reserve(curves * esnos.size());
  
  for(int j= 0; j < curves; j++) {
    d_residbufs_real.push_back(gr::fft::malloc_double(esnos.size()));
    d_residbufs_imag.push_back(gr::fft::malloc_double(esnos.size()));
    for(int i = 0; i < d_nconnections; i++) {
    
      d_residbufs_real[j][i] = esnos[i];
      d_residbufs_imag[j][i] = 0.0;
      d_total.push_back(0);
      d_totalErrors.push_back(1);
    }
  }
  
  
  initialize();
  for(int j= 0; j < curves; j++) {
    set_line_width(j, 1);
    //35 unique styles supported
    set_line_style(j, (j%5) + 1);
    set_line_marker(j, (j%7));
    
  }
  if(curvenames.size() == curves) {
    for(int j = 0; j < curves; j++) {
      if (curvenames[j] != "") {
	set_line_label(j, curvenames[j]);
      }
    }
  }
}

fec_ber_sink_b_impl::~fec_ber_sink_b_impl() {
  if(!d_main_gui->isClosed()) {
    d_main_gui->close();
  }

  for(int i = 0; i < d_residbufs_real.size(); i++) {
    gr::fft::free(d_residbufs_real[i]);
    gr::fft::free(d_residbufs_imag[i]);
    
  }
}

bool
fec_ber_sink_b_impl::check_topology(int ninputs, int noutputs)
{
  return ninputs == d_residbufs_real.size() * d_nconnections * 2;
}

void
fec_ber_sink_b_impl::initialize()
{
  if(qApp != NULL) {
    d_qApplication = qApp;
  }
  else {
    int argc=0;
    char **argv = NULL;
    d_qApplication = new QApplication(argc, argv);
  }
  
  d_main_gui = new ConstellationDisplayForm(d_residbufs_real.size(), d_parent);

  d_main_gui->setNPoints(d_nconnections);
  d_main_gui->getPlot()->setAxisTitle(QwtPlot::yLeft, "LogScale BER");
  d_main_gui->getPlot()->setAxisTitle(QwtPlot::xBottom, "ESNO");
  // initialize update time to 10 times a second
  set_update_time(0.1);
}

void
fec_ber_sink_b_impl::exec_()
{
  d_qApplication->exec();
}

QWidget*
fec_ber_sink_b_impl::qwidget()
{
  return d_main_gui;
}

PyObject*
fec_ber_sink_b_impl::pyqwidget()
{
  PyObject *w = PyLong_FromVoidPtr((void*)d_main_gui);
  PyObject *retarg = Py_BuildValue("N", w);
  return retarg;
}

void
fec_ber_sink_b_impl::set_y_axis(double min, double max)
{
  d_main_gui->setYaxis(min, max);
}

void
fec_ber_sink_b_impl::set_x_axis(double min, double max)
{
  d_main_gui->setXaxis(min, max);
}

void
fec_ber_sink_b_impl::set_update_time(double t)
{
  //convert update time to ticks
  gr::high_res_timer_type tps = gr::high_res_timer_tps();
  d_update_time = t * tps;
  d_main_gui->setUpdateTime(t);
  d_last_time = 0;
}

void
fec_ber_sink_b_impl::set_title(const std::string &title)
{
  d_main_gui->setTitle(title.c_str());
}

void
fec_ber_sink_b_impl::set_line_label(int which, const std::string &label)
{
  d_main_gui->setLineLabel(which, label.c_str());
}

void
fec_ber_sink_b_impl::set_line_color(int which, const std::string &color)
{
  d_main_gui->setLineColor(which, color.c_str());
}

void
fec_ber_sink_b_impl::set_line_width(int which, int width)
{
  d_main_gui->setLineWidth(which, width);
}

void
fec_ber_sink_b_impl::set_line_style(int which, int style)
{
  d_main_gui->setLineStyle(which, (Qt::PenStyle)style);
}

void
fec_ber_sink_b_impl::set_line_marker(int which, int marker)
{
  d_main_gui->setLineMarker(which, (QwtSymbol::Style)marker);
}

void
fec_ber_sink_b_impl::set_line_alpha(int which, double alpha)
{
  d_main_gui->setMarkerAlpha(which, (int)(255.0*alpha));
}

void
fec_ber_sink_b_impl::set_size(int width, int height)
{
  d_main_gui->resize(QSize(width, height));
}

std::string
fec_ber_sink_b_impl::title()
{
  return d_main_gui->title().toStdString();
}

std::string
fec_ber_sink_b_impl::line_label(int which)
{
  return d_main_gui->lineLabel(which).toStdString();
}

std::string
fec_ber_sink_b_impl::line_color(int which)
{
  return d_main_gui->lineColor(which).toStdString();
}

int
fec_ber_sink_b_impl::line_width(int which)
{
  return d_main_gui->lineWidth(which);
}

int
fec_ber_sink_b_impl::line_style(int which)
{
  return d_main_gui->lineStyle(which);
}

int
fec_ber_sink_b_impl::line_marker(int which)
{
  return d_main_gui->lineMarker(which);
}

double
fec_ber_sink_b_impl::line_alpha(int which)
{
  return (double)(d_main_gui->markerAlpha(which))/255.0;
}

int
fec_ber_sink_b_impl::nsamps() const
{
  return d_nconnections;
}

void
fec_ber_sink_b_impl::enable_menu(bool en)
{
  d_main_gui->enableMenu(en);
}

void
fec_ber_sink_b_impl::enable_autoscale(bool en)
{
  d_main_gui->autoScale(en);
}





int
fec_ber_sink_b_impl::general_work (int noutput_items,
			 gr_vector_int& ninput_items,
			 gr_vector_const_void_star &input_items,
			 gr_vector_void_star &output_items)
{
  if(gr::high_res_timer_now() - d_last_time > d_update_time) {
    d_last_time = gr::high_res_timer_now();
    d_qApplication->postEvent(d_main_gui,
			      new ConstUpdateEvent(d_residbufs_real,
						   d_residbufs_imag,
						   d_nconnections));
    
  }
  
  //check stopping condition
  int done=0, maxed=0;
  for(int j = 0; j < d_residbufs_real.size(); ++j) {
    for(int i = 0; i < d_nconnections; ++i) {
    
      if (d_totalErrors[j * d_nconnections + i] >= d_berminerrors) {
	done++;
      }
      else if(log10(((double)d_berminerrors)/(d_total[j * d_nconnections + i] * 8.0)) < d_berLimit) {
	maxed++;
      }
    }
  }

  if (done+maxed == d_nconnections * d_residbufs_real.size()) {
    d_qApplication->postEvent(d_main_gui,
			      new ConstUpdateEvent(d_residbufs_real,
						   d_residbufs_imag,
						   d_nconnections));

    return -1;
  }
  
  /*for(int i = 0; i < d_nconnections; ++i) {
    printf("%f, ", d_residbufs_imag[0][i]);
  }
  printf("\n");
  for(int i = 0; i < d_nconnections; ++i) {
    printf("%f, ", d_residbufs_real[0][i]);
  }
  printf("\n");*/

  for(int i = 0; i < ninput_items.size(); i += 2) {
    
    
    
    if ((d_totalErrors[i >> 1] < d_berminerrors) && (log10(((double)d_berminerrors)/(d_total[i >> 1] * 8.0)) >= d_berLimit)) {
      
	int items = ninput_items[i] <= ninput_items[i+1] ? ninput_items[i] : ninput_items[i+1];

	    
	unsigned char *inBuffer0 = (unsigned char *)input_items[i];
	unsigned char *inBuffer1 = (unsigned char *)input_items[i+1];
    
    
    
    
	if(items > 0) {
      
	  d_totalErrors[i >> 1] += compBER(inBuffer0, inBuffer1, items);
	  d_total[i >> 1] += items;
	  
	  d_residbufs_imag[i/(d_nconnections * 2)][(i%(d_nconnections * 2)) >> 1] = log10(((double)d_totalErrors[i >> 1])/(d_total[i >> 1] * 8.0));
	  
	}
	consume(i, items);
	consume(i + 1, items);
    
	
	
	if(d_totalErrors[i >> 1] >= d_berminerrors) {
	  printf("    %u over %d\n", d_totalErrors[i >> 1], d_total[i >> 1] * 8);
      //outBuffer[0] = log10(((double)d_totalErrors)/(d_total * 8.0));
	}
	else if(log10(((double)d_berminerrors)/(d_total[i >> 1] * 8.0)) < d_berLimit) {
	  printf("crapout\n");
	  d_residbufs_imag[i/(d_nconnections * 2)][(i%(d_nconnections * 2)) >> 1] = d_berLimit;
	  d_totalErrors[i >> 1] = d_berminerrors + 1;
	}
	
      
    }
    else {
      consume(i, ninput_items[i]);
      consume(i+1, ninput_items[i+1]);
    }
  
  }

  return 0;
  
}



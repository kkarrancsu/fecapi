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
#ifndef INCLUDED_FEC_BER_SINK_B_IMPL_H
#define INCLUDED_FEC_BER_SINK_B_IMPL_H




#include <fec_api.h>
#include <ber_sink_b.h>
#include <gnuradio/high_res_timer.h>
#include <gnuradio/thread/thread.h>
#include <gnuradio/qtgui/constellationdisplayform.h>


    
class FEC_API fec_ber_sink_b_impl : public fec_ber_sink_b {
 private:
  friend fec_ber_sink_b_sptr fec_make_ber_sink_b(std::vector<float> esnos, int curves, int berminerrors, float berLimit, std::vector<std::string> curvenames, QWidget *parent);
  fec_ber_sink_b_impl(std::vector<float> esnos, int curves = 1, int berminerrors = 100, float berLimit = -7.0, std::vector<std::string> curvenames = std::vector<std::string>(), QWidget *parent=NULL);

  void initialize();
  
  gr::thread::mutex d_mutex;
  
  //int d_size;
  //std::string d_name;
  int d_nconnections;
  
  
  std::vector<double*> d_residbufs_real;
  std::vector<double*> d_residbufs_imag;
  
  
  QWidget *d_parent;
  ConstellationDisplayForm *d_main_gui;
  
  gr::high_res_timer_type d_update_time;
  gr::high_res_timer_type d_last_time;
  
  std::vector<int> d_totalErrors;
  int d_berminerrors;
  float d_berLimit;
  std::vector<int> d_total;
  
  
 public:
  
  ~fec_ber_sink_b_impl();
  
  bool check_topology(int ninputs, int noutputs);
  
  void exec_();
  QWidget*  qwidget();
  PyObject* pyqwidget();
  
  void set_y_axis(double min, double max);
  void set_x_axis(double min, double max);
  
  void set_update_time(double t);
  void set_title(const std::string &title);
  void set_line_label(int which, const std::string &label);
  void set_line_color(int which, const std::string &color);
  void set_line_width(int which, int width);
  void set_line_style(int which, int style);
  void set_line_marker(int which, int marker);

  void set_line_alpha(int which, double alpha);
  
  std::string title();
  std::string line_label(int which);
  std::string line_color(int which);
  int line_width(int which);
  int line_style(int which);
  int line_marker(int which);
  double line_alpha(int which);
  
  void set_size(int width, int height);
  
  int nsamps() const;
  void enable_menu(bool en);
  void enable_autoscale(bool en);

  
  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
  
  
};



#endif /*INCLUDED_FEC_BER_SINK_B_IMPL_H*/

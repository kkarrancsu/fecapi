# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

install(FILES
  fec_encoder.xml
  fec_encoder_async.xml
  fec_decoder_async.xml
  fec_decoder.xml
  fec_interleave.xml
  fec_deinterleave.xml
  wxgui_curvesink.xml
  bercurve_generate.py.xml
  extended_decoder_interface.xml
  extended_encoder_interface.xml
  variable_cc_decoder_def_list.xml
  variable_cc_encoder_def_list.xml
  tpc_encoder_def_list.xml
  tpc_decoder_def_list.xml
  ldpc_encoder_def_list.xml
  ldpc_decoder_def_list.xml
  new_bercurve_generate.xml
  qt_bercurve_sink.xml
  DESTINATION share/gnuradio/grc/blocks
)



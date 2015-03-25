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

########################################################################
# Include python install macros
########################################################################
include(GrPython)
if(NOT PYTHONINTERP_FOUND)
    return()
endif()

########################################################################
# Install python sources
########################################################################
GR_PYTHON_INSTALL(
    FILES
    curvesink.py
    curvesink_nongl.py
    __init__.py
    bercurve_generate.py
    ber_generator.py
    threaded_decoder.py
    capillary_threaded_decoder.py
    extended_decoder_interface.py
    threaded_encoder.py
    capillary_threaded_encoder.py
    extended_encoder_interface.py
    bitflip.py
    fec_test.py
    new_bercurve_generate.py
    DESTINATION ${GR_PYTHON_DIR}/fec
)

########################################################################
# Handle the unit tests
########################################################################
include(GrTest)

set(GR_TEST_PYTHON_DIRS ${CMAKE_BINARY_DIR}/swig)
GR_ADD_TEST(qa_tpc_encoder ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_tpc_encoder.py)
GR_ADD_TEST(qa_tpc_decoder ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_tpc_decoder.py)
GR_ADD_TEST(qa_tpc_encode_decode ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_tpc_encode_decode.py)
GR_ADD_TEST(qa_tpc_decoder_withnoise ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_tpc_decoder_withnoise.py)
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
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX
include(GrPython)
GR_PYTHON_CHECK_MODULE("PyQt4" PyQt4 True PYQT4_FOUND)


add_library(fec SHARED
    libbertools.cc
    fec_random_gen_b.cc
    fec_encoder.cc
    fec_encoder_async.cc
    fec_decoder_async.cc
    fec_gaussnoise_ff.cc
    fec_decoder.cc
    fec_ber_bb.cc
    fec_interleave.cc
    fec_deinterleave.cc
    cc_decoder.cc
    cc_encoder.cc
    tpc_common.cc
    tpc_encoder.cc
    tpc_decoder.cc
    fec_corr_bb.cc
    fec_reinflate_bb.cc
    fec_puncture_ff.cc
    ber_sink_b_impl.cc
    ldpc_encoder.cc
    ldpc_decoder.cc
)

message("${GNURADIO_QTGUI_LIBRARIES}")
message("${QT_LIBRARIES}")

target_link_libraries(fec
    ${Boost_LIBRARIES}
    ${VOLK_LIBRARIES}
    ${QT_LIBRARIES}
    ${QWT_LIBRARIES}
    ${GNURADIO_RUNTIME_LIBRARIES}
    ${GNURADIO_QTGUI_LIBRARIES}
    ${GNURADIO_FFT_LIBRARIES}
    ${GNURADIO_LDPC_LIBRARIES}
    volk_fecapi
)
set_target_properties(fec PROPERTIES DEFINE_SYMBOL "fec_EXPORTS")


########################################################################
# Install info files for Python
########################################################################
install(FILES
  DESTINATION ${GR_PYTHON_DIR}/fec
)


########################################################################
# Install built library files
########################################################################
install(TARGETS fec
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

include(GrTest)
set(GR_TEST_TARGET_DEPS fec)
#turn each test cpp file into an executable with an int main(t) function
add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)


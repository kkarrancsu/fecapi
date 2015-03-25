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
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(fec CXX C)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "RelWithDebInfo")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")


configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/CMakeUninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/Modules/CMakeUninstall.cmake"
  @ONLY
)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/Modules/CMakeUninstall.cmake"
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/share/gnuradio/cmake/Modules)

########################################################################
# Compiler specific setup
########################################################################
if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    add_definitions(-fvisibility=hidden)
endif()



########################################################################
# Find boost
########################################################################
if(UNIX AND EXISTS "/usr/lib64")
    list(APPEND BOOST_LIBRARYDIR "/usr/lib64") #fedora 64-bit fix
endif(UNIX AND EXISTS "/usr/lib64")
set(Boost_ADDITIONAL_VERSIONS
    "1.35.0" "1.35" "1.36.0" "1.36" "1.37.0" "1.37" "1.38.0" "1.38" "1.39.0" "1.39"
    "1.40.0" "1.40" "1.41.0" "1.41" "1.42.0" "1.42" "1.43.0" "1.43" "1.44.0" "1.44"
    "1.45.0" "1.45" "1.46.0" "1.46" "1.47.0" "1.47" "1.48.0" "1.48" "1.49.0" "1.49"
    "1.50.0" "1.50" "1.51.0" "1.51" "1.52.0" "1.52" "1.53.0" "1.53" "1.54.0" "1.54"
    "1.55.0" "1.55" "1.56.0" "1.56" "1.57.0" "1.57" "1.58.0" "1.58" "1.59.0" "1.59"
    "1.60.0" "1.60" "1.61.0" "1.61" "1.62.0" "1.62" "1.63.0" "1.63" "1.64.0" "1.64"
    "1.65.0" "1.65" "1.66.0" "1.66" "1.67.0" "1.67" "1.68.0" "1.68" "1.69.0" "1.69"
)

IF(NOT DEFINED BOOST_ROOT)
    SET(BOOST_ROOT "")
ENDIF()
SET(BOOST_ROOT ${BOOST_ROOT} CACHE STRING "Modify search path for Boost components")

#after caching user-defined value, make sure to add the install prefix

IF("${BOOST_ROOT}" STREQUAL "")
    message("-- Looking into CMAKE_INSTALL_PREFIX for BOOST")
    SET(BOOST_ROOT ${CMAKE_INSTALL_PREFIX})
ENDIF()


set(BOOST_REQUIRED_COMPONENTS
    system
    thread
    )

    find_package(Boost "1.35" COMPONENTS ${BOOST_REQUIRED_COMPONENTS})


if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost required to compile fec")
endif()






########################################################################
# Find gnuradio build dependencies
########################################################################

set(GR_REQUIRED_COMPONENTS RUNTIME QTGUI FFT)
find_package(Gnuradio)
find_package(GnuradioLdpc)
find_package(Volk)

find_package(Qt4 4.2.0 COMPONENTS QtCore QtGui)

find_package(Qwt)

find_package(PythonLibs)



if(NOT GNURADIO_RUNTIME_FOUND)
    message(FATAL_ERROR "GnuRadio Runtime required to compile fec")
endif()

if(NOT VOLK_FOUND)
    message(FATAL_ERROR "GnuRadio Volk required to compile fec")
endif()



include(GrSetupQt4)

########################################################################
# Setup the include and linker paths
########################################################################
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/volk_fecapi/include
    ${CMAKE_SOURCE_DIR}/volk_fecapi/include
    ${Boost_INCLUDE_DIRS}
    ${GNURADIO_RUNTIME_INCLUDE_DIRS}
    ${VOLK_INCLUDE_DIRS}
    ${PMT_INCLUDE_DIRS}
    ${QT_INCLUDE_DIRS}
    ${QWT_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${GNURADIO_QTGUI_INCLUDE_DIRS}
    ${GNURADIO_FFT_INCLUDE_DIRS}
    ${GNURADIO_LDPC_INCLUDE_DIRS}
)

link_directories(
    ${Boost_LIBRARY_DIRS}
    ${GNURADIO_RUNTIME_LIBRARY_DIRS}
    ${VOLK_LIBRARY_DIRS}
    ${QT_LIBRARY_DIRS}
    ${QWT_LIBRARY_DIRS}
    ${PYTHON_LIBRARY_DIRS}
    ${GNURADIO_QTGUI_LIBRARY_DIRS}
    ${GNURADIO_FFT_LIBRARY_DIRS}
    ${GNURADIO_LDPC_LIBRARY_DIRS}
)



########################################################################
# Add subdirectories
########################################################################
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(swig)
add_subdirectory(python)
add_subdirectory(grc)
add_subdirectory(apps)
add_subdirectory(volk_fecapi)

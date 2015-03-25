

FIND_PATH(
    VOLK_FECAPI_INCLUDE_DIRS
    NAMES volk_fecapi.h 
    HINTS $ENV{VOLK_FECAPI_DIR}/include/volk_fecapi
	      ${CMAKE_INSTALL_PREFIX}/include/volk_fecapi
    PATHS /usr/local/include/volk_fecapi
          /usr/include/volk_fecapi
)

FIND_LIBRARY(
    VOLK_FECAPI_LIBRARIES
    NAMES volk_fecapi
    HINTS $ENV{VOLK_FECAPI_DIR}/lib
	${CMAKE_INSTALL_PREFIX}/lib
	${CMAKE_INSTALL_PREFIX}/lib64
    PATHS /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VOLK_FECAPI DEFAULT_MSG VOLK_FECAPI_LIBRARIES VOLK_FECAPI_INCLUDE_DIRS)
MARK_AS_ADVANCED(VOLK_FECAPI_LIBRARIES VOLK_FECAPI_INCLUDE_DIRS)

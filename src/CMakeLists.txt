file(GLOB_RECURSE openfec_sources *)

option(OF_USE_REED_SOLOMON_CODEC "Enable Reed-Solomon 2_8 codec" ON)
option(OF_USE_REED_SOLOMON_2_M_CODEC "Enable Reed-Solomon 2_M codec" ON)
option(OF_USE_LDPC_STAIRCASE_CODEC "Enable LDPC-Staircase codec" ON)
option(OF_USE_2D_PARITY_MATRIX_CODEC "Enable 2d parity matrix codec" ON)
option(OF_USE_LDPC_FROM_FILE_CODEC "Enable ldpc_from_file codec" OFF)

option(ASSEMBLY_SSE_OPT "Enable SSE optimizations for XOR operations" OFF)

configure_file(lib_common/of_build_config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/lib_common/of_build_config.h)

# Use -DBUILD_STATIC_LIBS=ON to build static libraries instead of shared.
option(BUILD_STATIC_LIBS "Build the static library" OFF)

if(BUILD_STATIC_LIBS)
  add_library(openfec STATIC ${openfec_sources})
else(BUILD_STATIC_LIBS)
  add_library(openfec SHARED ${openfec_sources})
endif(BUILD_STATIC_LIBS)

# From: $cmake --help-property SOVERSION
#    For shared libraries VERSION and SOVERSION can be used to specify
#    the build version and api version respectively.
#
# Edit it as appropriate to be in line with the src/lib_common/of_openfec_api.c::more_about() version
#
set_target_properties(openfec PROPERTIES
  VERSION 1.4.2
  SOVERSION 1)

# Feel free to edit as appropriate the "target_link_libraries".
#
# Add the IL (DevIL) library if you want to have the possibility to
# produce H/G matrix images with LDPC codes.
# More precisely, we are relying on the DevIL library
# (http://openil.sourceforge.net/).
# Please install it on your machine before compiling the OpenFEC
# library if needed.
# Otherwise remove the IL library.

target_link_libraries(openfec m)
#target_link_libraries(openfec m IL)

#target_link_libraries(openfec pthread IL)
#target_link_libraries(openfec pthread)

install(TARGETS openfec DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/src/
    DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/openfec
    FILES_MATCHING PATTERN "*.h")

include(TestBigEndian)
test_big_endian(BIG_ENDIAN)
if(BIG_ENDIAN)
  target_compile_definitions(openfec PRIVATE OPENFEC_BIG_ENDIAN)
else(BIG_ENDIAN)
  target_compile_definitions(openfec PRIVATE OPENFEC_LITTLE_ENDIAN)
endif(BIG_ENDIAN)

#-----------------------------*-cmake-*----------------------------------------#
# file   src/VendorsChecks/test/CMakeLists.txt
# author Kelly Thompson <kgt@lanl.gov>
# date   2016 May 11
# brief  Instructions for building VendorsChecks/test level Makefile.
# note   Copyright (C) 2016-2019 Triad National Security, LLC.
#        All rights reserved.
#------------------------------------------------------------------------------#
project( VendorsChecks_test CXX )

# ---------------------------------------------------------------------------- #
# Build Unit tests
# ---------------------------------------------------------------------------- #

if( METIS_FOUND )
  add_scalar_tests(
    SOURCES "tstMetis.cc"
    DEPS    "Lib_dsxx;METIS::metis" )
endif()

if( TARGET ParMETIS::parmetis AND ${DRACO_C4} STREQUAL "MPI" )

    add_parallel_tests(
      SOURCES "tstParmetis.cc"
      DEPS    "Lib_c4;ParMETIS::parmetis"
      PE_LIST "3" )

   if ( TARGET SuperLU_DIST::superludist AND TARGET lapack AND NOT WIN32)

     add_parallel_tests(
       SOURCES "tstSuperludist.cc"
       DEPS    "Lib_c4;SuperLU_DIST::superludist;ParMETIS::parmetis;lapack"
       PE_LIST "4" )
     target_include_directories( Ut_VendorsChecks_tstSuperludist_exe
       PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}> )

   endif()

endif()

# ---------------------------------------------------------------------------- #
# end src/VendorsChecks/test/CMakeLists.txt
# ---------------------------------------------------------------------------- #


# a vanilla build for local fuzzing with libFuzzer
# CXX="ccache clang++-7" CXXFLAGS="-O3" cmake .. -Dbuild_tests=On -Doss_fuzz_mode=Off -Denable_libfuzzer=On -GNinja

# running afl, locally
# CXX="ccache afl-g++" CXXFLAGS="-O3" cmake .. -Dbuild_tests=On -Doss_fuzz_mode=Off -Denable_libfuzzer=Off -Dlink_with_main=On -GNinja

#this is roughly what it looks like when built through oss-fuzz:
#LIB_FUZZING_ENGINE=/usr/lib/llvm-7/lib/libFuzzer.a CXX=clang++-7 CXXFLAGS="-fsanitize=fuzzer-no-link,address" cmake .. -Dbuild_tests=On  -Doss_fuzz_mode=On -GNinja

cmake_minimum_required(VERSION 3.12.0)

project(libtorrent_fuzzers)

#link in a main which reads all files given as
#command line arguments and run them through the
#fuzzer. Great for reproducing or if using afl.
option(link_with_main "make fuzzers accept fil input" OFF)

#are we in oss-fuzz mode?
option(oss_fuzz_mode "oss fuzz mode" OFF)

# if we are not in oss fuzz mode, but want to use libFuzzer, we have to link
# in main with this flag. cmake configuration step can't handle having
# -fsanitize=fuzzer, that is why we have to add it here and not through the
# CXXFLAGS
option(enable_libfuzzer "add libfuzzer link flag" OFF)

if(oss_fuzz_mode)
 #this is how oss-fuzz passes the fuzzer engine
if(DEFINED ENV{LIB_FUZZING_ENGINE})
  set(engine $ENV{LIB_FUZZING_ENGINE})
  if(NOT EXISTS ${engine}) 
    message(FATAL_ERROR "fuzzing engine ${engine} not found")
  endif()
else()
  message(FATAL_ERROR "In oss fuzz mode, but environment variable LIB_FUZZING_ENGINE is not set")
endif()
if(enable_libfuzzer)
  message(FATAL_ERROR "Don't use enable_libfuzzer and oss_fuzz_mode at the same time!")
endif()
endif()


if(NOT oss_fuzz_mode AND NOT enable_libfuzzer AND NOT link_with_main)
  message(FATAL_ERROR "use one of oss_fuzz_mode, enable_libfuzzer or link_with_main, otherwise the link won't find main!")
endif() 

# step 1 - let libtorrent compile but not link with the fuzzers
if(enable_libfuzzer)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer-no-link")
endif()
add_subdirectory(root)

# step 2 - compile and link the fuzzers with the fuzzers
if(enable_libfuzzer)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer")
endif()


#some glue code to avoid having to repeate the same crappy casts
#over and over again
add_library(glue OBJECT glue/glue.cpp)
target_link_libraries(glue torrent-rasterbar)

#if using afl, or making a reproducer, of some other reason that
#means we need to provide our own main
add_library(main OBJECT glue/slurp.cpp glue/aflmain.cpp)
target_link_libraries(main glue)

#find all fuzzers.
file(GLOB SOURCES "*.cpp")

macro(implement_fuzzer sourcefile)
  get_filename_component(basename ${sourcefile} NAME_WE)
  add_executable(fuzzer_${basename} ${sourcefile})
  target_link_libraries(fuzzer_${basename} torrent-rasterbar)
  target_link_libraries(fuzzer_${basename} glue)
  if(oss_fuzz_mode)
    target_link_libraries(fuzzer_${basename} ${engine})
  endif()
  if(link_with_main)
    target_link_libraries(fuzzer_${basename} main)
  endif()
endmacro()

foreach(X IN ITEMS ${SOURCES})
    implement_fuzzer(${X})
endforeach()


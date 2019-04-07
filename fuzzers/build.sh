#!/bin/sh
#
# Builds various variants of the fuzzers
#
# Author: Paul Dreik 

set -e

me=$(basename "$0")
scriptdir=$(readlink -f "$(dirname "$0")")
rootdir=$(readlink -f "$scriptdir/..")

#cmake backend (leave empty for the default)
cmakebackend=-GNinja

#let the user optionally set another cmake
if [ -z $CMAKE ] ; then
    CMAKE=cmake
fi

# 1 - directory name for build
# 2 - CXX
# 3 - CXXFLAGS
# 4 - cmake args
dobuild() {
    cd $scriptdir
    mkdir -p $1
    cd $1
    CXX=$2 CXXFLAGS=$3 $CMAKE .. -Dexpose_internal_functions=On $4 $cmakebackend
    $CMAKE --build .
}

# local fuzzing with libfuzzer (good for speedy exploration)
dobuild build-libfuzzer-plain clang++ -O3  -Denable_libfuzzer=On

# local fuzzing with libFuzzer, with sanitizers
dobuild build-libfuzzer-sanitizers clang++ "-O3 -fsanitize=address,undefined"  -Denable_libfuzzer=On

# local fuzzing with AFL:
dobuild build-aflgcc-plain afl-g++ "" -Dlink_with_main=On 

# reproducer (good for coverage, valgrind)
dobuild build-reproducer-gcc-plain g++ "-g -O0" -Dlink_with_main=On 

# reproducer, good for verifying that the corpus is in good shape
dobuild build-reproducer-clang-sanitizers clang++ "-fsanitize=address,undefined" -Dlink_with_main=On

# emulating what it looks like when building through oss-fuzz
export LIB_FUZZING_ENGINE=/usr/lib/llvm-7/lib/libFuzzer.a
dobuild build-ossfuzz-emulation clang++-7 "-fsanitize=fuzzer-no-link,address" \
	-Doss_fuzz_mode=On -DBUILD_SHARED_LIBS=Off
unset LIB_FUZZING_ENGINE


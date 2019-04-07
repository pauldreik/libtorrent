#!/bin/sh
#
# This script is for running fuzzers,
# corpus minimization and measuring coverage.
#
# Build the fuzzers with the specific flags
# required for what you are about to do, then
# execute the script from within that build directory.
#
# Author: Paul Dreik 

set -e

rootdir=$(readlink -f "$(dirname "$0")/..")

#where is the corpus directory
corpusdir=$rootdir/fuzzers/corpus

#where is the build dir
builddir=$(pwd)

#which mode to run in  (minimize|run|reproduce)
#mode=libfuzzerminimize
#mode=run
#mode=reproduce
#mode=runafl
#mode=runaflcmin
#mode=runlibfuzzerinscreen
mode=kcov

for fuzzer in $(ls fuzzer_* |sed -e 's/fuzzer_//') ; do
    echo $looking at fuzzer $fuzzer

    mkdir -p out/$fuzzer
    mkdir -p $corpusdir/$fuzzer
    export UBSAN_OPTIONS=halt_on_error=1

    #running locally
    if [ $mode = run ] ; then
	$builddir/fuzzer_$fuzzer -max_total_time=20 out/$fuzzer $corpusdir/$fuzzer
    fi

    #minimization of corpus. replace the existing one.
    if [ $mode = libfuzzerminimize ]; then
	[ -e $corpusdir/$fuzzer.tmp ] && rm -rf $corpusdir/$fuzzer.tmp
	mkdir -p $corpusdir/$fuzzer.tmp
	$builddir/fuzzer_$fuzzer -merge=1 $corpusdir/$fuzzer.tmp $corpusdir/$fuzzer out/$fuzzer
	rm -rf $corpusdir/$fuzzer
	mv $corpusdir/$fuzzer.tmp $corpusdir/$fuzzer
    fi

    #reproduce - just runs the input from the corpus
    if [ $mode = reproduce ]; then
	$builddir/fuzzer_$fuzzer $corpusdir/$fuzzer/*
    fi

    #kcov
    if [ $mode = kcov ]; then
	mkdir -p kcovout
	kcov kcovout --exclude-path=/usr/include $builddir/fuzzer_$fuzzer $corpusdir/$fuzzer/*
    fi

    
    #running afl in separate screen sessions
    if [ $mode = runafl ]; then
	screen -S afl -X screen
	screen -S afl -X stuff "afl-fuzz -m none -i cminout/$fuzzer -o out/$fuzzer -- $builddir/fuzzer_$fuzzer @@\n"
    fi
    if [ $mode = runaflcmin ]; then
	mkdir -p cminout/$fuzzer
	screen -S afl -X screen
	screen -S afl -X stuff "afl-cmin -m none -i $corpusdir/$fuzzer -o cminout/$fuzzer -- $builddir/fuzzer_$fuzzer @@\n"
    fi

    if [ $mode = runlibfuzzerinscreen ]; then
	screen -S libfuzzer -X screen
	screen -S libfuzzer -X title "libfuzzer run $(LANG= date --rfc-3339=s) run"
	screen -S libfuzzer -X stuff "$builddir/fuzzer_$fuzzer out/$fuzzer $corpusdir/$fuzzer\n"
    fi

done

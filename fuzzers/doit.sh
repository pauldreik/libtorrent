#!/bin/sh

#run this from the build directory

set -e

rootdir=$(readlink -f $(dirname $0)/..)

#where is the build directory
builddir=$rootdir/fuzzers/build-localfuzzer

#where is the corpus directory
corpusdir=$rootdir/fuzzers/corpus

#which mode to run in  (minimize|run|reproduce)
mode=minimize
mode=run
mode=reproduce

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
   if [ $mode = minimize ]; then
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
done




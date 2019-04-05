This directory contains fuzzers.

The cmake based build is intended to be usable for four kinds of builds:

1)
oss-fuzz targets (see https://github.com/google/oss-fuzz/blob/master/docs/ideal_integration.md#build-support
and https://github.com/google/oss-fuzz/blob/master/docs/new_project_guide.md#buildsh)

2)
local fuzzing with libFuzzer

3)
local fuzzing with afl

4)
reproducer binaries, which can be used for multiple purposes. These
don't have any fuzzing instrumentation, they just serve as a way to execercise
the code with data of your choice.
 a) making sure the corpora passes without crashes, even
    with sanitizers enabled
 b) reproducing a crash from a crashing test case and perhaps
    run in a debugger or through valgrind
 c) measuring coverage, perhaps with a tool like kcov.




Adding a fuzzer should be easy, name it with suffix .cpp and drop in this
directory and rerun cmake.

Happy fuzzing!


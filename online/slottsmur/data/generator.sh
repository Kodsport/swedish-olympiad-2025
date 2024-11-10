#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution arvid100.cpp

compile gen_rand.py 

samplegroup
limits maxn=10 maxq=10
sample 1

group group1 10
limits maxn=100 maxq=100
tc 1
tc g1-1 gen_rand n=100 q=100
tc g1-2 gen_rand n=100 q=100
tc g1-3 gen_rand n=100 q=100
tc g1-4 gen_rand n=100 q=100

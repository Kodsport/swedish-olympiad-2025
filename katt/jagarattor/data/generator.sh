#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution highdeg_slow.cpp

compile gen_slowrand.py

group group1 5
tc g1-1 gen_slowrand n=5 m=5 q=100
tc g1-2 gen_slowrand n=6 m=8 q=10
tc g1-3 gen_slowrand n=10 m=30 q=100
tc g1-4 gen_slowrand n=30 m=40 q=100
tc g1-5 gen_slowrand n=200 m=500 q=100
tc g1-6 gen_slowrand n=100 m=500 q=100


# TODO: low degree group

group group2 5
tc g2-6 gen_slowrand n=100 m=500 q=20000
# high degree testcases

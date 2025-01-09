#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2
sample 3

group group1 17
limits line=1
tc 2
tc line-1 gen_rand n=10 m=9 sand=1 mode=line
tc line-2 gen_rand n=300000 m=299999 sand=1 mode=line
tc line-3 gen_rand n=300000 m=299999 sand=1 noise=1 mode=line

group group2 29
limits tree=1
include_group group1
tc 3
tc tree-1 gen_rand n=10 m=9 sand=3
tc tree-2 gen_rand n=1000 m=999 branch=3 sand=1
tc tree-3 gen_rand n=300000 m=299999 branch=3 sand=1
tc tree-4 gen_rand n=300000 m=299999 sand=10
tc tree-5 gen_rand n=300000 m=299999 sand=10 noise=1

group group3 34
limits possible=1
tc 1
tc possible-1 gen_rand n=10 m=15 sand=3
tc possible-2 gen_rand n=100 m=711 sand=30
tc possible-3 gen_rand n=100 m=141 branch=3 sand=3
tc possible-4 gen_rand n=200000 m=300000 branch=10 sand=2000
tc possible-5 gen_rand n=300000 m=300000 branch=100 sand=30
tc possible-6 gen_rand n=300 m=300 branch=100 sand=300

group group4 20
include_group group3
include_group group2
tc full-1 gen_rand n=25 m=35 sand=0 branch=4
tc full-2 gen_rand n=152 m=341 sand=20 branch=7 noise=1
tc full-3 gen_rand n=1592 m=1700 sand=141 noise=1
tc full-4 gen_rand n=99281 m=100000 sand=0 noise=1
tc full-5 gen_rand n=300000 m=300000 sand=10000 noise=1

#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils.cpp

compile gen_rand.py

samplegroup
sample 1

MAXN=300000

group group1 17
limits m=1
tc line-1 gen_rand n=1000 m=1 q=30000 sand_density=0 sand_changes=10

group group2 28
#limits n=100 m=100 q=100
tc 1
tc small-1 gen_rand n=10 m=10 q=100
tc small-2 gen_rand n=100 m=10 q=100 sand_density=0.1
tc small-3 gen_rand n=10 m=100 q=100 sand_density=0
tc small-4 gen_rand n=30 m=30 q=100 sand_density=0.03 possible=1
tc small-5 gen_rand n=100 m=100 q=100 sand_density=0.001
tc small-6 gen_rand n=100 m=100 q=100 sand_density=0.03 q_density=0.9

group group3 20
tc possible-1 gen_rand n=300 m=300 q=300000 sand_density=0.01 possible=1 sand_changes=100

group group4 35
include_group group1
include_group group2
include_group group3
tc large-1 gen_rand n=10000 m=30 q=300000 sand_density=0.01 sand_changes=100

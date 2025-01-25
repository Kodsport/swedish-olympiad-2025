#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils.py

compile gen_rand.py

samplegroup
sample 1
sample 2
sample 3

MAXN=300000
MAXT=1000000000

group group1 17
limits n=200 t=500
tc 1
tc tiny-1 gen_rand n=10 tmax=10
tc tiny-2 gen_rand n=20 tmax=100
tc tiny-3 gen_rand n=200 tmax=500
tc tiny-4 gen_rand n=200 tmax=500
tc tiny-5 gen_rand n=200 tmax=500 mode=groups d=2
tc tiny-6 gen_rand n=200 tmax=500 mode=groups d=5
tc tiny-7 gen_rand n=200 tmax=500 mode=pairs
tc tiny-8 gen_rand n=200 tmax=500 mode=uneven large=5

group group2 26
limits n=1000 t=$MAXT
include_group group1
tc 2
tc 3
tc small-1 gen_rand n=1000
tc small-2 gen_rand n=1000
tc small-3 gen_rand n=1000 mode=groups d=10
tc small-4 gen_rand n=1000 mode=groups d=100
tc small-5 gen_rand n=1000 mode=pairs
tc small-6 gen_rand n=1000 mode=uneven large=13

group group3 25
limits n=$MAXN t=$MAXT identity=1
tc identity-1 gen_rand n=2 mode=identity
tc identity-2 gen_rand n=299999 mode=identity
tc identity-3 gen_rand n=300000 mode=identity

group group4 32
limits n=$MAXN t=$MAXT 
include_group group3
include_group group2
tc full-1 gen_rand n=300000
tc full-2 gen_rand n=300000
tc full-3 gen_rand n=300000
tc full-4 gen_rand n=300000 mode=groups d=2
tc full-5 gen_rand n=300000 mode=groups d=3
tc full-6 gen_rand n=300000 mode=groups d=10000
tc full-7 gen_rand n=300000 mode=pairs
tc full-8 gen_rand n=300000 mode=uneven large=3
tc full-9 gen_rand n=300000 mode=uneven large=127

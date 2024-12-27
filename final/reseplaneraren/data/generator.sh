#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution segtree_sweep.cpp

compile gen_rand.py
compile gen_long.py

samplegroup
limits maxn=10 maxk=10 maxq=10
sample 1
sample 2

group group1 10
limits maxn=100 maxk=100 maxq=100
include_group sample
tc g1-1 gen_rand n=100 k=100 q=100
tc g1-2 gen_long n=100 k=100 q=100

group group2 20
limits maxn=1000 maxk=1000 maxq=1000
include_group group1
tc g2-1 gen_rand n=1000 k=1000 q=1000
tc g2-2 gen_rand n=1000 k=10 q=1000
tc g2-3 gen_long n=1000 k=1000 q=1000

group group3 15
limits maxn=1000 maxk=50000 maxq=50000
include_group group2
tc g3-1 gen_rand n=1000 k=50000 q=50000
tc g3-2 gen_rand n=1000 k=10 q=50000
tc g3-3 gen_long n=1000 k=50000 q=50000

group group4 15
limits maxn=50000 maxk=50000 maxq=50000
include_group group3
tc g4-1 gen_rand n=50000 k=50000 q=50000
tc g4-2 gen_rand n=50000 k=10 q=50000
tc g4-3 gen_long n=50000 k=50000 q=50000

group group5 40
limits maxn=300000 maxk=300000 maxq=300000
include_group group4
tc g5-1 gen_rand n=300000 k=50000 q=300000
tc g5-2 gen_rand n=300000 k=10 q=300000
tc g5-3 gen_long n=300000 k=300000 q=300000

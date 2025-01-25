#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution segtree_sweep.cpp

compile gen_rand.py
compile gen_long.py
compile gen_new.py

samplegroup
limits maxn=10 maxk=10 maxq=10
sample 1

group group1 7
limits maxn=100 maxk=100 maxq=100
include_group sample
tc g1-1 gen_rand n=100 k=100 q=100
tc g1-2 gen_long n=100 k=100 q=100
tc g1-3 gen_new n=100 k=100 q=100
tc g1-4 gen_new n=100 k=100 q=100 branch=1 tram_len=10
tc g1-5 gen_new n=100 k=100 q=100 branch=5 tram_len=10
tc g1-6 gen_new n=100 k=100 q=100 branch=3 tram_len=4
tc g1-7 gen_new n=100 k=100 q=100 mode=star
tc g1-8 gen_new n=100 k=100 q=100 mode=star noise=30

group group2 19
limits maxn=1000 maxk=1000 maxq=1000
include_group group1
tc g2-1 gen_rand n=1000 k=1000 q=1000
tc g2-2 gen_rand n=1000 k=10 q=1000
tc g2-3 gen_long n=1000 k=1000 q=1000
tc g2-4 gen_new n=1000 k=1000 q=1000 branch=10 tram_len=40
tc g2-5 gen_new n=1000 k=1000 q=1000 branch=4 tram_len=100
tc g2-6 gen_new n=1000 k=1000 q=1000 branch=1 tram_len=500
tc g2-7 gen_new n=1000 k=1000 q=1000 mode=star noise=100

group group3 13
limits maxn=50000 maxk=50000 maxq=50000
tc g3-1 gen_rand n=1000 k=50000 q=50000
tc g3-2 gen_rand n=1000 k=10 q=50000
tc g3-3 gen_long n=1000 k=50000 q=50000
tc g3-4 gen_new n=1000 k=50000 q=50000 branch=5 tram_len=40
tc g3-5 gen_new n=1000 k=50000 q=50000 branch=2 tram_len=500
tc g3-6 gen_new n=50000 k=50000 q=50000 mode=star noise=600
tc g3-7 gen_rand n=50000 k=50000 q=50000
tc g3-8 gen_rand n=50000 k=10 q=50000
tc g3-9 gen_long n=50000 k=50000 q=50000
tc g3-10 gen_new n=50000 k=50000 q=50000 branch=100 tram_len=1000
tc g3-11 gen_new n=50000 k=50000 q=50000 branch=10 tram_len=345
tc g3-12 gen_new n=50000 k=50000 q=50000 branch=2 tram_len=10000
tc g3-13 gen_new n=50000 k=50000 q=50000 mode=star noise=1000

group group4 23
limits mode=g4 maxn=300000 maxk=300000 maxq=300000
tc g4-1 gen_rand n=300000 k=300000 q=300000 mode=g4

group group5 38
limits maxn=300000 maxk=300000 maxq=300000
include_group group1
include_group group2
include_group group3
include_group group4
tc g5-1 gen_rand n=300000 k=50000 q=300000
tc g5-2 gen_rand n=300000 k=10 q=300000
tc g5-3 gen_long n=300000 k=300000 q=300000
tc g5-4 gen_new n=300000 k=300000 q=300000
tc g5-5 gen_new n=300000 k=300000 q=300000 branch=100 tram_len=9000
tc g5-6 gen_new n=300000 k=300000 q=300000 branch=10 tram_len=90000
tc g5-7 gen_new n=300000 k=300000 q=300000 branch=1 tram_len=150000
tc g5-8 gen_new n=300000 k=300000 q=300000 mode=star
tc g5-9 gen_new n=300000 k=300000 q=300000 mode=star noise=10000
tc g5-10 gen_new n=300000 k=300000 q=300000 mode=star noise=130000

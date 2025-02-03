#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution joshua_sqrt.cpp

compile gen_rand.py

samplegroup
limits maxn=10 maxk=10 maxt=10
sample 1
sample 2
sample 3

group group1 3
limits maxn=15 maxq=0 maxv=9
tc 1
tc 2
tc g1-1 gen_rand n=15 q=0 maxv=9

group group2 7
limits maxn=1000 maxq=0 maxv=9
include_group group1
tc g2-1 gen_rand n=1000 q=0 maxv=9

group group3 8
limits maxn=100000 maxq=0 maxv=9
include_group group2
tc g3-1 gen_rand n=100000 q=0 maxv=9

group group4 15
limits maxn=100000 maxq=6000 maxv=9
include_group group3
tc 3
tc g4-1 gen_rand n=100000 q=6000 maxv=9

group group5 30
limits maxn=100000 maxq=100000 maxv=1
tc g5-1 gen_rand n=100000 q=100000 maxv=1

group group6 20
limits maxn=100000 maxq=100000 maxv=3
include_group group5
tc g6-1 gen_rand n=100000 q=100000 maxv=3

group group7 7
limits maxn=100000 maxq=100000 maxv=6
include_group group6
tc g7-1 gen_rand n=100000 q=100000 maxv=6

group group8 10
limits maxn=100000 maxq=100000 maxv=9
include_group group4
include_group group7
tc g8-1 gen_rand n=100000 q=100000 maxv=9


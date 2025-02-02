#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution joshua.cpp

compile gen_rand.py

# samplegroup
# limits maxn=10 maxk=10 maxt=10
# sample 1

group group1 3
limits maxn=15 maxq=0 maxv=9
tc g1-1 gen_rand n=15 q=0 maxv=9

group group2 7
limits maxn=1000 maxq=0 maxv=9
tc g2-1 gen_rand n=1000 q=0 maxv=9

group group3 8
limits maxn=100000 maxq=0 maxv=9
tc g3-1 gen_rand n=100000 q=0 maxv=9

group group4 15
limits maxn=100000 maxq=4000 maxv=9
tc g4-1 gen_rand n=100000 q=4000 maxv=9

group group5 30
limits maxn=100000 maxq=100000 maxv=1
tc g5-1 gen_rand n=100000 q=100000 maxv=1

group group6 20
limits maxn=100000 maxq=100000 maxv=3
tc g6-1 gen_rand n=100000 q=100000 maxv=3

group group7 7
limits maxn=100000 maxq=100000 maxv=6
tc g7-1 gen_rand n=100000 q=100000 maxv=6

group group8 10
limits maxn=100000 maxq=100000 maxv=9
tc g8-1 gen_rand n=100000 q=100000 maxv=9


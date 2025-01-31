#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution sqrt10.cpp

compile gen_rand.py

# samplegroup
# limits maxn=10 maxk=10 maxt=10
# sample 1

group group1 10
limits maxn=15 maxq=0 maxv=9
tc g1-1 gen_rand n=15 q=0 maxv=9
tc g1-2 gen_rand n=15 q=0 maxv=9

group group2 10
limits maxn=1000 maxq=0 maxv=10
tc g2-1 gen_rand n=1000 q=0 maxv=9
tc g2-2 gen_rand n=1000 q=0 maxv=9

group group3 10
limits maxn=100000 maxq=0 maxv=10
tc g3-1 gen_rand n=100000 q=0 maxv=9
tc g3-2 gen_rand n=100000 q=0 maxv=9

group group4 10
limits maxn=100000 maxq=2000 maxv=10
tc g4-1 gen_rand n=100000 q=2000 maxv=9
tc g4-2 gen_rand n=100000 q=2000 maxv=9

group group5 10
limits maxn=100000 maxq=100000 maxv=1
tc g5-1 gen_rand n=100000 q=100000 maxv=1
tc g5-2 gen_rand n=100000 q=100000 maxv=1

group group6 10
limits maxn=100000 maxq=100000 maxv=3
tc g6-1 gen_rand n=100000 q=100000 maxv=3
tc g6-2 gen_rand n=100000 q=100000 maxv=3

group group7 10
limits maxn=100000 maxq=100000 maxv=6
tc g7-1 gen_rand n=100000 q=100000 maxv=6
tc g7-2 gen_rand n=100000 q=100000 maxv=6

group group8 10
limits maxn=100000 maxq=100000 maxv=9
tc g8-1 gen_rand n=100000 q=100000 maxv=9
tc g8-2 gen_rand n=100000 q=100000 maxv=9


#!/bin/bash
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited
use_solution joshua_sqrt.cpp

compile gen_rand.py
compile gen_same.py

samplegroup
limits maxn=10 maxq=10 maxv=10
sample 1
sample 2
sample 3

group group1 3
limits maxn=15 maxq=0 maxv=9
tc 1
tc 2
tc g1-1 gen_rand n=15 q=0 maxv=9
tc g1-2 gen_same n=15 q=0 maxv=9 mode="same"
tc g1-3 gen_same n=15 q=0 maxv=9 mode="diff"

group group2 7
limits maxn=1000 maxq=0 maxv=9
include_group group1
tc g2-1 gen_rand n=1000 q=0 maxv=9 
tc g2-2 gen_same n=1000 q=0 maxv=9 mode="same"
tc g2-3 gen_same n=1000 q=0 maxv=9 mode="diff"

group group3 8
limits maxn=100000 maxq=0 maxv=9
include_group group2
tc g3-1 gen_rand n=100000 q=0 maxv=9
tc g3-2 gen_same n=100000 q=0 maxv=9 mode="same"
tc g3-3 gen_same n=100000 q=0 maxv=9 mode="diff"

group group4 15
limits maxn=100000 maxq=6000 maxv=9
include_group group3
tc 3
tc g4-1 gen_rand n=100000 q=6000 maxv=9 
tc g4-2 gen_same n=100000 q=6000 maxv=9 mode="same" 
tc g4-3 gen_same n=100000 q=6000 maxv=9 mode="same" phaseSize=3000
tc g4-4 gen_same n=100000 q=6000 maxv=9 mode="same" phaseSize=10
tc g4-5 gen_same n=100000 q=6000 maxv=9 mode="diff" 
tc g4-6 gen_same n=100000 q=6000 maxv=9 mode="diff" phaseSize=3000
tc g4-7 gen_same n=100000 q=6000 maxv=9 mode="diff" phaseSize=10
tc g4-8 gen_rand n=100000 q=6000 maxv=9 mode="distinct"

group group5 30
limits maxn=100000 maxq=100000 maxv=1
tc g5-1 gen_rand n=100000 q=100000 maxv=1
tc g5-2 gen_same n=100000 q=100000 maxv=1 mode="same" 
tc g5-3 gen_same n=100000 q=100000 maxv=1 mode="same" phaseSize=50000
tc g5-4 gen_same n=100000 q=100000 maxv=1 mode="same" phaseSize=10
tc g5-5 gen_same n=100000 q=100000 maxv=1 mode="diff" 
tc g5-6 gen_same n=100000 q=100000 maxv=1 mode="diff" phaseSize=50000
tc g5-7 gen_same n=100000 q=100000 maxv=1 mode="diff" phaseSize=10
tc g5-8 gen_rand n=100000 q=100000 maxv=1 mode="distinct"

group group6 20
limits maxn=100000 maxq=100000 maxv=3
include_group group5
tc g6-1 gen_rand n=100000 q=100000 maxv=3
tc g6-2 gen_same n=100000 q=100000 maxv=3 mode="same" 
tc g6-3 gen_same n=100000 q=100000 maxv=3 mode="same" phaseSize=50000
tc g6-4 gen_same n=100000 q=100000 maxv=3 mode="same" phaseSize=10
tc g6-5 gen_same n=100000 q=100000 maxv=3 mode="diff" 
tc g6-6 gen_same n=100000 q=100000 maxv=3 mode="diff" phaseSize=50000
tc g6-7 gen_same n=100000 q=100000 maxv=3 mode="diff" phaseSize=10
tc g6-8 gen_rand n=100000 q=100000 maxv=3 mode="distinct"

group group7 7
limits maxn=100000 maxq=100000 maxv=6
include_group group6
tc g7-1 gen_rand n=100000 q=100000 maxv=6
tc g7-2 gen_same n=100000 q=100000 maxv=6 mode="same" 
tc g7-3 gen_same n=100000 q=100000 maxv=6 mode="same" phaseSize=50000
tc g7-4 gen_same n=100000 q=100000 maxv=6 mode="same" phaseSize=10
tc g7-5 gen_same n=100000 q=100000 maxv=6 mode="diff" 
tc g7-6 gen_same n=100000 q=100000 maxv=6 mode="diff" phaseSize=50000
tc g7-7 gen_same n=100000 q=100000 maxv=6 mode="diff" phaseSize=10
tc g7-8 gen_rand n=100000 q=100000 maxv=6 mode="distinct"

group group8 10
limits maxn=100000 maxq=100000 maxv=9
include_group group4
include_group group7
tc g8-1 gen_rand n=100000 q=100000 maxv=9
tc g8-2 gen_same n=100000 q=100000 maxv=9 mode="same" 
tc g8-3 gen_same n=100000 q=100000 maxv=9 mode="same" phaseSize=50000
tc g8-4 gen_same n=100000 q=100000 maxv=9 mode="same" phaseSize=10
tc g8-5 gen_same n=100000 q=100000 maxv=9 mode="diff" 
tc g8-6 gen_same n=100000 q=100000 maxv=9 mode="diff" phaseSize=50000
tc g8-7 gen_same n=100000 q=100000 maxv=9 mode="diff" phaseSize=10
tc g8-8 gen_rand n=100000 q=100000 maxv=9 mode="distinct"
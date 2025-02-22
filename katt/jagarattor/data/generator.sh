#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution simd.cpp

# graph with many articulation points
# some cheese i forgot

# stars
# degreeness: precompute rat graph -> some high-degree node, many BCC adjacent
# query transitions rat graph -> some high-degree node part of many queries

# starry with rat as center
# query "which side of rat am i" 

# starry with t as center
# query "can i reach any node adjacent to rat"

# starry with s as center?

# scc.cpp is too fast
# m2q is too fast

compile gen_rand.py
compile gen_lowdeg.py
compile gen_starry.py
compile gen_star.py
compile gen_path.py
compile gen_logstar.py
compile gen_articulation.py

samplegroup
limits maxn=10 maxm=10 maxq=10
sample 1

group group1 5
limits maxn=50 maxm=50 maxq=100
tc 1
tc g1-1 gen_rand n=5 m=5 q=100
tc g1-2 gen_rand n=6 m=8 q=10
tc g1-3 gen_rand n=10 m=30 q=100
tc g1-4 gen_rand n=30 m=40 q=100
tc g1-5 gen_path n=50 q=100
tc g1-6 gen_star n=50 q=100
tc g1-7 gen_articulation n=20 q=100

group group2 11
include_group group1
limits maxn=500 maxm=500 maxq=10000
tc g2-1 gen_starry n=376 m=500 q=10000
tc g2-2 gen_rand n=100 m=500 q=10000
tc g2-3 gen_rand n=200 m=500 q=10000
tc g2-4 gen_rand n=100 m=500 q=10000
tc g2-5 gen_path n=500 q=10000
tc g2-6 gen_star n=500 q=10000
tc g2-7 gen_logstar n=470 q=10000 decay=0.5 focal=0
tc g2-8 gen_logstar n=470 q=10000 decay=0.5 focal=1
tc g2-9 gen_logstar n=470 q=10000 decay=0.5 focal=2
tc g2-10 gen_articulation n=310 q=10000

group group3 20
limits maxn=100000 maxm=100000 maxq=1 maxdeg=5
tc g3-1 gen_lowdeg n=90000 m=100000 maxdeg=5 q=1
tc g3-2 gen_path n=100000 q=1
tc g3-3 gen_lowdeg n=100 m=200 maxdeg=5 q=1
tc g3-4 gen_lowdeg n=100 m=105 maxdeg=5 q=1
tc g3-5 gen_lowdeg n=100 m=240 maxdeg=5 q=1
tc g3-6 gen_lowdeg n=100 m=120 maxdeg=5 q=1
tc g3-7 gen_lowdeg n=100 m=150 maxdeg=5 q=1
tc g3-8 gen_articulation n=72000 q=1

group group4 23
limits maxn=100000 maxm=100000 maxq=1
include_group group3
tc g4-1 gen_starry n=75000 m=100000 q=1 seed=123456 # for python3, use 12345 instead
tc g4-2 gen_starry n=100 m=500 q=1
tc g4-3 gen_starry n=100 m=500 q=1
tc g4-4 gen_rand n=10 m=30 q=1
tc g4-5 gen_rand n=10 m=30 q=1
tc g4-6 gen_rand n=10 m=30 q=1
tc g4-7 gen_rand n=10 m=30 q=1
tc g4-8 gen_rand n=10 m=30 q=1
tc g4-9 gen_rand n=10 m=30 q=1
tc g4-10 gen_path n=100000 q=1
tc g4-11 gen_star n=100000 q=1
tc g4-12 gen_logstar n=99000 q=1 decay=0.5 focal=0
tc g4-13 gen_logstar n=99000 q=1 decay=0.5 focal=1
tc g4-14 gen_logstar n=99000 q=1 decay=0.5 focal=2
tc g4-15 gen_articulation n=72000 q=1
tc g4-16 gen_articulation n=72000 q=1

group group5 12
limits maxn=100000 maxm=100000 maxq=100000 samerat=1 samestart=1
tc g5-1 gen_starry n=75000 m=100000 q=5 samerat=1 samestart=1 seed=123456 # for python3, use 12345 instead
tc g5-2 gen_starry n=75000 m=100000 q=100000 samerat=1 samestart=1
tc g5-3 gen_rand n=30000 m=100000 q=100000 samerat=1 samestart=1
tc g5-4 gen_path n=100000 q=100000 samerat=1 samestart=1
tc g5-5 gen_star n=100000 q=100000 samerat=1 samestart=1
tc g5-12 gen_logstar n=99000 q=100000 decay=0.5 focal=0 samerat=1
tc g5-13 gen_logstar n=99000 q=100000 decay=0.5 focal=1 samerat=1
tc g5-14 gen_logstar n=99000 q=100000 decay=0.5 focal=2 samerat=1
tc_manual ../manual_data/tiny_evil
# random small cases
tc g5-6 gen_rand n=10 m=30 q=1
tc g5-7 gen_rand n=10 m=30 q=1
tc g5-8 gen_rand n=10 m=30 q=1
tc g5-9 gen_rand n=10 m=30 q=1
tc g5-10 gen_rand n=10 m=30 q=1
tc g5-11 gen_rand n=10 m=30 q=1
tc g5-15 gen_articulation n=72000 q=100000 samestart=1 samerat=1

group group6 17
limits maxn=100000 maxm=100000 maxq=100000 samegoal=1
tc g6-1 gen_starry n=75000 m=100000 q=5 samegoal=1 seed=123456 # for python3, use 12345 instead
tc g6-2 gen_starry n=100 m=500 q=100000 samegoal=1
tc g6-3 gen_path n=100000 q=100000 samegoal=1
tc g6-4 gen_star n=100000 q=100000 samegoal=1
tc g6-5 gen_rand n=100000 m=100000 q=100000 samegoal=1
tc g6-6 gen_rand n=30000 m=100000 q=100000 samegoal=1
tc g6-13 gen_logstar n=99000 q=100000 decay=0.5 focal=0 samegoal=1
tc g6-14 gen_logstar n=99000 q=100000 decay=0.5 focal=1 samegoal=1
tc g6-15 gen_logstar n=99000 q=100000 decay=0.5 focal=2 samegoal=1
tc_manual ../manual_data/samegoal_evil
tc tiny_evil
# random small cases
tc g6-7 gen_rand n=10 m=30 q=1
tc g6-8 gen_rand n=10 m=30 q=1
tc g6-9 gen_rand n=10 m=30 q=1
tc g6-10 gen_rand n=10 m=30 q=1
tc g6-11 gen_rand n=10 m=30 q=1
tc g6-12 gen_rand n=10 m=30 q=1
tc g6-16 gen_articulation n=72000 q=100000 samegoal=1

group group7 10
limits maxn=30000 maxm=30000 maxq=100000
include_group group2
tc g7-1 gen_star n=30000 q=100000
tc g7-2 gen_starry n=19000 m=30000 q=100000 seed=123456 # for python3, use 12345 instead
tc g7-3 gen_path n=30000 q=100000
tc g7-4 gen_rand n=30000 m=30000 q=100000
tc g7-5 gen_rand n=15000 m=30000 q=100000
tc g7-6 gen_logstar n=29900 q=100000 decay=0.5 focal=0
tc g7-7 gen_logstar n=29900 q=100000 decay=0.5 focal=1
tc g7-8 gen_logstar n=29900 q=100000 decay=0.5 focal=2
tc g7-9 gen_articulation n=19000 q=100000

group group8 2
limits maxn=100000 maxm=100000 maxq=100000
include_group group4
include_group group5
include_group group6
include_group group7
tc g8-1 gen_star n=100000 q=100000
tc g8-2 gen_starry n=75000 m=100000 q=100000 seed=123456 # for python3, use 12345 instead
tc g8-3 gen_path n=100000 q=100000
tc g8-4 gen_star n=100000 q=100000
tc g8-5 gen_rand n=100000 m=100000 q=100000
tc g8-6 gen_rand n=30000 m=100000 q=100000
tc g8-7 gen_logstar n=99000 q=100000 decay=0.5 focal=0
tc g8-8 gen_logstar n=99000 q=100000 decay=0.5 focal=1
tc g8-9 gen_logstar n=99000 q=100000 decay=0.5 focal=2
tc g8-10 gen_articulation n=72000 q=100000

#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution olle.cpp

compile gen_dense.py
compile gen_shapes.py
compile gen_square.py

samplegroup
sample 1
sample 2
sample 3
sample 4

group group1 10
tc 1
tc 2
tc 3
tc 4
tc g1-1 gen_shapes n=5 r=4 c=5
tc g1-2 gen_dense r=5 c=4
tc g1-3 gen_shapes n=20 r=4 c=5
tc g1-4 gen_shapes n=20 r=5 c=4
tc g1-5 gen_shapes n=10 r=3 c=5
tc g1-6 gen_shapes n=2 r=4 c=5
tc g1-7 gen_shapes n=10 r=4 c=5
tc g1-8 gen_shapes n=5 r=2 c=10
tc g1-9 gen_shapes n=5 r=10 c=2
tc g1-10 gen_dense r=2 c=10
tc g1-11 gen_dense r=10 c=2
tc g1-12 gen_dense r=5 c=4


group group2 5
tc 2
tc g2-1 gen_shapes n=400000 r=400000 c=1
tc g2-2 gen_shapes n=100000 r=400000 c=1
tc g2-3 gen_shapes n=1000 r=2000 c=1
tc g2-4 gen_shapes n=100000 r=400000 c=1
tc g2-5 gen_shapes n=9000 r=400000 c=1
tc g2-6 gen_shapes n=10023 r=29990 c=1
tc g2-7 gen_shapes n=16023 r=51230 c=1
tc g2-8 gen_shapes n=30023 r=123350 c=1
tc g2-9 gen_shapes n=90000 r=503223 c=1

group group3 10
include_group group2
tc g3-1 gen_shapes n=1000 r=200000 c=2
tc g3-2 gen_shapes n=100000 r=200000 c=2
tc g3-3 gen_shapes n=50000 r=200000 c=2
tc g3-4 gen_shapes n=100 r=200000 c=2
tc g3-5 gen_shapes n=400000 r=200000 c=2
tc g3-6 gen_shapes n=200000 r=200000 c=2
tc g3-7 gen_shapes n=100 r=2000 c=2

group group4 15
include_group group2
tc g4-1 gen_square r=500 c=500
tc g4-2 gen_square r=1000 c=400
tc g4-3 gen_square r=400 c=1000
tc g4-4 gen_square r=50 c=50
tc g4-5 gen_square r=4 c=100000
tc g4-6 gen_square r=100000 c=4
tc g4-7 gen_square r=500 c=500
tc g4-8 gen_dense r=1000 c=400
tc g4-9 gen_dense r=500 c=500
tc g4-10 gen_dense r=400 c=1000


group group5 15
include_group group1
tc g5-1 gen_shapes n=2000 r=50 c=50
tc g5-2 gen_shapes n=2000 r=500 c=500
tc g5-3 gen_shapes n=1999 r=100 c=4000
tc g5-4 gen_shapes n=1234 r=20000 c=20
tc g5-5 gen_shapes n=2000 r=5000 c=50
tc g5-6 gen_shapes n=1230 r=50 c=5000

group group6 7
include_group group5
tc g6-1 gen_shapes n=50000 r=500 c=500
tc g6-2 gen_shapes n=50000 r=200 c=1000
tc g6-3 gen_shapes n=50000 r=1000 c=400
tc g6-4 gen_shapes n=43211 r=500 c=500
tc g6-5 gen_shapes n=50000 r=100 c=500
tc g6-6 gen_shapes n=12345 r=333 c=333

group group7 38
tc g7-1 gen_shapes n=400000 r=400 c=1000
tc g7-2 gen_dense r=400 c=1000
tc g7-3 gen_shapes n=400000 r=1000 c=400
tc g7-4 gen_shapes n=400000 r=200000 c=2
tc g7-5 gen_shapes n=123456 r=400 c=1000
tc g7-6 gen_shapes n=200100 r=400 c=1000
tc g7-7 gen_shapes n=100000 r=40 c=10000
tc g7-8 gen_shapes n=100000 r=4000 c=100
tc g7-9 gen_shapes n=50000 r=40000 c=10
tc g7-10 gen_dense r=40 c=10000
tc g7-11 gen_dense r=4000 c=100
tc g7-12 gen_dense r=40000 c=10


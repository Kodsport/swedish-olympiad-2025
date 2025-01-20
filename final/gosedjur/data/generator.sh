#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution olle.cpp
# use_solution theodor_bitset.cpp

compile gen_rand.py
compile gen_dense.py

samplegroup
limits maxn=10 maxq=10
sample 1

group group1 1
tc 1
tc g1-1 gen_rand n=10 r=5 c=4
tc g1-2 gen_dense r=5 c=4

group group2 1
tc g2-1 gen_rand n=100 r=50 c=40

group group3 1
tc g3-1 gen_rand n=1000 r=2000 c=2

group group4 1
tc g4-1 gen_rand n=10000 r=500 c=500

group group5 1
tc g5-1 gen_rand n=10000 r=500 c=500

group group6 1
tc g6-1 gen_rand n=10000 r=1000 c=1000
tc g6-2 gen_dense r=1000 c=1000


# tc g1-5 gen_rand n=1000 q=1000
# tc g1-6 gen_rand n=1000 q=1000
# tc g1-7 gen_rand n=1000 q=1000
# tc g1-8 gen_rand n=1000 q=1000
# tc g1-9 gen_rand n=1000 q=1000
# tc g1-10 gen_rand n=1000 q=1000
# tc g1-11 gen_rand n=1000 q=1000
# tc g1-12 gen_rand n=1000 q=1000

# tc g3-5 gen_rand n=200000 q=200000 c=1
# tc g3-6 gen_rand n=200000 q=200000 c=1
# tc g3-7 gen_rand n=200000 q=200000 c=1
# tc g3-8 gen_rand n=200000 q=200000 c=1
# tc g3-9 gen_rand n=200000 q=200000 c=1
# tc g3-10 gen_rand n=200000 q=200000 c=1 
# tc g3-11 gen_rand n=200000 q=200000 c=1
# tc g3-12 gen_rand n=200000 q=200000 c=1



# tc g4-6 gen_rand n=20000 q=20000
# tc g4-7 gen_rand n=20000 q=20000
# tc g4-8 gen_rand n=20000 q=20000
# tc g4-9 gen_rand n=20000 q=20000
# tc g4-10 gen_rand n=20000 q=20000
# tc g4-11 gen_rand n=20000 q=20000
# tc g4-12 gen_rand n=20000 q=20000




# tc g5-6 gen_rand n=200000 q=200000
# tc g5-7 gen_rand n=200000 q=200000
# tc g5-8 gen_rand n=200000 q=200000
# tc g5-9 gen_rand n=200000 q=200000
# tc g5-10 gen_rand n=200000 q=200000
# tc g5-11 gen_rand n=200000 q=200000
# tc g5-12 gen_rand n=200000 q=200000


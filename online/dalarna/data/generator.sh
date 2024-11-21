#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py 

samplegroup
sample 1

group group1 10
limits line=1
tc 1


group group2 13
limits pmax=1
tc g2-1 gen_rand n=100 pmax=1
tc g2-2 gen_rand n=20000 pmax=1
tc g2-3 gen_rand n=100000 pmax=1
tc g2-4 gen_rand pmax=1
tc g2-5 gen_rand pmax=1

group group3 23
limits nmax=6 pmax=5
tc g3-1 gen_rand n=4 pmax=5
tc g3-2 gen_rand n=6 pmax=5
tc g3-3 gen_rand n=6 pmax=5
tc g3-4 gen_rand n=6 pmax=5

group group4 23
limits nmax=1000 pmax=1000
tc g4-1 gen_rand n=1000 pmax=10
tc g4-2 gen_rand n=10 pmax=1000
tc g4-3 gen_rand n=1000 pmax=1000
tc g4-4 gen_rand n=1000 pmax=1000
tc g4-5 gen_rand n=1000 pmax=1000

group group5 23
limits nmax=1000
tc g5-1 gen_rand n=500 pmax=10000
tc g5-2 gen_rand n=1000 pmax=100000
tc g5-3 gen_rand n=900 
tc g5-4 gen_rand n=1000 
tc g5-5 gen_rand n=1000 

group group6 20
tc g6-1 gen_rand 
tc g6-2 gen_rand 
tc g6-3 gen_rand 
tc g6-4 gen_rand 
tc g6-5 gen_rand 


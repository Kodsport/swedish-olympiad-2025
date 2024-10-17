#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py 
compile gen_prefix.py

samplegroup
sample 1
sample 2
sample 3

group group1 10
limits mmin=0 mmax=0
tc 1

tc g1-1 gen_rand n=98 m=0
tc g1-2 gen_rand n=63 m=0


group group2 13
limits nmax=3 mmax=10
tc 1
tc 2
tc g2-1 gen_rand n=3 m=10
tc g2-2 gen_rand n=3 m=9
tc g2-3 gen_prefix n=3 m=10 p=0.2
tc g2-4 gen_prefix n=3 m=10 p=0.4


group group3 23
limits mmin=1 mmax=1
tc g3-1 gen_rand n=73 m=1
tc g3-2 gen_rand n=93 m=1
tc g3-3 gen_rand n=100 m=1

group group4 32
limits nmax=50 mmax=50
include_group group2
tc 3
tc g4-1 gen_rand n=50 m=50
tc g4-2 gen_rand n=47 m=33
tc g4-3 gen_rand n=44 m=47
tc g4-4 gen_prefix n=50 m=50 p=0.05
tc g4-5 gen_prefix n=48 m=49 p=0.2
tc g4-6 gen_prefix n=50 m=50 p=0.1 l=14
tc g4-7 gen_prefix n=50 m=50 p=0.05 r=True
tc g4-8 gen_prefix n=48 m=49 p=0.2 r=True
tc g4-9 gen_prefix n=50 m=50 p=0.1 l=12 r=True

group group5 22
include_group group1 group3 group4
tc g5-1 gen_rand n=100 m=100
tc g5-2 gen_rand n=97 m=83
tc g5-3 gen_rand n=94 m=97
tc g5-4 gen_prefix n=100 m=100 p=0.03
tc g5-5 gen_prefix n=96 m=100 p=0.07
tc g5-6 gen_prefix n=100 m=95 p=0.2
tc g5-7 gen_prefix n=99 m=99 p=0.03 l=15
tc g5-8 gen_prefix n=100 m=100 p=0.1 l=7
tc g5-9 gen_prefix n=100 m=100 p=0.03 r=True
tc g5-10 gen_prefix n=96 m=100 p=0.07 r=True
tc g5-11 gen_prefix n=100 m=95 p=0.2 r=True
tc g5-12 gen_prefix n=99 m=99 p=0.03 l=15 r=True
tc g5-13 gen_prefix n=100 m=100 p=0.1 l=7 r=True




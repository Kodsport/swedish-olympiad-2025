#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution arvid100.cpp

compile gen_rand.py 
compile gen_pyramid.py 

samplegroup
limits maxn=10 maxq=10
sample 1

group group1 13
limits maxn=1000 maxq=1000
tc 1
tc g1-1 gen_rand n=10 q=10
tc g1-2 gen_pyramid n=1000 q=1000
tc g1-3 gen_rand n=1000 q=1000
tc g1-4 gen_pyramid n=1000 q=1000
# tc g1-5 gen_rand n=1000 q=1000
# tc g1-6 gen_rand n=1000 q=1000
# tc g1-7 gen_rand n=1000 q=1000
# tc g1-8 gen_rand n=1000 q=1000
# tc g1-9 gen_rand n=1000 q=1000
# tc g1-10 gen_rand n=1000 q=1000
# tc g1-11 gen_rand n=1000 q=1000
# tc g1-12 gen_rand n=1000 q=1000

group group2 17
limits maxn=200000 maxq=200000
tc g2-1 gen_rand n=100000 q=100000
tc g2-2 gen_rand n=10000 q=200000
tc g2-3 gen_rand n=200000 q=200000 
tc g2-4 gen_rand n=200000 q=200000
# tc g2-5 gen_rand n=200000 q=200000
# tc g2-6 gen_rand n=200000 q=200000
# tc g2-7 gen_rand n=200000 q=200000
# tc g2-8 gen_rand n=200000 q=200000
# tc g2-9 gen_rand n=200000 q=200000
# tc g2-10 gen_rand n=200000 q=200000 
# tc g2-11 gen_rand n=200000 q=200000
# tc g2-12 gen_rand n=200000 q=200000

group group3 20
limits maxn=200000 maxq=200000
tc g3-1 gen_rand n=100000 q=100000 c=1
tc g3-2 gen_pyramid n=200000 q=200000 c=1
tc g3-3 gen_rand n=200000 q=200000 c=1 
tc g3-4 gen_pyramid n=200000 q=200000 c=1
# tc g3-5 gen_rand n=200000 q=200000 c=1
# tc g3-6 gen_rand n=200000 q=200000 c=1
# tc g3-7 gen_rand n=200000 q=200000 c=1
# tc g3-8 gen_rand n=200000 q=200000 c=1
# tc g3-9 gen_rand n=200000 q=200000 c=1
# tc g3-10 gen_rand n=200000 q=200000 c=1 
# tc g3-11 gen_rand n=200000 q=200000 c=1
# tc g3-12 gen_rand n=200000 q=200000 c=1

group group4 23
limits maxn=40000 maxq=40000
tc g4-1 gen_rand n=10000 q=10000
tc g4-2 gen_pyramid n=10000 q=20000
tc g4-3 gen_rand n=40000 q=40000
tc g4-4 gen_pyramid n=40000 q=40000
tc g4-5 gen_rand n=40000 q=40000
# tc g4-6 gen_rand n=20000 q=20000
# tc g4-7 gen_rand n=20000 q=20000
# tc g4-8 gen_rand n=20000 q=20000
# tc g4-9 gen_rand n=20000 q=20000
# tc g4-10 gen_rand n=20000 q=20000
# tc g4-11 gen_rand n=20000 q=20000
# tc g4-12 gen_rand n=20000 q=20000


group group5 27
limits maxn=200000 maxq=200000
tc g5-1 gen_pyramid n=100000 q=100000
tc g5-2 gen_rand n=100000 q=200000
tc g5-3 gen_pyramid n=200000 q=200000
tc g5-4 gen_rand n=200000 q=200000
tc g5-5 gen_pyramid n=200000 q=200000
# tc g5-6 gen_rand n=200000 q=200000
# tc g5-7 gen_rand n=200000 q=200000
# tc g5-8 gen_rand n=200000 q=200000
# tc g5-9 gen_rand n=200000 q=200000
# tc g5-10 gen_rand n=200000 q=200000
# tc g5-11 gen_rand n=200000 q=200000
# tc g5-12 gen_rand n=200000 q=200000


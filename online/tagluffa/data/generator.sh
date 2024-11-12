#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution joshua_optimized.cpp

compile gen_rand.py

samplegroup
limits maxn=10 maxk=10 maxt=10
sample 1

group group1 5
limits maxn=100 maxk=100 maxt=100
tc 1

tc g1-1 gen_rand n=50 k=10 t=100 maxd=1
tc g1-2 gen_rand n=50 k=16 t=100 maxd=2
tc g1-3 gen_rand n=50 k=25 t=100 maxd=10
tc g1-4 gen_rand n=50 k=50 t=100 maxd=5

group group2 10
limits maxn=50 maxk=50 maxt=1000000000
tc g2-1 gen_rand n=50 k=50 t=1000000000 maxd=1000
tc g2-2 gen_rand n=50 k=50 t=1000000000 maxd=1000000

group group3 10
limits maxn=1000 maxk=200 maxt=1000000000
tc g3-1 gen_rand n=1000 k=200 t=1000000000 maxd=1000
tc g3-2 gen_rand n=1000 k=200 t=1000000000 maxd=1000000

group group4 10
limits maxn=2000 maxk=2000 maxt=1000000000
tc g4-1 gen_rand n=2000 k=2000 t=1000000000 maxd=1000
tc g4-2 gen_rand n=2000 k=2000 t=1000000000 maxd=1000000

group group5 10
limits maxn=100000 maxk=50 maxt=1000000000
tc g5-1 gen_rand n=100000 k=50 t=1000000000 maxd=1000
tc g5-2 gen_rand n=100000 k=50 t=1000000000 maxd=1000000

group group6 10
limits maxn=30000 maxk=30000 maxt=1000000000
tc g6-1 gen_rand n=30000 k=30000 t=1000000000 maxd=1000
tc g6-2 gen_rand n=30000 k=30000 t=1000000000 maxd=1000000

group group7 10
limits maxn=100000 maxk=100000 maxt=1000000000
tc g7-1 gen_rand n=100000 k=100000 t=1000000000 maxd=1000
tc g7-2 gen_rand n=100000 k=100000 t=1000000000 maxd=1000000

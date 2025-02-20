#!/bin/bash
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited
use_solution emil.cpp

compile gen_rand.py #converted
compile gen_path.py
compile gen_dumbbell.py
compile gen_starry.py
compile gen_smalldeg.py pypy3
compile gen_line.py
compile gen_line2.py
compile gen_line3.py

samplegroup
limits maxn=10 maxm=10 maxt=10
#sample 1

group group1 6
limits maxe=1
#tc 1
tc g1-1 gen_rand n=10 m=1 t=100 maxt=10 maxe=1
tc g1-2 gen_rand n=10 m=2 t=100 maxt=10 maxe=1

tc g1-3 gen_rand n=200000 m=100000 t=1000000000 maxt=1000000000 maxe=1


group group2 5
limits maxm=1
tc g1-1
tc g2-1 gen_rand n=10 m=1 t=100 maxt=10 maxe=1000

tc g2-3 gen_rand n=200000 m=1 t=1000000000 maxt=1000000000 maxe=100000

group group3 10
include_group group2
limits maxm=2
tc g1-2
tc g2-1 gen_rand n=10 m=2 t=100 maxt=10 maxe=1000

tc g2-3 gen_rand n=200000 m=2 t=1000000000 maxt=1000000000 maxe=100000

group group4 23
include_group group3
limits maxm=20
tc g4-1 gen_rand n=11 m=10 t=1000 maxt=1000 maxe=100000
tc g4-2 gen_rand n=21 m=20 t=1000 maxt=1000 maxe=100000

tc g4-3 gen_rand n=200000 m=20 t=1000000000 maxt=1000000000 maxe=100000


# Binärt träd
group group5 17
limits binary=1



group group6 39
include_group group1
include_group group4
include_group group5
#limits maxn=100000 maxk=100000 maxt=1000000000
tc g6-1 gen_rand n=200000 m=199999 t=1000000000 maxt=1000000000 maxe=100000
tc g6-2 gen_rand n=198007 m=99999 t=1000000000 maxt=1000000000 maxe=100000


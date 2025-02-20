#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution linear_query.cpp

# TODO: graph with many articulation points

compile gen_slowrand.py
compile gen_lowdeg.py
compile gen_starry.py

group group1 5
limits maxn=50 maxm=50 maxq=100
tc g1-1 gen_slowrand n=5 m=5 q=100
tc g1-2 gen_slowrand n=6 m=8 q=10
tc g1-3 gen_slowrand n=10 m=30 q=100
tc g1-4 gen_slowrand n=30 m=40 q=100


group group2 5
include_group group1
limits maxn=500 maxm=500 maxq=10000
tc g2-1 gen_starry n=500 m=500 q=10000
tc g2-2 gen_slowrand n=100 m=500 q=10000
tc g2-3 gen_slowrand n=200 m=500 q=10000
tc g2-4 gen_slowrand n=100 m=500 q=10000
# high degree testcases

group group3 5
limits maxn=100000 maxm=100000 maxq=1 maxdeg=5
tc g3-1 gen_lowdeg n=100000 m=100000 maxdeg=5 q=1

group group4 5
limits maxn=100000 maxm=100000 maxq=500
tc g4-1 gen_starry n=100000 m=100000 q=500
# high degree testcases

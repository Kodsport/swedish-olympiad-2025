#!/bin/bash
. ../../../testdata_tools/gen.sh

use_solution full.cpp

compile gen.py 

# Generate answers to sample cases
samplegroup
sample 1

INF=1000000000

group group1 7
limits maxN=3
tc g1-01 gen maxn=3 maxg=3 E=1 mode=rand
tc g1-02 gen maxn=3 maxg=$INF E=$INF mode=rand
tc g1-03 gen maxn=3 diff=1 E=1 mode=arit
tc g1-04 gen maxn=3 diff=10 mode=arit
tc g1-05 gen maxn=3 diff=1 rev=1 mode=arit
tc ge-06 gen maxn=3 diff=1000 rev=1 mode=arit
tc g1-07 gen maxn=3 maxg=$INF mult=3 mode=expo
tc g1-08 gen maxn=3 maxg=$INF mult=5 E=$INF mode=expo
tc g1-09 gen maxn=3 maxg=$INF mode=large
tc_manual ../manual/n3_1.in
tc_manual ../manual/n3_2.in

group group2 12
limits maxN=15
include_group group1
tc 1
tc g2-01 gen maxn=15 maxg=3 mode=rand
tc g2-02 gen maxn=15 maxg=$INF E=$INF mode=rand
tc g2-03 gen maxn=15 diff=1 mode=arit
tc g2-04 gen maxn=15 diff=10 n=15 mode=arit
tc g2-05 gen maxn=15 diff=1 n=15 rev=1 mode=arit
tc g2-06 gen maxn=15 diff=1000 rev=1 mode=arit
tc g2-07 gen maxn=15 maxg=$INF mult=3 mode=expo
tc g2-08 gen maxn=15 maxg=$INF mode=group
tc g2-09 gen maxn=15 maxg=$INF ratio=0.50 mode=2val
tc g2-10 gen maxn=15 maxg=$INF ratio=0.01 mode=2val
tc g2-11 gen maxn=15 maxg=$INF mode=large

group group3 23
limits maxN=5000
include_group group2
tc g3-01 gen maxn=5000 maxg=3 mode=rand
tc g3-02 gen maxn=5000 maxg=$INF E=$INF mode=rand
tc g3-03 gen maxn=5000 diff=1 mode=arit
tc g3-04 gen maxn=5000 diff=10 mode=arit
tc g3-05 gen maxn=5000 diff=1 rev=1 mode=arit
tc g3-06 gen maxn=5000 diff=1000 rev=1 mode=arit
tc g3-07 gen maxn=5000 maxg=$INF mult=3 mode=expo
tc g3-08 gen maxn=5000 maxg=$INF mode=group
tc g3-09 gen maxn=5000 maxg=$INF ratio=0.50 mode=2val
tc g3-10 gen maxn=5000 maxg=$INF ratio=0.01 mode=2val
tc g3-11 gen maxn=5000 maxg=$INF mode=large
tc g3-12 gen n=5000 maxg=$INF E=$INF mode=rand

group group4 17
limits diff=2
tc g2-09
tc g2-10
tc g3-09
tc g3-10
tc g4-01 gen maxn=500000 maxg=$INF ratio=0.50 E=10 mode=2val
tc g4-02 gen maxn=500000 maxg=$INF ratio=0.10 E=2 mode=2val
tc g4-03 gen maxn=500000 maxg=$INF ratio=0.01 mode=2val
tc g4-04 gen maxn=500000 maxg=$INF small_range=1 mode=large
tc g4-05 gen maxn=500000 mode=same
tc g4-06 gen maxn=500000 value=$INF mode=same
tc g4-07 gen n=500000 maxg=$INF ratio=0.80 E=$INF mode=2val

group group5 41
include_group group3
include_group group4
tc g5-01 gen maxn=500000 maxg=3 mode=rand
tc g5-02 gen maxn=500000 maxg=$INF E=$INF mode=rand
tc g5-03 gen maxn=500000 diff=1 mode=arit
tc g5-04 gen maxn=500000 diff=10 mode=arit
tc g5-05 gen maxn=500000 diff=1 rev=1 mode=arit
tc g5-06 gen maxn=500000 diff=1000 rev=1 mode=arit
tc g5-07 gen maxn=500000 maxg=$INF mult=3 mode=expo
tc g5-08 gen maxn=500000 maxg=$INF mode=group
tc g5-09 gen maxn=500000 maxg=$INF mode=large
tc g5-10 gen n=500000 maxg=$INF mult=4 E=$INF mode=expo
tc g5-11 gen n=500000 maxg=$INF E=$INF mode=rand

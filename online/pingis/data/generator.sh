#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../testdata_tools/gen.sh

#ulimit -s unlimited

#REQUIRE_SAMPLE_REUSE=0

use_solution emil.py

compile gen_rand.py

samplegroup
#limits maxlen=32 maxdiff=-1 unique=false
sample 1
sample 2
sample 3

group group1 8
limits maxK=2
tc 1
tc 2
tc 3
#tc_manual ../manual/sample3.in
tc_manual ../manual/n1.in
tc g1-01 gen_rand minK=0 maxK=0 mode=solveable
tc g1-02 gen_rand minK=2 maxK=2 mode=solveable
tc g1-03 gen_rand minK=1 maxK=1 mode=solveable
tc g1-04 gen_rand minK=1 maxK=1 mode=random
tc g1-05 gen_rand minK=2 maxK=2 mode=random
tc_manual ../manual/n4_1.in
tc g1-06 gen_rand minK=2 maxK=2 mode=almost
tc g1-07 gen_rand minK=2 maxK=2 mode=random
tc_manual ../manual/n4_2.in
tc g1-08 gen_rand minK=2 maxK=2 mode=random
tc g1-09 gen_rand minK=2 maxK=2 mode=zeros
tc_manual ../manual/n4_3.in
tc g1-10 gen_rand minK=2 maxK=2 mode=solveable
tc_manual ../manual/n4_4.in


group group2 12
limits maxK=3
include_group group1
tc g2-01 gen_rand minK=3 maxK=3 mode=solveable
tc g2-02 gen_rand minK=3 maxK=3 mode=random
tc g2-03 gen_rand minK=3 maxK=3 mode=almost
tc g2-04 gen_rand minK=3 maxK=3 mode=almost
tc g2-05 gen_rand minK=3 maxK=3 mode=solveable
tc g2-06 gen_rand minK=3 maxK=3 mode=solveable
tc g2-07 gen_rand minK=3 maxK=3 mode=solveable
tc g2-08 gen_rand minK=3 maxK=3 mode=solveable

group group3 18
limits maxK=7
include_group group2
tc_manual ../manual/n16_1.in
tc_manual ../manual/n16_2.in
tc g3-01 gen_rand minK=4 maxK=4 mode=solveable
tc g3-02 gen_rand minK=7 maxK=7 mode=random
tc g3-03 gen_rand minK=7 maxK=7 mode=almost
tc g3-04 gen_rand minK=6 maxK=6 mode=solveable
tc g3-05 gen_rand minK=5 maxK=5 mode=solveable
tc g3-06 gen_rand minK=7 maxK=7 mode=solveable
tc g3-07 gen_rand minK=7 maxK=7 mode=solveable
tc g3-08 gen_rand minK=7 maxK=7 mode=solveable
tc g3-09 gen_rand minK=4 maxK=4 mode=solveable sorted=1
tc g3-10 gen_rand minK=7 maxK=7 mode=solveable sorted=1

group group4 12
limits maxK=11
include_group group3
tc g4-01 gen_rand minK=8 maxK=11 mode=solveable
tc g4-02 gen_rand minK=8 maxK=11 mode=solveable
tc g4-03 gen_rand minK=8 maxK=11 mode=solveable
tc g4-04 gen_rand minK=8 maxK=11 mode=almost
tc g4-05 gen_rand minK=8 maxK=11 mode=random
tc g4-06 gen_rand minK=11 maxK=11 mode=solveable
tc g4-07 gen_rand minK=11 maxK=11 mode=solveable
tc g4-08 gen_rand minK=11 maxK=11 mode=almost 
tc g4-09 gen_rand minK=11 maxK=11 mode=solveable sorted=1

group group5 12
limits sorted=1
tc 2
tc 3
tc g1-01
tc g1-04
tc g1-09
tc n1
tc n4_1
tc g2-04
tc g3-09
tc g3-10
tc g4-09
tc g5-01 gen_rand minK=12 maxK=12 mode=solveable sorted=1
tc g5-02 gen_rand minK=15 maxK=15 mode=solveable sorted=1
tc g5-03 gen_rand minK=19 maxK=19 mode=solveable sorted=1
tc g5-04 gen_rand minK=14 maxK=14 mode=almost sorted=1
tc g5-05 gen_rand minK=18 maxK=18 mode=solveable sorted=1
tc g5-06 gen_rand minK=19 maxK=19 mode=almost sorted=1
tc g5-07 gen_rand minK=17 maxK=17 mode=solveable sorted=1
tc g5-08 gen_rand minK=19 maxK=19 mode=zeros

group group6 38
tc 1
limits maxK=19
include_group group4
include_group group5
tc g6-01 gen_rand minK=12 maxK=15 mode=solveable
tc g6-02 gen_rand minK=16 maxK=19 mode=solveable
tc g6-03 gen_rand minK=19 maxK=19 mode=solveable
tc g6-04 gen_rand minK=19 maxK=19 mode=almost
tc g6-05 gen_rand minK=19 maxK=19 mode=random
tc g6-06 gen_rand minK=19 maxK=19 mode=solveable
tc g6-07 gen_rand minK=19 maxK=19 mode=solveable

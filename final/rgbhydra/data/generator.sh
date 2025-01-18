#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_rand.py

samplegroup
sample 1
sample 2
sample 3
sample 4

MAXX=$((10**18))

group group1 20
limits R_max=10 B_max=10 G_max=10 k_max=10
tc 1
tc 2
tc 3
tc g1-01 gen_rand R=1 B=0 G=0 k=0
tc g1-02 gen_rand R=1 B=0 G=0 k=1
tc g1-03 gen_rand R=2 B=0 G=0 k=10
tc g1-04 gen_rand R=0 B=5 G=0 k=10
tc g1-05 gen_rand R=0 G=0 B=3 k=10
tc g1-06 gen_rand R=0 G=10 B=5 k=0
tc g1-07 gen_rand R=3 G=4 B=5 k=10
tc g1-08 gen_rand R=9 G=9 B=9 k=10
tc g1-09 gen_rand R=10 G=10 B=10 k=10
tc g1-10 gen_rand R=9 G=0 B=9 k=10
tc g1-11 gen_rand R=7 G=1 B=0 k=10
tc g1-12 gen_rand R=0 G=7 B=0 k=0
tc g1-13 gen_rand R=0 G=0 B=4 k=0

group group2 15
limits smallK=1
tc 2
tc 3
tc g1-01 
tc g1-06
tc g1-09
tc g1-12
tc g1-13
tc g2-01 gen_rand R=$MAXX B=0 G=0 k=0
tc g2-02 gen_rand R=$MAXX B=10000000 G=10000000 k=10000000
tc g2-03 gen_rand R=98765432 B=3 G=2 k=1
tc g2-04 gen_rand R=98765432 B=8765432 G=8765432 k=3765431
tc g2-05 gen_rand R=23999999 B=22765432 G=23765432 k=4465431
tc g2-06 gen_rand R=$MAXX B=$MAXX G=$MAXX k=$MAXX
tc g2-07 gen_rand R=99995125 G=99359995 B=99999999 k=0
tc g2-08 gen_rand R=99999999 G=9999999 B=9999999 k=123
tc g2-09 gen_rand R=99999999999123499 B=99999999999124499 G=99999999999123599 k=99999999999123499
tc g2-10 gen_rand R=0 B=99999999999124499 G=0 k=0
tc g2-11 gen_rand R=0 B=0 G=99999999999124399 k=0
tc g2-12 gen_rand R=0 B=33999999999124499 G=499999999912449 k=0
tc g2-13 gen_rand R=0 B=399999999912449 G=44999999999124499 k=0

group group3 10
limits R_max=0
tc 1
tc g1-04
tc g1-06
tc g1-12
tc g1-13
tc g2-10 
tc g2-11 
tc g2-12 
tc g2-13
tc g3-01 gen_rand R=0 B=1 G=1 k=91725827
tc g3-02 gen_rand R=0 G=1 B=0 k=$MAXX
tc g3-03 gen_rand R=0 G=30000000 B=30000000 k=$MAXX
tc g3-04 gen_rand R=0 G=30000000 B=2 k=0
tc g3-05 gen_rand R=0 G=100203 B=20005004 k=1092701
tc g3-06 gen_rand R=0 G=0 B=1 k=7724188

group group4 10
limits G_max=0
tc 1
tc g1-01 
tc g1-02
tc g1-03
tc g1-04
tc g1-10
tc g1-13
tc g2-01
tc g2-10
tc g3-06
tc g4-01 gen_rand R=1 G=0 B=19250179 k=9999999
tc g4-02 gen_rand R=12581298 G=0 B=0 k=$MAXX
tc g4-03 gen_rand R=1258 G=0 B=1251890 k=$MAXX
tc g4-04 gen_rand R=8521258 G=0 B=1234 k=123457
tc g4-05 gen_rand R=8521758 G=0 B=71502987 k=443457

group group5 10
limits B_max=0
tc g1-01
tc g1-02 
tc g1-03
tc g1-11
tc g1-12
tc g2-01
tc g2-11
tc g3-02
tc g4-02
tc g5-01 gen_rand R=1 G=19250179 B=0 k=9999999
tc g5-02 gen_rand R=1257 G=1251890 B=0 k=$MAXX
tc g5-03 gen_rand R=8521258 G=1234 B=0 k=123457
tc g5-04 gen_rand R=8521758 G=71502987 B=0 k=443457

group group6 35
include_group sample
include_group group1
include_group group2
include_group group3
include_group group4
include_group group5
tc g6-01 gen_rand R=99125 G=9935995 B=9999999 k=12566666
tc g6-02 gen_rand R=99125 G=99 B=1 k=1256655
tc g6-03 gen_rand 
tc g6-04 gen_rand 
tc g6-05 gen_rand R=99999999999 G=9999999999 B=9999999999 k=79999999999
tc g6-06 gen_rand R=1 B=529 G=15 k=99999999999123499

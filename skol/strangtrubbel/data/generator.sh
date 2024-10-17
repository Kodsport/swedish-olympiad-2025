#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution victor.cpp

compile gen_rand.py

samplegroup
limits maxlen=32 maxdiff=-1 unique=0
sample 1
sample 2

group group1 10
limits maxlen=26 maxdiff=-1 unique=1

for i in {1..10}
do
tc g1-$i gen_rand maxlen=26 maxdiff=-1 unique=1

done


group group2 15
limits maxlen=32 maxdiff=1 unique=0
for i in {1..10}
do
tc g2-$i gen_rand maxlen=32 maxdiff=1 unique=0

done

group group3 30
limits maxlen=32 maxdiff=3 unique=0
for i in {1..12}
do
tc g3-$i gen_rand maxlen=32 maxdiff=3 unique=0

done

group group4 45
include_group group1
include_group group2
include_group group3
include_group sample
limits maxlen=32 maxdiff=-1 unique=0
include_group group2 
for i in {1..15}
do
tc g4-$i gen_rand maxlen=32 maxdiff=-1 unique=0

done


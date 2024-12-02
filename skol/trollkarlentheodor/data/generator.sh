#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2

group group1 20
limits seta=0
for i in {1..4}
do
tc g1-$i gen_rand maxh=32 seta=0

done
tc g1-5 gen_rand sets=4 seta=0
tc g1-6 gen_rand sets=1 seta=0


group group2 40
limits maxh=100
include_group sample
for i in {1..6}
do
tc g2-$i gen_rand maxh=100

done
tc g2-7 gen_rand maxh=100 seta=0
tc g2-8 gen_rand maxh=100 seta=987893125

group group3 40
include_group group1
include_group group2
for i in {1..6}
do
tc g3-$i gen_rand 

done
tc g3-7 gen_rand sets=5 seta=2
tc g3-8 gen_rand sets=2 seta=4
tc g3-9 gen_rand sets=1 seta=1
tc g3-10 gen_rand seta=1000000000
tc g3-11 gen_rand sets=3 seta=873892164
tc g3-12 gen_rand sets=783921798


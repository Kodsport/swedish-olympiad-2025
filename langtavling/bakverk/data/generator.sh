#!/usr/bin/env bash

REQUIRE_SAMPLE_REUSE=0
. ./gen.sh  # ../../../testdata_tools/gen.sh
# Modified testdata_tools from "Make them meet"

compile gen_rand.py

use_solution solution.cpp

INF=1000000000000000000

samplegroup
sample_manual 1
sample_manual 2

group group1 20
limits x=20
tc small-1 gen_rand x=1 y=1
tc small-2 gen_rand x=1 y=20
tc small-3 gen_rand x=5 y=4
tc small-4 gen_rand x=20 y=1
tc small-5 gen_rand x=20 y=2
tc small-6 gen_rand x=20 y=19
tc small-7 gen_rand x=20 y=20
tc small-8 gen_rand x=20 y=17
tc small-9 gen_rand x=20 y=10
tc small-10 gen_rand x=17 y=13

group group2 80
include_group group1

tc max-one gen_rand x=$INF y=1
tc max-prime gen_rand x=$INF y=1000000007
tc max-small-1 gen_rand x=$INF y=2
tc max-small-2 gen_rand x=$INF y=3
tc max-small-3 gen_rand x=$INF y=4
tc max-small-4 gen_rand x=$INF y=10
tc max-small-5 gen_rand x=$INF y=4217
tc max-small-6 gen_rand x=$INF y=32193
tc max-small-7 gen_rand x=$INF y=132141
tc max-max gen_rand x=$INF y=$INF
tc max-large-1 gen_rand x=$INF y=$(($INF-1))
tc max-large-2 gen_rand x=$INF y=$(($INF-2))
tc max-large-3 gen_rand x=$INF y=$(($INF-11))
tc max-large-4 gen_rand x=$INF y=$(($INF-12311))
tc max-large-5 gen_rand x=$INF y=$(($INF-1000000007))
tc max-half gen_rand x=$INF y=$(($INF/2))

for i in {1..40}; do
    tc max-random-$i gen_rand x=$INF
done

for i in {1..40}; do
    tc random-$i gen_rand x=$INF
done



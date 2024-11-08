#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
. ../../../testdata_tools/gen.sh

use_solution joshua.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2

# Intentionally do not merge groups to see what solutions actually get during skolkval

group group1 20
limits maxn=10 b=3
tc_manual ../manual/secret_1.in

group group2 20
limits maxn=100000 b=2
tc_manual ../manual/secret_2.in

group group3 20
limits maxn=100000
tc_manual ../manual/secret_3.in

group group4 20
tc_manual ../manual/secret_4.in

group group5 20
tc_manual ../manual/secret_5.in

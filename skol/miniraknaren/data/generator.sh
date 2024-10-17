#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution baseconversion.cpp

compile gen_rand.py


group group1 20
limits maxn=10 b=3
tc_manual ../manual/1.in

group group2 20
limits maxn=100000 b=2
tc_manual ../manual/2.in

group group3 20
limits maxn=100000
tc_manual ../manual/3.in

group group4 20
limits maxn=100000
tc_manual ../manual/4.in

group group5 20
tc_manual ../manual/5.in

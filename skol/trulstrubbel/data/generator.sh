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

group group1 40
limits win_instant=1
tc 1
tc 2
tc_manual ../manual_data/secret_01.in
tc_manual ../manual_data/secret_02.in
tc_manual ../manual_data/m1.in

group group2 60
include_group sample
tc_manual ../manual_data/secret_03.in
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in
tc g2-1 gen_rand
tc g2-2 gen_rand
tc g2-3 gen_rand
tc g2-4 gen_rand

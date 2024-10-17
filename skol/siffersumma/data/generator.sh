#!/usr/bin/env bash
REQUIRE_SAMPLE_REUSE=0
PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution theodor.cpp


samplegroup 
sample 1
sample 2
sample 3

group group1 40
tc_manual ../manual_data/secret_01.in
tc_manual ../manual_data/secret_02.in



group group2 60
tc_manual ../manual_data/secret_03.in
tc_manual ../manual_data/secret_04.in
tc_manual ../manual_data/secret_05.in





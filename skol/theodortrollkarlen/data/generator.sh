REQUIRE_SAMPLE_REUSE=0
#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution olle.cpp

samplegroup
sample 1
sample 2

group group1 20
tc_manual ../manual_data/secret_01.in

group group2 20
tc_manual ../manual_data/secret_02.in

group group3 20
tc_manual ../manual_data/secret_03.in

group group4 20
tc_manual ../manual_data/secret_04.in

group group5 20
tc_manual ../manual_data/secret_05.in

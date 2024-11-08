REQUIRE_SAMPLE_REUSE=0
#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution olle.cpp

samplegroup
limits maxa=5 maxnk=5 maxs=5
sample 1
sample 2

group group1 20
limits maxa=0 maxnk=5 maxs=5
tc_manual ../manual_data/secret_01.in

group group2 20
limits maxa=0 maxnk=70 maxs=10
include_group group1
tc_manual ../manual_data/secret_02.in

group group3 20
limits maxa=150 maxnk=150 maxs=150
include_group group2
tc_manual ../manual_data/secret_03.in

group group4 20
limits maxa=1000 maxnk=1000 maxs=1000
include_group group3
tc_manual ../manual_data/secret_04.in

group group5 20
limits maxa=200000 maxnk=200000 maxs=200000
include_group group4
tc_manual ../manual_data/secret_05.in

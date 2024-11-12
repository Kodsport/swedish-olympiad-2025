#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution ../generate_secret.cpp

compile generate.py

#samplegroup


group group1 7
limits n=100 k=510
tc g1-1 generate n=100 k=510 mode=random
tc g1-2 generate n=100 k=510 mode=random

group group2 11
limits n=100 k=410
include_group group1
tc g2-1 generate n=100 k=410 mode=random
tc g2-2 generate n=100 k=410 mode=random

group group3 16
limits n=100 k=310
include_group group2
tc g3-1 generate n=100 k=310 mode=random
tc g3-2 generate n=100 k=310 mode=random

group group4 15
limits n=100 k=275
include_group group3
tc g4-1 generate n=100 k=275 mode=random
tc g4-2 generate n=100 k=275 mode=random

group group5 5
limits n=100 k=250 evenends=1
tc g5-1 generate n=100 k=250 mode=evenends
tc g5-2 generate n=100 k=250 mode=evenends

group group6 5
limits n=100 k=250 lefteven=1
tc g6-1 generate n=100 k=250 mode=lefteven
tc g6-2 generate n=100 k=250 mode=lefteven

group group7 5
limits n=100 k=250 size1=1
tc g7-1 generate n=100 k=250 mode=size1
tc g7-2 generate n=100 k=250 mode=size1
tc g7-3 generate n=100 k=250 mode=size1

group group8 21
limits n=100 k=250
include_group group4
include_group group5
include_group group6
include_group group7
tc g8-1 generate n=100 k=250 mode=random
tc g8-2 generate n=100 k=250 mode=random

group group9 15
limits n=100 k=225
include_group group8
tc g9-1 generate n=100 k=225 mode=random
tc g9-2 generate n=100 k=225 mode=random
tc g9-3 generate n=100 k=225 mode=size1
tc g9-5 generate n=100 k=225 mode=size1
tc g9-6 generate n=100 k=225 mode=size1

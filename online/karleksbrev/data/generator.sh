#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution ../generate_secret.cpp

compile generate.py

group group1 7
limits k=510
tc g1-1 generate k=510 mode=random
tc g1-2 generate k=510 mode=random

group group2 11
limits k=410
tc g2-1 generate k=410 mode=random
tc g2-2 generate k=410 mode=random

group group3 21
limits k=310
tc g3-1 generate k=310 mode=random
tc g3-2 generate k=310 mode=random
tc g3-3 generate k=310 mode=size1
tc g3-4 generate k=310 mode=size1

group group4 0
limits k=310 evenends=1
tc g4-1 generate k=310 mode=evenends
tc g4-2 generate k=310 mode=evenends

group group5 0
limits k=310 lefteven=1
tc g5-1 generate k=310 mode=lefteven
tc g5-2 generate k=310 mode=lefteven

group group6 5
limits k=250 size1=1
tc g6-1 generate k=250 mode=size1
tc g6-2 generate k=250 mode=size1
tc g6-3 generate k=250 mode=size1

group group7 25
limits k=250
tc g7-1 generate k=250 mode=random
tc g7-2 generate k=250 mode=random
tc g7-3 generate k=250 mode=size1
tc g7-4 generate k=250 mode=size1

group group8 13
limits k=210
tc g8-1 generate k=210 mode=random
tc g8-2 generate k=210 mode=random
tc g8-3 generate k=210 mode=size1
tc g8-4 generate k=210 mode=size1
tc g8-5 generate k=210 mode=size1

group group9 18
limits k=150
tc g9-1 generate k=150 mode=random
tc g9-2 generate k=150 mode=random
tc g9-3 generate k=150 mode=size1
tc g9-4 generate k=150 mode=size1
tc g9-5 generate k=150 mode=size1

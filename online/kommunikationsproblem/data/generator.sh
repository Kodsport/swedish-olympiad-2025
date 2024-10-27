#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution generate_secret.cpp

compile generate.py

#samplegroup


group group01 3
limits n=1 k=100
tc g1-1 generate n=1 k=100 mode=random
tc g1-2 generate n=1 k=100 mode=random seed=5

group group02 7
limits n=2 k=100
# Every possible input for n=2
tc g2-1 generate n=2 k=100 mode=random seed=1
tc g2-2 generate n=2 k=100 mode=random seed=3
tc g2-3 generate n=2 k=100 mode=random seed=4
tc g2-4 generate n=2 k=100 mode=random seed=5
tc g2-5 generate n=2 k=100 mode=random seed=7
tc g2-6 generate n=2 k=100 mode=random seed=13
tc g2-7 generate n=2 k=100 mode=random seed=15
tc g2-8 generate n=2 k=100 mode=random seed=16
tc g2-9 generate n=2 k=100 mode=random seed=21
tc g2-10 generate n=2 k=100 mode=random seed=24
tc g2-11 generate n=2 k=100 mode=random seed=46
tc g2-12 generate n=2 k=100 mode=random seed=47

group group03 7
limits n=100 k=510
tc g3-1 generate n=100 k=510 mode=random
tc g3-2 generate n=100 k=510 mode=random

group group04 8
limits n=100 k=410
tc g4-1 generate n=100 k=410 mode=random
tc g4-2 generate n=100 k=410 mode=random

group group05 9
limits n=100 k=310
tc g5-1 generate n=100 k=310 mode=random
tc g5-2 generate n=100 k=310 mode=random

group group06 6
limits n=100 k=250 evenends=1
tc g6-1 generate n=100 k=250 mode=evenends
tc g6-2 generate n=100 k=250 mode=evenends

group group07 9
limits n=100 k=250 lefteven=1
include_group group06
tc g7-1 generate n=100 k=250 mode=lefteven
tc g7-2 generate n=100 k=250 mode=lefteven

group group08 15
limits n=100 k=250 size1=1
tc g8-1 generate n=100 k=250 mode=size1
tc g8-2 generate n=100 k=250 mode=size1
tc g8-3 generate n=100 k=250 mode=size1
tc g8-4 generate n=100 k=250 mode=size1

group group09 21
limits n=100 k=250
include_group group07
include_group group08
tc g9-1 generate n=100 k=250 mode=random
tc g9-2 generate n=100 k=250 mode=random

group group10 15
limits n=100 k=150
tc g10-1 generate n=100 k=150 mode=random
tc g10-2 generate n=100 k=150 mode=random
tc g10-3 generate n=100 k=150 mode=size1
tc g10-5 generate n=100 k=150 mode=size1
tc g10-6 generate n=100 k=150 mode=size1

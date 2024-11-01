#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution joshua.cpp

compile gen_rand.py 

group group1 5
limits maxr=30 maxq=1
tc_manual ../manual/kill_harry
tc_manual ../manual/kill_harry_oneshot
tc_manual ../manual/kill_joshua
tc g1-1 gen_rand r=30 c=30 q=100
tc g1-2 gen_rand r=30 c=30 q=100
tc g1-3 gen_rand r=30 c=30 q=100
tc g1-4 gen_rand r=30 c=30 q=100
tc g1-5 gen_rand r=30 c=30 q=100
tc g1-6 gen_rand r=30 c=30 q=100
tc g1-7 gen_rand r=30 c=30 q=100
tc g1-8 gen_rand r=30 c=30 q=100
tc g1-9 gen_rand r=30 c=30 q=100 snake=1
tc g1-10 gen_rand r=30 c=30 q=100 pockets=1
tc g1-11 gen_rand r=30 c=30 q=100 pockets=3

group group2 10
limits maxr=30 maxq=1000
include_group group1
tc g2-1 gen_rand r=30 c=30 q=1000
tc g2-2 gen_rand r=30 c=30 q=1000
tc g2-3 gen_rand r=30 c=30 q=1000
tc g2-4 gen_rand r=30 c=30 q=1000
tc g2-5 gen_rand r=30 c=30 q=1000
tc g2-6 gen_rand r=30 c=30 q=1000
tc g2-7 gen_rand r=30 c=30 q=1000
tc g2-8 gen_rand r=30 c=30 q=1000
tc g2-9 gen_rand r=30 c=30 q=1000 snake=1
tc g2-10 gen_rand r=30 c=30 q=1000 pockets=1
tc g2-11 gen_rand r=30 c=30 q=1000 pockets=3

group group3 40
limits maxr=100 maxq=1
#include_group group1
tc kill_harry
tc kill_harry_oneshot
tc kill_joshua
tc g3-1 gen_rand r=100 c=100 q=1
tc g3-2 gen_rand r=100 c=100 q=1
tc g3-3 gen_rand r=100 c=100 q=1
tc g3-4 gen_rand r=100 c=100 q=1
tc g3-5 gen_rand r=100 c=100 q=1
tc g3-6 gen_rand r=100 c=100 q=1
tc g3-7 gen_rand r=100 c=100 q=1
tc g3-8 gen_rand r=100 c=100 q=1
tc g3-9 gen_rand r=100 c=100 q=1 snake=1
tc g3-10 gen_rand r=100 c=100 q=1 pockets=1
tc g3-11 gen_rand r=100 c=100 q=1 pockets=3

# Same box and goal
group group4 10
limits maxr=100 sameboxgoal=1 maxq=100000
include_group group3
tc g4-1 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-2 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-3 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-4 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-5 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-6 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-7 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1
tc g4-8 gen_rand r=100 c=100 q=100000 samebox=1 samegoal=1

# Same goal
group group5 15
limits maxr=100 samegoal=1 maxq=100000
include_group group4
tc g5-1 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-2 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-3 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-4 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-5 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-6 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-7 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-8 gen_rand r=100 c=100 q=100000 samegoal=1
tc g5-9 gen_rand r=100 c=100 q=100000 samegoal=1 snake=1
tc g5-10 gen_rand r=100 c=100 q=100000 samegoal=1 pockets=1
tc g5-11 gen_rand r=100 c=100 q=100000 samegoal=1 pockets=3

group group6 20
limits maxr=100 maxq=100000
include_group group1
include_group group3
include_group group5
tc g6-1 gen_rand r=100 c=100 q=100000
tc g6-2 gen_rand r=100 c=100 q=100000
tc g6-3 gen_rand r=100 c=100 q=100000
tc g6-4 gen_rand r=100 c=100 q=100000
tc g6-5 gen_rand r=100 c=100 q=100000
tc g6-6 gen_rand r=100 c=100 q=100000
tc g6-7 gen_rand r=100 c=100 q=100000
tc g6-8 gen_rand r=100 c=100 q=100000
tc g6-9 gen_rand r=100 c=100 q=100000 snake=1
tc g6-10 gen_rand r=100 c=100 q=100000 pockets=1
tc g6-11 gen_rand r=100 c=100 q=100000 pockets=3

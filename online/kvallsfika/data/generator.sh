#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution joshua.cpp

compile gen_afford.py
compile gen_rand.py

samplegroup
sample 1

group group1 20
tc_manual affisch

group group2 5
limits nocategories=1 buyall=1
tc g2-1 gen_afford k=100000 num_categories=10
tc g2-2 gen_afford k=100000 num_categories=1000
tc g2-3 gen_afford k=100000 num_categories=100000

group group3 15
limits buyall=1
include_group group2
tc g3-1 gen_afford k=10 num_categories=10
tc g3-2 gen_afford k=100000 num_categories=1
tc g3-3 gen_afford k=1000 num_categories=10
tc g3-4 gen_afford k=2 num_categories=100000

group group4 5
limits maxc=1
tc g4-1 gen_rand n=100000 maxcost=1 k=10 num_categories=10
tc g4-2 gen_rand n=100000 maxcost=1 k=100000 num_categories=1
tc g4-3 gen_rand n=100000 maxcost=1 k=1000 num_categories=10
tc g4-4 gen_rand n=100000 maxcost=1 k=2 num_categories=100000

group group5 17
limits nocategories=1 maxn=500
tc g5-1 gen_rand n=500 k=500 num_categories=1      maxcost=10     
tc g5-2 gen_rand n=500 k=500 num_categories=100000 maxcost=100    
tc g5-3 gen_rand n=500 k=500 num_categories=100000 maxcost=1000   
tc g5-4 gen_rand n=500 k=500 num_categories=100000 maxcost=100000 

group group6 21
limits nocategories=1
include_group group2
include_group group5
tc g6-1 gen_rand n=100000 k=100000 num_categories=1      maxcost=10     
tc g6-2 gen_rand n=100000 k=100000 num_categories=100000 maxcost=100    
tc g6-3 gen_rand n=100000 k=100000 num_categories=100000 maxcost=1000   
tc g6-4 gen_rand n=100000 k=100000 num_categories=100000 maxcost=100000 

group group7 9
limits maxn=500
include_group group5
tc g7-1 gen_rand n=500 k=100 num_categories=3  maxcost=10     
tc g7-2 gen_rand n=500 k=10 num_categories=100 maxcost=100    
tc g7-3 gen_rand n=500 k=2 num_categories=500  maxcost=1000   
tc g7-4 gen_rand n=500 k=10 num_categories=3 maxcost=100000 

group group8 8
include_group group3
include_group group4
include_group group6
include_group group7
tc g8-1 gen_rand n=100000 k=10 num_categories=10 maxcost=10     
tc g8-2 gen_rand n=100000 k=100000 num_categories=1 maxcost=100    
tc g8-3 gen_rand n=100000 k=1000 num_categories=10 maxcost=1000   
tc g8-4 gen_rand n=100000 k=2 num_categories=100000 maxcost=100000 

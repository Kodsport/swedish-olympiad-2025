#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2

group group1 15
limits nmax=1
tc 1
tc g1-1 gen_rand n=1 m=1 max_duck=10
tc g1-2 gen_rand n=1 m=100 max_duck=1000000
tc g1-3 gen_rand n=1 m=100000
tc g1-4 gen_rand n=1 m=50000 max_duck=1000000000

group group2 20
limits c_is_i=1
tc g2-1 gen_rand n=100 m=100 max_duck=1000 c_is_i=1
tc g2-2 gen_rand n=1000 m=1000 max_duck=1000000 c_is_i=1
tc g2-3 gen_rand n=100000 m=100000 c_is_i=1
tc g2-4 gen_rand n=50000 m=50000 max_duck=1000000000 c_is_i=1
tc g2-5 gen_rand n=75000 m=75000 max_duck=1000000000000 c_is_i=1

group group3 25
limits max_duck_sum=100000
tc 2
tc g3-1 gen_rand n=1000 m=1000 max_duck=100 max_duck_sum=100000
tc g3-2 gen_rand n=100 m=100 max_duck=1000 max_duck_sum=100000
tc g3-3 gen_rand n=500 m=500 max_duck=200 max_duck_sum=100000
tc g3-4 gen_rand n=10000 m=10000 max_duck=10 max_duck_sum=100000
tc g3-5 gen_rand n=50000 m=50000 max_duck=2 max_duck_sum=100000

group group4 20
limits nmax=2000 mmax=2000
tc 2
tc g4-1 gen_rand n=2000 m=2000
tc g4-2 gen_rand n=2000 m=2000
tc g4-3 gen_rand n=1500 m=2000 max_duck=1000000000000
tc g4-4 gen_rand n=2000 m=1500 max_duck=1000000000000
tc g4-5 gen_rand n=1800 m=1800

group group5 20
include_group group1
include_group group2
include_group group3
include_group group4
tc g5-1 gen_rand n=100000 m=100000
tc g5-2 gen_rand n=100000 m=100000
tc g5-3 gen_rand n=90000 m=100000
tc g5-4 gen_rand n=100000 m=90000
tc g5-5 gen_rand n=95000 m=95000



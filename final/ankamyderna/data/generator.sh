#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution theodor.cpp

compile gen_rand.py
compile gen_exact.py

samplegroup
sample 1
sample 2

group group1 11
limits nmax=1
tc 1
tc g1-1 gen_rand n=1 m=1 max_duck=10
tc g1-2 gen_rand n=1 m=100 max_duck=1000000
tc g1-3 gen_rand n=1 m=100000
tc g1-4 gen_rand n=1 m=50000 max_duck=1000000000
tc g1-5 gen_exact n=1 m=100000 
tc g1-6 gen_exact n=1 m=100000 mode="remove"

group group2 19
limits c_is_i=1
tc g2-1 gen_rand n=100 m=100 max_duck=1000 c_is_i=1
tc g2-2 gen_rand n=1000 m=1000 max_duck=1000000 c_is_i=1
tc g2-3 gen_rand n=100000 m=100000 c_is_i=1
tc g2-4 gen_rand n=50000 m=50000 max_duck=1000000000 c_is_i=1
tc g2-5 gen_rand n=75000 m=75000 max_duck=1000000000000 c_is_i=1
tc g2-6 gen_exact n=100000 m=100000 mode="shift" c_is_i=1 shift=1000 amt=100
tc g2-7 gen_exact n=100000 m=100000 mode="remove" c_is_i=1
tc g2-8 gen_exact n=100000 m=100000 c_is_i=1
tc g2-9 gen_exact n=100000 m=100000 mode="shift" c_is_i=1 shift=10000 amt=10000
tc g2-10 gen_exact n=100000 m=100000 mode="shift" c_is_i=1 shift=100000 amt=1000000

group group3 17
limits max_duck_sum=100000
tc 2
tc g3-1 gen_rand n=1000 m=1000 max_duck=100 max_duck_sum=100000
tc g3-2 gen_rand n=100 m=100 max_duck=1000 max_duck_sum=100000
tc g3-3 gen_rand n=500 m=500 max_duck=200 max_duck_sum=100000
tc g3-4 gen_rand n=10000 m=10000 max_duck=10 max_duck_sum=100000
tc g3-5 gen_rand n=50000 m=50000 max_duck=2 max_duck_sum=100000
tc g3-6 gen_exact n=100000 m=66 mode="shift" shift=1000 amt=100
tc g3-7 gen_exact n=100000 m=65 mode="remove" 
tc g3-8 gen_exact n=100000 m=65 
tc g3-9 gen_exact n=100000 m=66 mode="shift" shift=100000 amt=100

group group4 19
limits nmax=2000 mmax=2000
tc 2
tc g4-1 gen_rand n=2000 m=2000
tc g4-2 gen_rand n=2000 m=2000
tc g4-3 gen_rand n=1500 m=2000 max_duck=1000000000000
tc g4-4 gen_rand n=2000 m=1500 max_duck=1000000000000
tc g4-5 gen_rand n=1800 m=1800
tc g4-6 gen_exact n=2000 m=66 mode="shift" shift=1000 amt=10
tc g4-7 gen_exact n=2000 m=2000 mode="remove" 
tc g4-8 gen_exact n=2000 m=2000 
tc g4-9 gen_exact n=2000 m=2000 mode="shift" shift=10000 amt=1000

group group5 34
include_group group1
include_group group2
include_group group3
include_group group4
tc g5-1 gen_rand n=100000 m=100000
tc g5-2 gen_rand n=100000 m=100000
tc g5-3 gen_rand n=90000 m=100000
tc g5-4 gen_rand n=100000 m=90000
tc g5-5 gen_rand n=95000 m=95000
tc g5-6 gen_exact n=100000 m=100000 mode="shift" shift=100000 amt=1000
tc g5-7 gen_exact n=100000 m=100000 mode="remove" 
tc g5-8 gen_exact n=100000 m=100000 
tc g5-9 gen_exact n=100000 m=100000 mode="shift" shift=10000 amt=10000
tc g5-10 gen_exact n=100000 m=100000 mode="shift" shift=100000 amt=1000000


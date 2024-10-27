#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution brute.cpp

compile gen_rand.py 


group group1 10
tc g1-1 gen_rand r=10 c=10 q=10
tc g1-2 gen_rand r=10 c=10 q=10
tc g1-3 gen_rand r=10 c=10 q=10
tc g1-4 gen_rand r=10 c=10 q=10
tc g1-5 gen_rand r=10 c=10 q=10
tc g1-6 gen_rand r=10 c=10 q=10
tc g1-7 gen_rand r=10 c=10 q=10
tc g1-8 gen_rand r=10 c=10 q=10


#!/usr/bin/env bash

PPATH=$(realpath ..)

. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution ../printnothing.cpp

compile generate.py

# group group1 5
# tc g1-1 generate n=5 k=2
# tc g1-2 generate n=5 k=2
# tc g1-3 generate n=5 k=2
# tc g1-4 generate n=5 k=2
# tc g1-5 generate n=5 k=2


group group2 5
tc g2-1 generate n=50 k=10 mode=random
tc g2-2 generate n=50 k=10 mode=a
tc g2-3 generate n=50 k=10 mode=b
tc g2-4 generate n=50 k=10 mode=c
tc g2-5 generate n=50 k=10 mode=d
tc g2-6 generate n=50 k=10 mode=e
tc g2-7 generate n=50 k=10 mode=f
tc g2-8 generate n=50 k=10 mode=g
tc g2-9 generate n=50 k=10 mode=h
tc g2-10 generate n=50 k=10 mode=i
tc g2-11 generate n=50 k=10 mode=j
tc g2-12 generate n=50 k=10 mode=rainbow
tc g2-15 generate n=50 k=10 mode=random
tc g2-16 generate n=50 k=10 mode=random
tc g2-17 generate n=50 k=10 mode=random
tc g2-18 generate n=50 k=10 mode=random
tc g2-19 generate n=50 k=10 mode=unbalanced
tc g2-20 generate n=50 k=10 mode=unbalanced

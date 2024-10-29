#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution brute.cpp

compile gen_rand.py 

R=5
group group1 10
limits maxr=30 maxq=1000
tc g1-1 gen_rand r=$R c=$R q=10
tc g1-2 gen_rand r=$R c=$R q=10
tc g1-3 gen_rand r=$R c=$R q=10
tc g1-4 gen_rand r=$R c=$R q=10
tc g1-5 gen_rand r=$R c=$R q=10
tc g1-6 gen_rand r=$R c=$R q=10
tc g1-7 gen_rand r=$R c=$R q=10
tc g1-8 gen_rand r=$R c=$R q=10

# Same box and goal
group group2 10
limits maxr=100 sameboxgoal=1 maxq=1000
tc g2-1 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-2 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-3 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-4 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-5 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-6 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-7 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1
tc g2-8 gen_rand r=$R c=$R q=10 samebox=1 samegoal=1

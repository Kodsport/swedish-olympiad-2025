#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution emil.cpp

compile gen_rand.py
compile gen_path.py
compile gen_dumbbell.py
compile gen_starry.py
compile gen_smalldeg.py pypy3
compile gen_line.py
compile gen_line2.py
compile gen_line3.py

samplegroup
limits maxn=10 maxk=10 maxt=10
#sample 1

group group1 10
limits maxn=50 maxk=50 maxt=100
#tc 1
tc g1-1 gen_rand n=50 k=10 t=100 maxs=1 dmult=3
tc g1-2 gen_rand n=50 k=16 t=100 maxs=2 dmult=5
tc g1-3 gen_rand n=50 k=25 t=100 maxs=5 dmult=6
tc g1-4 gen_rand n=50 k=50 t=100 maxs=10 dmult=7
tc g1-5 gen_rand n=50 k=10 t=100 maxs=1 dmult=20
tc g1-6 gen_rand n=50 k=16 t=100 maxs=2 dmult=6
tc g1-7 gen_rand n=50 k=25 t=100 maxs=10 dmult=2
tc g1-8 gen_rand n=50 k=50 t=100 maxs=5 dmult=20

group group2 5
include_group group1
limits maxn=50 maxk=50 maxt=1000000000
tc g2-1 gen_rand n=50 k=50 t=1000000000 maxs=1000
tc g2-2 gen_rand n=50 k=50 t=1000000000 maxs=1000000
tc g2-3 gen_path n=50 k=50 l=45 num_weights=3 traintime=1000
tc g2-4 gen_starry n=50 k=50 p=0 traintime=100000

group group3 12
include_group group2
limits maxn=1000 maxk=200 maxt=1000000000
tc g3-1 gen_rand n=1000 k=200 t=1000000000 maxs=1000
tc g3-2 gen_rand n=1000 k=200 t=1000000000 maxs=1000000
tc g3-3 gen_path n=1000 k=200 l=923 num_weights=3 traintime=10000
tc g3-4 gen_starry n=1000 k=200 p=0 traintime=100000

group group4 13
include_group group3
limits maxn=2000 maxk=2000 maxt=1000000000
tc g4-1 gen_rand n=2000 k=2000 t=1000000000 maxs=1000
tc g4-2 gen_rand n=2000 k=2000 t=1000000000 maxs=1000000
tc g4-3 gen_path n=2000 k=2000 l=1953 num_weights=4 traintime=10000
tc g4-4 gen_dumbbell n=2000 k=2000 num_weights=4 traintime=10000
tc g4-5 gen_starry n=2000 k=2000 p=0 traintime=100000

# Binary lifting
group group5 10
limits maxn=100000 maxk=2000 maxt=1000000000 latetrains=1
tc g5-1 gen_rand n=100000 k=2000 t=500000000 maxs=1000 latetrains=1
tc g5-2 gen_rand n=100000 k=2000 t=500000000 maxs=100 latetrains=1
tc g5-3 gen_path n=100000 k=2000 l=95000 num_weights=4 traintime=1000 max_exp=4 latetrains=1
tc g5-4 gen_dumbbell n=100000 k=2000 num_weights=4 traintime=1000 max_exp=4 latetrains=1
tc g5-5 gen_starry n=100000 k=2000 p=0 traintime=1000 max_exp=4 latetrains=1

group group6 2
include_group group4
include_group group5
limits maxn=100000 maxk=20000 maxt=1000000000
tc g6-1 gen_rand n=100000 k=20000 t=1000000000 maxs=1000
tc g6-2 gen_rand n=100000 k=20000 t=1000000000 maxs=1000000
tc g6-3 gen_path n=100000 k=20000 l=95000 num_weights=1 traintime=100
tc g6-4 gen_path n=100000 k=20000 l=95000 num_weights=3 traintime=1000
tc g6-5 gen_path n=100000 k=20000 l=95000 num_weights=5 traintime=10000
tc g6-6 gen_dumbbell n=100000 k=20000 num_weights=4 traintime=10000
tc g6-7 gen_starry n=100000 k=20000 traintime=10000 p=1
tc g6-8 gen_starry n=100000 k=20000 traintime=10000 p=0.6
tc g6-9 gen_starry n=100000 k=20000 traintime=10000 p=0.3
tc g6-10 gen_starry n=100000 k=20000 traintime=10000 p=0.1
tc g6-11 gen_starry n=100000 k=20000 traintime=10000 p=0

group group7 23
limits maxn=100000 maxk=100000 maxt=1000000000 line=1
tc g7-1 gen_line n=100000 k=100000 num_weights=1 traintime=100
tc g7-2 gen_line n=100000 k=100000 num_weights=3 traintime=1000
tc g7-3 gen_line n=100000 k=100000 num_weights=5 traintime=10000
tc g7-4 gen_line2 w=1 d=5
tc g7-5 gen_line2 w=100 d=200
tc g7-6 gen_line3


group group8 25
include_group group6
include_group group7
limits maxn=100000 maxk=100000 maxt=1000000000
tc g8-1 gen_rand n=100000 k=100000 t=1000000000 maxs=1000
tc g8-2 gen_rand n=100000 k=100000 t=1000000000 maxs=1000000
tc g8-3 gen_path n=100000 k=100000 l=95000 num_weights=1 traintime=100
tc g8-4 gen_path n=100000 k=100000 l=95000 num_weights=3 traintime=1000
tc g8-5 gen_path n=100000 k=100000 l=95000 num_weights=5 traintime=10000
tc g8-6 gen_dumbbell n=100000 k=100000 num_weights=4 traintime=10000
tc g8-7 gen_starry n=100000 k=100000 traintime=10000 p=1
tc g8-8 gen_starry n=100000 k=100000 traintime=10000 p=0.6
tc g8-9 gen_starry n=100000 k=100000 traintime=10000 p=0.3
tc g8-10 gen_starry n=100000 k=100000 traintime=10000 p=0.1
tc g8-11 gen_starry n=100000 k=100000 traintime=10000 p=0

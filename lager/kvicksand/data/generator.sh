#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils.cpp

compile gen_rand.py

samplegroup
sample 1

MAXN=300000

group group1 17
limits n=1
tc line-1 gen_rand n=1 m=1000 q=30000 sand_density=0 sand_changes=10
tc_manual ../manual_tests/small_line.in
tc line-2 gen_rand n=1 m=3 q=300000 mode=random
tc line-3 gen_rand n=1 m=4 q=300000 mode=random
tc line-4 gen_rand n=1 m=1000 q=300000 mode=line
tc line-5 gen_rand n=1 m=1000 q=300000 mode=line noise=100
tc line-6 gen_rand n=1 m=300000 q=300000 mode=line noise=1000
tc line-7 gen_rand n=1 m=300000 q=300000 mode=line noise=1000 d=100

group group2 28
limits n=100 m=100 q=100
tc 1
tc small-1 gen_rand n=10 m=10 q=100
tc small-2 gen_rand n=100 m=10 q=100 sand_density=0.1
tc small-3 gen_rand n=10 m=100 q=100 sand_density=0
tc small-4 gen_rand n=30 m=30 q=100 sand_density=0.03 possible=1
tc small-5 gen_rand n=100 m=100 q=100 sand_density=0.001
tc small-6 gen_rand n=100 m=100 q=100 sand_density=0.03 q_density=0.9
tc random-small-1 gen_rand n=2 m=2 q=100 maxd=2 mode=random
tc random-small-2 gen_rand n=2 m=1 q=100 maxd=1 mode=random
tc random-small-3 gen_rand n=2 m=1 q=100 maxd=1 mode=random
tc_manual ../manual_tests/square.in
tc_manual ../manual_tests/olle.in
tc small-7 gen_rand n=100 m=100 q=100 sand_density=0 sand_change_mode=blob sand_changes=10
tc small-8 gen_rand n=100 m=100 q=100 sand_start_mode=chess sand_changes=2
tc small-9 gen_rand n=100 m=100 q=100 sand_density=0.2 sand_start_mode=caves sand_changes=2
tc small-manhattan-1 gen_rand n=100 m=100 q=100 sand_density=1 sand_start_mode=manhattan
tc small-manhattan-2 gen_rand n=99 m=100 q=100 sand_density=1 sand_start_mode=manhattan sand_change_mode=square sand_changes=20
tc small-fill-1 gen_rand n=30 m=30 q=100 sand_density=0 sand_change_mode=fill possible=1
tc small-fill-2 gen_rand n=10 m=10 q=100 sand_density=0 sand_change_mode=fill possible=1 sand_changes=10


group group3 20
tc possible-1 gen_rand n=300 m=300 q=300000 sand_density=0.01 possible=1 sand_changes=100
tc possible-2 gen_rand n=300 m=1000 q=300000 sand_density=0 possible=1 sand_changes=100 sand_change_mode=blob
tc possible-3 gen_rand n=500 m=500 q=300000 sand_density=0.4 sand_start_mode=caves sand_changes=200 possible=1
tc possible-4 gen_rand n=50 m=5000 q=300000 sand_density=0.05 sand_start_mode=caves sand_change_mode=dig sand_changes=200 possible=1
tc manhattan-1 gen_rand n=100 m=100 q=300000 sand_density=1 sand_start_mode=manhattan possible=1
tc manhattan-2 gen_rand n=1000 m=300 q=300000 sand_density=1 q_density=0.9 sand_start_mode=manhattan sand_change_mode=dig sand_changes=200 possible=1
tc fill-1 gen_rand n=547 m=547 q=300000 sand_density=0  sand_change_mode=fill sand_changes=200 possible=1
tc fill-2 gen_rand n=30 m=10000 q=300000 sand_density=0  sand_change_mode=fill sand_changes=200 possible=1
tc random-possible-1 gen_rand n=10 m=10 q=300000 possible=1
tc random-possible-2 gen_rand n=3 m=3 q=300000 possible=1
tc line-possible-1 gen_rand n=1 m=100000 q=300000 mode=line
tc no-changes-1 gen_rand n=547 m=547 q=300000 sand_density=0.5 sand_start_mode=caves q_density=1.0 possible=1


group group4 35
include_group group1
include_group group2
include_group group3
tc large-1 gen_rand n=10000 m=30 q=300000 sand_density=0.01 sand_changes=100
tc random-1 gen_rand n=3 m=3 q=300000 maxd=4 mode=random
tc random-2 gen_rand n=2 m=3 q=300000 mode=random
tc random-3 gen_rand n=3 m=2 q=300000 mode=random
tc random-4 gen_rand n=2 m=2 q=300000 mode=random
tc random-5 gen_rand n=2 m=3 q=300000 maxd=3 mode=random
tc random-6 gen_rand n=2 m=4 q=300000 maxd=4 mode=random
tc random-7 gen_rand n=2 m=2 q=300000 maxd=2 mode=random
tc manhattan-3 gen_rand n=500 m=500 sand_density=1 sand_start_mode=manhattan sand_changes=200
tc fill-3 gen_rand n=547 m=547 q=300000 sand_density=0  sand_change_mode=fill sand_changes=200
tc random-8 gen_rand n=10 m=10 q=300000

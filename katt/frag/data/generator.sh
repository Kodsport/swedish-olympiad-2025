#!/bin/bash
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited
use_solution emil.cpp

compile gen_rand.py 
compile gen_path.py 
compile gen_dumbbell.py 
compile gen_starry.py 
compile gen_smalldeg.py pypy3 
compile gen_binarytree.py
#compile gen_line.py
#compile gen_line2.py
#compile gen_line3.py

samplegroup
limits maxn=10 maxm=10 maxt=10
sample 1
sample 2

group group1 6
limits maxe=1
#tc 1
tc g1-01 gen_rand n=10 m=1 t=100 maxt=10 maxe=1
tc g1-02 gen_rand n=10 m=2 t=100 maxt=10 maxe=1
tc g1-03 gen_rand n=2 m=1 t=100 maxt=2 maxe=1
tc g1-04 gen_path n=100 m=1 l=90 t=100 maxt=100 maxe=1 root0=1
tc g1-05 gen_rand n=200000 m=100000 t=100000000 maxt=100000000 maxe=1
tc g1-06 gen_rand n=200000 m=180003 t=100000000 maxt=1 maxe=1
tc g1-07 gen_path n=200000 l=120001 m=40003 t=1000000 maxt=1000 maxe=1 root0=1
tc g1-08 gen_path n=200000 l=50001 m=4003 t=100000000 maxt=100 maxe=1 
tc g1-09 gen_dumbbell n=200000 m=100000 t=100000000 maxt=1000 maxe=1 root0=1
tc g1-10 gen_dumbbell n=200000 m=20000 t=100000000 maxt=10000000 maxe=1 
tc g1-11 gen_starry n=200000 m=194999 t=100000000 maxt=10000 p=0 root0=1 maxe=1
tc g1-12 gen_starry n=200000 m=123 t=100000000 maxt=10000 p=0.7 root0=1 maxe=1
tc g1-13 gen_smalldeg n=200000 m=500 t=100000000 maxt=100 maxe=1
tc g1-14 gen_binarytree n=200000 m=199999 t=100000000 maxt=10 maxe=1 root0=1


group group2 5
limits maxm=1
tc_manual ../manual_data/m1
tc g1-01
tc g1-03
tc g1-04
tc g2-01 gen_rand n=10 m=1 t=100 maxt=10 maxe=1000
tc g2-02 gen_rand n=200000 m=1 t=100000000 maxt=100000000 maxe=100000
tc g2-03 gen_path n=200000 l=120001 m=1 t=1000000 maxt=1000 root0=1
tc g2-04 gen_path n=200000 l=4001 m=1 t=100000000 maxt=100 
tc g2-05 gen_dumbbell n=199999 m=1 t=100000000 maxt=1000 root0=1
tc g2-06 gen_dumbbell n=200000 m=1 t=100000000 maxt=10000 
tc g2-07 gen_starry n=200000 m=1 t=100000000 maxt=10000 p=0 root0=1 
tc g2-08 gen_starry n=200000 m=1 t=100000000 maxt=10000 p=0.5 root0=1 
tc g2-09 gen_smalldeg n=200000 m=1 t=100000000 maxt=1000 
tc g2-10 gen_binarytree n=200000 m=1 t=100000000 maxt=10000 root0=1


group group3 10
include_group group2
include_group sample
limits maxm=2
tc_manual ../manual_data/m2
tc_manual ../manual_data/m3
tc_manual ../manual_data/m4
tc g1-02
tc g3-01 gen_rand n=10 m=2 t=100 maxt=10 maxe=1000
tc g3-02 gen_rand n=1000 m=2 t=1000000 maxt=100000 maxe=1000
tc g3-03 gen_rand n=200000 m=2 t=100000000 maxt=100000000 maxe=100000
tc g3-04 gen_path n=200000 l=170001 m=2 t=1000000 maxt=1000 root0=1
tc g3-05 gen_path n=200000 l=3001 m=2 t=100000000 maxt=100 
tc g3-06 gen_dumbbell n=199999 m=2 t=100000000 maxt=1000 root0=1
tc g3-07 gen_dumbbell n=200000 m=2 t=100000000 maxt=10000 
tc g3-08 gen_starry n=200000 m=2 t=100000000 maxt=10000 p=0 root0=1 
tc g3-09 gen_starry n=200000 m=2 t=100000000 maxt=10 p=0.5 root0=1 
tc g3-10 gen_smalldeg n=200000 m=2 t=100000000 maxt=100
tc g3-11 gen_binarytree n=200000 m=2 t=100000000 maxt=100000 root0=1


group group4 10
include_group sample
limits maxn=100 maxt=100
tc g1-01
tc g1-02
tc g1-03
tc g1-04
tc g2-01
tc g3-01

tc g4-01 gen_rand n=11 m=10 t=99 maxt=70 maxe=100000
tc g4-02 gen_rand n=21 m=20 t=80 maxt=70 maxe=100000
tc g4-03 gen_rand n=100 m=51 t=100 maxt=100 maxe=100000
tc g4-04 gen_rand n=100 m=71 t=100 maxt=50 maxe=100000
tc g4-05 gen_path n=100 l=99 m=5 t=100 maxt=3 root0=1
tc g4-06 gen_path n=100 l=31 m=31 t=100 maxt=100 
tc g4-07 gen_dumbbell n=100 m=35 t=100 maxt=100 root0=1
tc g4-08 gen_dumbbell n=100 m=99 t=100 maxt=7 
tc g4-09 gen_starry n=100 m=13 t=100 maxt=10 p=0 root0=1 
tc g4-10 gen_smalldeg n=100 m=22 t=100 maxt=100
tc g4-11 gen_binarytree n=100 m=47 t=100 maxt=4 root0=1

group group5 23
limits maxn=2000
include_group group4
tc g5-01 gen_rand n=2000 m=987 t=100000000 maxt=1000 maxe=100000
tc g5-02 gen_path n=2000 l=1699 m=1923 t=1000000 maxt=1000 root0=1
tc g5-03 gen_path n=2000 l=661 m=123 t=100000000 maxt=100 
tc g5-04 gen_dumbbell n=2000 m=1987 t=100000000 maxt=1000 root0=1
tc g5-05 gen_dumbbell n=2000 m=11 t=100000000 maxt=10000 
tc g5-06 gen_starry n=2000 m=123 t=100000000 maxt=10000 p=0 root0=1 
tc g5-07 gen_starry n=2000 m=339 t=100000000 maxt=10 p=0.5 root0=1 
tc g5-08 gen_smalldeg n=2000 m=1422 t=100000000 maxt=10
tc g5-09 gen_binarytree n=2000 m=1999 t=100000000 maxt=4 root0=1

group group6 15
limits maxdist=20
tc g1-01
tc g1-02
tc g1-03
tc g1-11
tc g1-14
tc g2-01
tc g2-10
tc g3-01
tc g3-08
tc g3-11
tc g4-01
tc g4-02
tc g4-11
tc g5-06
tc g5-09
tc g6-01 gen_dumbbell n=50 m=20 t=100000000 maxt=1000 root0=1
tc g6-02 gen_dumbbell n=51 m=49 t=100000000 maxt=100000000 
tc g6-03 gen_path n=20 l=19 m=17 t=100000000 maxt=10000 root0=1
tc g6-04 gen_starry n=200000 m=20000 t=100000000 maxt=100 p=0 
tc g6-05 gen_binarytree n=200000 m=199999 t=100000000 maxt=10 root0=1
tc g6-06 gen_binarytree n=200000 m=391 t=100000000 root0=1

group group7 31
include_group group1
include_group group3
include_group group5
include_group group6
tc g7-01 gen_rand n=200000 m=99 t=100000000 maxt=100 maxe=100000
tc g7-02 gen_rand n=200000 m=198518 t=100000000 maxt=1000 maxe=100000
tc g7-03 gen_path n=200000 l=164999 m=192000 t=1000000 maxt=1000 root0=1
tc g7-04 gen_path n=200000 l=99961 m=12443 t=100000000 maxt=100000000 
tc g7-05 gen_dumbbell n=200000 m=199879 t=100000000 maxt=1000 root0=1
tc g7-06 gen_dumbbell n=200000 m=11 t=100000000 maxt=10000 
tc g7-07 gen_starry n=200000 m=1123 t=100000000 maxt=10000 p=1 
tc g7-08 gen_starry n=200000 m=133 t=100000000 maxt=1000 p=0.6
tc g7-09 gen_starry n=200000 m=100592 t=100000000 maxt=100  p=0.3
tc g7-10 gen_starry n=200000 m=87872 t=100000000 maxt=10  p=0.1 
tc g7-11 gen_starry n=200000 m=20000 t=100000000 maxt=1  p=0 root0=1
tc g7-12 gen_smalldeg n=200000 m=101929 t=100000000 maxt=1
tc g7-13 gen_binarytree n=200000 m=199999 t=99999999 
#!/bin/bash
. ../../../testdata_tools/gen.sh

#use_solution harry_qlogk.py
use_solution joshua_full.cpp

compile gen_rand.py # Query randomly [1,10^12]
compile gen_sortfile.py # File is sorted
compile gen_deep.py # Queries will be put on deep layers
compile gen_range.py # Queries selected [start,start+q]
compile gen_spread.py # Includes are spread out evenly

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3
sample 4

BILLION=1000000000

group group1 2
limits minInc=1 maxInc=1
tc 1
tc_manual ../manual/n1_2.in
tc_manual ../manual/n1_4.in
tc g1-01 gen_rand n=10 k=9 q=100000 inc=1
tc g1-02 gen_rand n=100 k=10 q=100000 inc=1
tc g1-03 gen_rand n=31 k=100000 q=100000 inc=1
tc g1-04 gen_rand n=1000000 k=1000 q=100000 inc=1
tc g1-05 gen_rand n=1000000 k=100000 q=100000 inc=1
tc g1-06 gen_rand n=1000000 k=$BILLION q=100000 inc=1
tc_manual ../manual/n5k5.in
tc g1-07 gen_rand n=2 k=10 q=100 inc=1
tc g1-08 gen_rand n=2 k=100000 q=100000 inc=1
tc g1-09 gen_sortfile n=1000000 k=499817 q=100000 inc=1 length=8
tc g1-10 gen_sortfile n=1000000 k=499897 q=100000 inc=1 mode=rev
tc g1-11 gen_deep n=1000000 k=$BILLION q=100000 inc=1 scale=10
tc g1-12 gen_deep n=1000000 k=$BILLION q=100000 inc=1 scale=5
tc g1-13 gen_deep n=1000000 k=100000 q=100000 inc=1 scale=3
tc g1-14 gen_deep n=1000000 k=$BILLION q=100000 inc=1 scale=50 mode=dec
tc g1-15 gen_deep n=1000000 k=500000 q=100000 inc=1 scale=7 mode=dec
tc g1-16 gen_range n=1000000 k=$BILLION q=100000 inc=1 start=1 
tc g1-17 gen_range n=1000000 k=500000 q=100000 inc=1 start=50000000000 
tc g1-18 gen_deep n=1000000 k=$BILLION q=100000 inc=1 scale=3


group group2 3
limits maxk=1
tc 3
tc_manual ../manual/n1_1.in
tc n1_2
tc g2-01 gen_rand n=10 k=1 q=100000 inc=4
tc g2-02 gen_rand n=31 k=1 q=100000 inc=19
tc g2-03 gen_rand n=1000000 k=1 q=100000 inc=1234
tc g2-04 gen_rand n=1000000 k=1 q=100000 inc=999999
tc g2-05 gen_rand n=1000000 k=1 q=100000 inc=1000000
tc_manual ../manual/n5k1.in
tc g2-06 gen_sortfile n=1000000 k=1 q=100000 inc=9997 length=8
tc g2-07 gen_sortfile n=1000000 k=1 q=100000 inc=48888 mode=rev
tc g2-08 gen_rand n=100000 k=1 q=100000 inc=100000
tc g2-09 gen_deep n=1000000 k=1 q=100000 inc=1025 
tc g2-10 gen_range n=1000000 k=1 q=100000 inc=30 start=1 
tc g2-11 gen_range n=1000000 k=1 q=100000 inc=311111 
tc g2-12 gen_spread n=1000000 k=1 q=100000 inc=500000 scale=3 
tc g2-13 gen_deep n=1000000 k=1 q=100000 inc=999900 scale=3 
tc g2-14 gen_deep n=1000000 k=1 q=100000 inc=1000000 scale=3 

group group3 9
limits minN=2 maxN=2
tc g1-07
tc g3-01 gen_rand n=2 k=9 q=100 inc=2
tc g3-02 gen_rand n=2 k=8 q=100 inc=0
tc_manual ../manual/n2_1.in
tc_manual ../manual/n2_2.in
tc_manual ../manual/n2_3.in
tc_manual ../manual/n2_4.in
tc g1-08
tc g3-03 gen_rand n=2 k=$BILLION q=100000 inc=2
tc g3-04 gen_rand n=2 k=$BILLION q=100000 inc=0
tc g3-05 gen_deep n=2 k=$BILLION q=100000 inc=2 scale=3
tc g3-06 gen_range n=2 k=$BILLION q=100000 inc=2 start=1
 

group group4 12
limits maxN=100 maxQ=100 maxk=10
include_group sample
tc n1_1
tc n1_2
# tc g1-01
# tc g1-02
tc g1-07
tc g3-01
tc g3-02
tc g4-01 gen_rand n=100 k=10 q=100 inc=3
tc g4-02 gen_rand n=100 k=10 q=100 inc=11
tc g4-03 gen_rand n=100 k=10 q=100 inc=40
tc g4-04 gen_rand n=100 k=10 q=100 inc=90
tc_manual ../manual/k10.in
tc_manual ../manual/n5k3-full1.in
tc_manual ../manual/n5k3-full2.in
tc n5k5
tc n5k1
tc g4-05 gen_sortfile n=100 k=9 q=100 inc=2 
tc g4-06 gen_sortfile n=100 k=9 q=100 inc=61 mode=rev 
tc g4-07 gen_rand n=100 k=10 q=100 inc=100
tc g4-08 gen_deep n=100 k=10 q=100 inc=12 scale=5
tc g4-09 gen_deep n=100 k=10 q=100 inc=20 scale=3
tc g4-10 gen_deep n=100 k=10 q=100 inc=31 scale=10 mode=dec
tc g4-11 gen_deep n=100 k=10 q=100 inc=13 scale=3 mode=dec
tc g4-12 gen_range n=100 k=10 q=100 inc=91 start=1
tc g4-13 gen_range n=100 k=10 q=100 inc=73
tc g4-14 gen_spread n=100 k=10 q=100 inc=50 scale=3

group group5 13
limits maxN=1000 maxk=100 maxQ=10000
include_group group4
#tc n2_1
#tc n2_2
#tc n2_3
#tc n2_4
#tc g2-08
tc g5-01 gen_rand n=1000 k=100 q=10000 inc=50
tc g5-02 gen_rand n=1000 k=10 q=10000 inc=250
tc g5-03 gen_rand n=1000 k=5 q=10000 inc=500
tc g5-04 gen_rand n=1000 k=5 q=10000 inc=950
tc g5-05 gen_sortfile n=1000 k=100 q=10000 inc=126 length=9
tc g5-06 gen_sortfile n=1000 k=71 q=10000 inc=999 mode=rev 
tc g5-07 gen_deep n=1000 k=99 q=10000 inc=120 scale=5
tc g5-08 gen_deep n=1000 k=100 q=10000 inc=20 scale=3
tc g5-09 gen_deep n=1000 k=99 q=10000 inc=120 scale=10
tc g5-10 gen_deep n=1000 k=100 q=10000 inc=311 scale=50 mode=dec
tc g5-11 gen_deep n=1000 k=100 q=10000 inc=311 scale=3 mode=dec
tc g5-12 gen_range n=1000 k=100 q=10000 inc=791 start=1
tc g5-13 gen_range n=1000 k=100 q=10000 inc=13 
tc g5-14 gen_spread n=1000 k=100 q=10000 inc=500 scale=3


group group6 11
limits maxk=500 maxQ=10000
include_group group5
tc g6-01 gen_rand n=1000000 k=123 q=10000 inc=2
tc g6-02 gen_rand n=1000000 k=497 q=10000 inc=49000
tc g6-03 gen_rand n=1000000 k=500 q=10000 inc=1000
tc g6-04 gen_sortfile n=1000000 k=430 q=10000 inc=126 length=9
tc g6-05 gen_sortfile n=1000000 k=500 q=10000 inc=329900 mode=rev length=8
tc g6-06 gen_deep n=1000000 k=500 q=10000 inc=10000 scale=3
tc g6-07 gen_deep n=1000000 k=500 q=10000 inc=90 scale=199
tc g6-08 gen_deep n=1000000 k=500 q=10000 inc=2025 scale=5 mode=dec
tc g6-09 gen_deep n=1000000 k=500 q=10000 inc=2025 scale=100 mode=dec
tc g6-11 gen_range n=1000000 k=500 q=10000 inc=400000 start=1
tc g6-12 gen_range n=1000000 k=500 q=10000 inc=102488  
tc g6-13 gen_spread n=1000000 k=500 q=10000 inc=500000 scale=3
tc g6-14 gen_deep n=1000000 k=500 q=10000 inc=50000 length=8 move=40000 specialFile=1
tc_manual ../manual/3incsk100.in

group group7 18
limits maxk=1000
include_group group2
include_group group6
tc g1-04
tc g7-02 gen_rand n=1000000 k=23 q=100000 inc=2
tc g7-03 gen_rand n=1000000 k=399 q=100000 inc=5
tc g7-04 gen_rand n=1000000 k=500 q=100000 inc=1000
tc g7-05 gen_rand n=1000000 k=997 q=100000 inc=10000
tc g7-06 gen_rand n=1000000 k=1000 q=100000 inc=90000 
tc g7-07 gen_rand n=1000000 k=1000 q=100000 inc=1000
tc g7-08 gen_sortfile n=1000000 k=130 q=100000 inc=126 length=9
tc g7-09 gen_sortfile n=1000000 k=1000 q=100000 inc=329900 mode=rev length=8
tc g7-10 gen_deep n=1000000 k=1000 q=100000 inc=10000 scale=3
tc g7-11 gen_deep n=1000000 k=1000 q=100000 inc=90 scale=10
tc g7-12 gen_deep n=1000000 k=1000 q=100000 inc=2025 scale=5 mode=dec
tc g7-13 gen_deep n=1000000 k=1000 q=100000 inc=2025 scale=100 mode=dec
tc g7-14 gen_range n=1000000 k=1000 q=100000 inc=400000 start=1
tc g7-15 gen_range n=1000000 k=1000 q=100000 inc=102488  
tc g7-16 gen_spread n=1000000 k=1000 q=100000 inc=500000 scale=3
tc g7-17 gen_deep n=1000000 k=899 q=100000 inc=250000 length=8 move=50000 specialFile=1
tc g7-18 gen_range n=1000000 k=3 q=100000 inc=999995 start=-1
tc g7-19 gen_range n=1000000 k=2 q=100000 inc=999996 start=-1 header=1
tc_manual ../manual/3incsk1000.in

group group8 23
limits maxk=500000
include_group group7
tc g8-01 gen_rand n=1000000 k=500000 q=100000 inc=100
tc g8-02 gen_sortfile n=1000000 k=500000 q=100000 inc=999999 length=2
tc g8-03 gen_sortfile n=1000000 k=500000 q=100000 inc=329900 mode=rev length=8
tc g8-04 gen_deep n=1000000 k=500000 q=100000 inc=10000 scale=3
tc g8-05 gen_deep n=1000000 k=500000 q=100000 inc=90 scale=10
tc g8-06 gen_deep n=1000000 k=500000 q=100000 inc=2025 scale=8 mode=dec
tc g8-07 gen_deep n=1000000 k=500000 q=100000 inc=2025 scale=30 mode=dec
tc g8-08 gen_deep n=1000000 k=500000 q=100000 inc=2025 scale=100 mode=dec
tc g8-09 gen_deep n=1000000 k=500000 q=100000 inc=2025 scale=700 mode=dec
tc g8-10 gen_range n=1000000 k=500000 q=100000 inc=200200 start=1
tc g8-11 gen_range n=1000000 k=500000 q=100000 inc=102488 
tc g8-12 gen_deep n=1000000 k=500000 q=100000 inc=5810 scale=3
tc g8-13 gen_spread n=1000000 k=500000 q=100000 inc=500000 scale=3
tc_manual ../manual/3incsk5e5.in
tc g8-14 gen_deep n=1000000 k=500000 q=100000 inc=10 scale=3 
tc g8-15 gen_deep n=1000000 k=500000 q=100000 inc=200 scale=3
tc g8-16 gen_deep n=1000000 k=500000 q=100000 inc=3000 scale=50 
tc g8-17 gen_deep n=1000000 k=500000 q=100000 inc=40000 scale=3 
tc g8-18 gen_deep n=1000000 k=500000 q=100000 inc=500000 scale=3 
tc g8-19 gen_deep n=1000000 k=500000 q=100000 inc=250000 length=8 move=50000 specialFile=1 scale=3
tc g8-20 gen_deep n=1000000 k=500000 q=100000 inc=150000 length=8 move=50000 specialFile=1 scale=10
tc g8-21 gen_deep n=1000000 k=500000 q=100000 inc=150000 length=8 move=50000 specialFile=1 scale=10 mode=dec
tc g8-22 gen_deep n=1000000 k=500000 q=100000 inc=3 length=8 specialFile=1 scale=10 mode=dec


group group9 9
include_group group1
include_group group2
include_group group3
include_group group4
include_group group5
include_group group6
include_group group7
include_group group8
tc g9-01 gen_rand n=1000000 k=$BILLION q=100000 inc=92
tc g9-02 gen_sortfile n=1000000 k=$BILLION q=100000 inc=99999 length=8
tc g9-03 gen_sortfile n=1000000 k=$BILLION q=100000 inc=729900 mode=rev length=8
tc g9-04 gen_deep n=1000000 k=$BILLION q=100000 inc=2025 scale=8 mode=dec
tc g9-05 gen_spread n=1000000 k=$BILLION q=100000 inc=500000 scale=3
tc g9-06 gen_range n=1000000 k=$BILLION q=100000 inc=20200 start=1
tc g9-07 gen_range n=1000000 k=$BILLION q=100000 inc=3 
tc g9-08 gen_deep n=1000000 k=$BILLION q=100000 inc=350000 length=8 move=50000 specialFile=1 scale=3
tc g9-09 gen_deep n=1000000 k=$BILLION q=100000 inc=50000 length=8 move=25000 specialFile=1 scale=10
tc g9-10 gen_deep n=1000000 k=$BILLION q=100000 inc=150000 length=8 move=50000 specialFile=1 scale=10 mode=dec
tc g9-11 gen_deep n=1000000 k=$BILLION q=100000 inc=2 length=8 specialFile=1 scale=10 mode=dec
tc g9-12 gen_deep n=1000000 k=$BILLION q=100000 inc=1000000 scale=3 
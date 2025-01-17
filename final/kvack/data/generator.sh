#!/usr/bin/env bash
REQUIRE_SAMPLE_REUSE=0
PPATH=$(realpath ..)
. gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_random.py

samplegroup
sample 1

group group1 5
tc sample-1 gen_random n=2 t=1 mode="manual" points="100,10000" 
tc random-01 gen_random n=2 t=1 seed=1
tc random-02 gen_random n=2 t=1 seed=2
tc edge-03 gen_random n=2 t=1 mode="t2" start=0
tc edge-04 gen_random n=2 t=1 mode="t2" start=999999999
tc random-05 gen_random n=2 t=1 seed=5
tc edge-06 gen_random n=2 t=1 mode="manual" points="0,1000000000"
tc edge-07 gen_random n=2 t=1 mode="manual" points="0"  seed=7
tc edge-08 gen_random n=2 t=1 mode="manual" points="1000000000" seed=8
tc edge-09 gen_random n=2 t=1 mode="manual" points="2,3"
tc edge-10 gen_random n=2 t=1 mode="manual" points="2,4"
tc edge-11 gen_random n=2 t=1 mode="manual" points="1,4"


group group2 15
tc g2-01 gen_random n=2 t=2 mode="manual" points="0,1"
tc g2-02 gen_random n=3 t=2 mode="manual" points="999999998,999999999,1000000000"
tc g2-03 gen_random n=10000 t=2 mode="t2" start=0
tc g2-04 gen_random n=10000 t=2 mode="t2" seed=24
tc g2-05 gen_random n=9725 t=2 mode="t2" seed=25


group group3 10
tc g3-sample-1 gen_random n=2 t=3 mode="manual" points="100,10000" 
tc g3-01 gen_random n=2 t=3 mode="manual" points="0,1"
tc g3-02 gen_random n=3 t=3 mode="manual" points="999999998,999999999,1000000000"
tc g3-03 gen_random n=100 t=3 mode="t2" start=0
tc g3-04 gen_random n=100 t=3 mode="t2" seed=24
tc g3-05 gen_random n=97 t=3 mode="t2" seed=25
tc g3-06 gen_random n=100 t=3 mode="manual" points="0,1000000000" seed=36
tc g3-07 gen_random n=100 t=3 seed=37
tc g3-08 gen_random n=100 t=3 mode="manual" points="2,31,419,520857" seed=38

tc g3-09 gen_random n=3 t=3 mode="manual" points="1001,1005,1006" seed=420420
tc g3-10 gen_random n=100 t=3 mode="manual" points="1001,1005,1006" seed=420420
tc g3-11 gen_random n=7 t=3 mode="manual" points="1,10,19,20,5000,7000,7001"
tc g3-12 gen_random n=100 t=3 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452

group group4 14
tc g4-sample-1 gen_random n=2 t=4 mode="manual" points="100,10000" 
tc g4-01 gen_random n=2 t=4 mode="manual" points="0,1"
tc g4-02 gen_random n=3 t=4 mode="manual" points="999999998,999999999,1000000000"
tc g4-03 gen_random n=100 t=4 mode="t2" start=0
tc g4-04 gen_random n=100 t=4 mode="t2" seed=24
tc g4-05 gen_random n=97 t=4 mode="t2" seed=25
tc g4-06 gen_random n=100 t=4 mode="manual" points="0,1000000000" seed=36
tc g4-07 gen_random n=100 t=4 seed=37
tc g4-08 gen_random n=100 t=4 mode="manual" points="2,31,419,520857" seed=38

tc g4-09 gen_random n=3 t=4 mode="manual" points="1001,1005,1006" seed=420420
tc g4-10 gen_random n=100 t=4 mode="manual" points="1001,1005,1006" seed=420420
tc g4-11 gen_random n=7 t=4 mode="manual" points="1,10,19,20,5000,7000,7001"
tc g4-12 gen_random n=100 t=4 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452

group group5 21
tc g5-sample-1 gen_random n=2 t=5 mode="manual" points="100,10000" 
tc g5-01 gen_random n=2 t=5 mode="manual" points="0,1"
tc g5-02 gen_random n=3 t=5 mode="manual" points="999999998,999999999,1000000000"
tc g5-03 gen_random n=100 t=5 mode="t2" start=0
tc g5-04 gen_random n=100 t=5 mode="t2" seed=24
tc g5-05 gen_random n=97 t=5 mode="t2" seed=25
tc g5-06 gen_random n=100 t=5 mode="manual" points="0,1000000000" seed=36
tc g5-07 gen_random n=100 t=5 seed=37
tc g5-08 gen_random n=100 t=5 mode="manual" points="2,31,419,520857" seed=38

tc g5-09 gen_random n=3 t=5 mode="manual" points="1001,1005,1006" seed=420420
tc g5-10 gen_random n=100 t=5 mode="manual" points="1001,1005,1006" seed=420420
tc g5-11 gen_random n=7 t=5 mode="manual" points="1,10,19,20,5000,7000,7001"
tc g5-12 gen_random n=100 t=5 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452

group group6 18
tc g6-sample-1 gen_random n=2 t=6 mode="manual" points="100,10000" 
tc g6-01 gen_random n=2 t=6 mode="manual" points="0,1"
tc g6-02 gen_random n=3 t=6 mode="manual" points="999999998,999999999,1000000000"
tc g6-03 gen_random n=100 t=6 mode="t2" start=0
tc g6-04 gen_random n=100 t=6 mode="t2" seed=24
tc g6-05 gen_random n=97 t=6 mode="t2" seed=25
tc g6-06 gen_random n=100 t=6 mode="manual" points="0,1000000000" seed=36
tc g6-07 gen_random n=100 t=6 seed=37
tc g6-08 gen_random n=100 t=6 mode="manual" points="2,31,419,520857" seed=38
tc g6-09 gen_random n=1000 t=6 mode="manual" points="2,31,419,520857" seed=38
tc g6-10 gen_random n=1000 t=6 seed=610
tc g6-11 gen_random n=1000 t=6 seed=999

tc g6-12 gen_random n=3 t=6 mode="manual" points="1001,1005,1006" seed=420420
tc g6-13 gen_random n=100 t=6 mode="manual" points="1001,1005,1006" seed=420420
tc g6-14 gen_random n=7 t=6 mode="manual" points="1,10,19,20,5000,7000,7001"
tc g6-15 gen_random n=100 t=6 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452
tc g6-16 gen_random n=1000 t=6 mode="manual" points="1001,1005,1006" seed=420420
tc g6-17 gen_random n=1000 t=6 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452

group group7 17
tc g7-sample-1 gen_random n=2 t=7 mode="manual" points="100,10000" 
tc g7-01 gen_random n=2 t=7 mode="manual" points="0,1"
tc g7-02 gen_random n=3 t=7 mode="manual" points="999999998,999999999,1000000000"
tc g7-03 gen_random n=100 t=7 mode="t2" start=0
tc g7-04 gen_random n=100 t=7 mode="t2" seed=24
tc g7-05 gen_random n=97 t=7 mode="t2" seed=25
tc g7-06 gen_random n=100 t=7 mode="manual" points="0,1000000000" seed=36
tc g7-07 gen_random n=100 t=7 seed=37
tc g7-08 gen_random n=100 t=7 mode="manual" points="2,31,419,520857" seed=38
tc g7-09 gen_random n=1000 t=7 mode="manual" points="2,31,419,520857" seed=38
tc g7-10 gen_random n=1000 t=7 seed=610
tc g7-11 gen_random n=1000 t=7 seed=999
tc g7-12 gen_random n=10000 t=7 mode="manual" points="2,31,419,520857" seed=38
tc g7-13 gen_random n=10000 t=7 seed=610
tc g7-14 gen_random n=10000 t=7 seed=999

tc g7-15 gen_random n=3 t=7 mode="manual" points="1001,1005,1006" seed=420420
tc g7-16 gen_random n=100 t=7 mode="manual" points="1001,1005,1006" seed=420420
tc g7-17 gen_random n=7 t=7 mode="manual" points="1,10,19,20,5000,7000,7001"
tc g7-18 gen_random n=100 t=7 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452
tc g7-19 gen_random n=1000 t=7 mode="manual" points="1001,1005,1006" seed=420420
tc g7-20 gen_random n=1000 t=7 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452
tc g7-21 gen_random n=10000 t=7 mode="manual" points="1001,1005,1006" seed=420420
tc g7-22 gen_random n=10000 t=7 mode="manual" points="1,10,19,20,5000,7000,7001" seed=123452
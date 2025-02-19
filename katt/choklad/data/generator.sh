#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution olle.cpp

compile gen_random.py
compile gen_bigarea.py

samplegroup
limits maxn=10 maxsz=10
sample 1

group group1 10
limits maxn=100000 maxsz=1000000
tc g1-1 gen_random n=100000 same=1
tc g1-2 gen_random n=100000 same=1
tc g1-3 gen_random n=101 same=1
tc g1-4 gen_random n=1230 same=1
tc g1-5 gen_random n=9999 same=1
tc g1-6 gen_random n=9999 same=1
tc g1-7 gen_random n=9999 same=1
tc g1-8 gen_random n=9999 same=1
tc g1-9 gen_random n=9999 same=1


group group2 20
limits maxn=100000 maxsz=10
tc 1
tc g2-1 gen_random n=100000 maxsz=10
tc g2-2 gen_random n=100000 maxsz=10
tc g2-3 gen_random n=100000 maxsz=10
tc g2-4 gen_random n=99999 maxsz=10
tc g2-5 gen_random n=99919 maxsz=10
tc g2-6 gen_random n=87778 maxsz=10
tc g2-7 gen_random n=12736 maxsz=10
tc g2-8 gen_random n=99999 maxsz=10
tc g2-9 gen_random n=99998 maxsz=10
tc g2-10 gen_random n=99997 maxsz=10
tc g2-11 gen_random n=10000 maxsz=10

group group3 15
limits maxn=50 maxsz=1000000
tc 1
tc g3-1 gen_random n=50
tc g3-2 gen_random n=50
tc g3-3 gen_random n=50
tc g3-4 gen_random n=50
tc g3-5 gen_random n=50
tc g3-6 gen_bigarea n=50 target=10000000000
tc g3-7 gen_bigarea n=50 target=9000000000
tc g3-8 gen_bigarea n=50 target=12121000000
tc g3-9 gen_bigarea n=50 target=1024145000
tc g3-10 gen_bigarea n=50 target=100001421

group group4 15
limits maxn=500 maxsz=1000000
include_group group3
tc g4-1 gen_random n=500
tc g4-2 gen_random n=500
tc g4-3 gen_random n=500
tc g4-4 gen_random n=413
tc g4-5 gen_random n=500
tc g4-6 gen_bigarea n=500 target=100000000
tc g4-7 gen_bigarea n=495 target=900000000
tc g4-8 gen_bigarea n=498 target=121200000
tc g4-9 gen_bigarea n=500 target=1024500000
tc g4-10 gen_bigarea n=500 target=1004212000


group group5 40
limits maxn=100000 maxsz=1000000
include_group group4
tc g5-1 gen_random n=100000
tc g5-2 gen_random n=100000
tc g5-3 gen_random n=99991
tc g5-4 gen_random n=100000
tc g5-5 gen_random n=100000
tc g5-6 gen_bigarea n=100000 target=1000000000
tc g5-7 gen_bigarea n=99997 target=900000000
tc g5-8 gen_bigarea n=100000 target=1212000000
tc g5-9 gen_bigarea n=100000 target=1024145000
tc g5-10 gen_bigarea n=99999 target=1000212000

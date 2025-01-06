#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution o1.py

compile gen_rand.py
compile gen_n3.py

samplegroup
limits maxn=10 maxk=25
sample 1

group group1 15
limits maxn=3 maxk=100000
tc g1-1 gen_n3 mode=skip_1 seed=1
tc g1-2 gen_n3 mode=force_1 seed=2
tc g1-3 gen_n3 mode=two_paths_small_1 seed=3
tc g1-4 gen_n3 mode=two_paths_big_1 seed=4
tc g1-5 gen_n3 mode=random seed=5
tc g1-6 gen_n3 mode=random seed=6
tc g1-7 gen_n3 mode=random seed=7
tc g1-8 gen_n3 mode=random seed=8
tc g1-9 gen_n3 mode=random seed=9
tc g1-10 gen_n3 mode=mixed_random seed=10
tc g1-11 gen_n3 mode=mixed_random seed=11
tc g1-12 gen_n3 mode=mixed_random seed=12
tc g1-13 gen_n3 mode=mixed_random seed=13
tc g1-14 gen_n3 mode=mixed_random seed=14

group group2 15
limits maxn=100000 maxk=100000
tc g2-1 gen_rand sumk=100000 chain_len=5 num_chains=25000 mode=single_lhs seed=1
tc g2-2 gen_rand sumk=100000 chain_len=5 num_chains=20000 mode=single_lhs seed=2
tc g2-3 gen_rand sumk=100000 chain_len=5 num_chains=15000 mode=single_lhs seed=3
tc g2-4 gen_rand sumk=100000 chain_len=5 num_chains=10000 mode=single_lhs seed=4
tc g2-5 gen_rand sumk=100000 chain_len=5 num_chains=5000 mode=single_lhs seed=5
tc g2-6 gen_rand sumk=100000 chain_len=5 num_chains=20 mode=single_lhs seed=6
tc g2-7 gen_rand sumk=100000 chain_len=9 num_chains=12000 mode=single_lhs seed=7
tc g2-8 gen_rand sumk=100000 chain_len=9 num_chains=11000 mode=single_lhs seed=8
tc g2-9 gen_rand sumk=100000 chain_len=9 num_chains=10000 mode=single_lhs seed=9
tc g2-10 gen_rand sumk=100000 chain_len=9 num_chains=9000 mode=single_lhs seed=10
tc g2-11 gen_rand sumk=100000 chain_len=7 num_chains=1500 mode=single_lhs seed=11
tc g2-12 gen_rand sumk=100000 chain_len=7 num_chains=1200 mode=single_lhs seed=12
tc g2-13 gen_rand sumk=100000 chain_len=7 num_chains=9000 mode=single_lhs seed=13
tc g2-14 gen_rand sumk=100000 chain_len=7 num_chains=6000 mode=single_lhs seed=14
tc g2-15 gen_rand sumk=100000 chain_len=7 num_chains=20 mode=single_lhs seed=15

group group3 30
limits maxn=1000 maxk=1000
tc 1
tc g3-1 gen_rand sumk=1000 chain_len=5 num_chains=50 mode=normal seed=1
tc g3-2 gen_rand sumk=1000 chain_len=5 num_chains=75 mode=normal seed=2
tc g3-3 gen_rand sumk=1000 chain_len=5 num_chains=100 mode=normal seed=3
tc g3-4 gen_rand sumk=1000 chain_len=5 num_chains=100 mode=normal seed=4
tc g3-5 gen_rand sumk=1000 chain_len=5 num_chains=110 mode=normal seed=5
tc g3-6 gen_rand sumk=1000 chain_len=5 num_chains=120 mode=normal seed=6
tc g3-7 gen_rand sumk=1000 chain_len=5 num_chains=130 mode=normal seed=7
tc g3-8 gen_rand sumk=1000 chain_len=5 num_chains=140 mode=normal seed=8
tc g3-9 gen_rand sumk=1000 chain_len=5 num_chains=150 mode=normal seed=9
tc g3-10 gen_rand sumk=1000 chain_len=5 num_chains=170 mode=normal seed=10
tc g3-11 gen_rand sumk=1000 chain_len=7 num_chains=40 mode=normal seed=11
tc g3-12 gen_rand sumk=1000 chain_len=7 num_chains=50 mode=normal seed=12
tc g3-13 gen_rand sumk=1000 chain_len=7 num_chains=60 mode=normal seed=13
tc g3-14 gen_rand sumk=1000 chain_len=7 num_chains=70 mode=normal seed=14
tc g3-15 gen_rand sumk=1000 chain_len=7 num_chains=80 mode=normal seed=15

group group4 40
limits maxn=100000 maxk=100000
include_group group1
include_group group2
include_group group3
tc g4-1 gen_rand sumk=100000 chain_len=5 num_chains=10000 mode=normal seed=1
tc g4-2 gen_rand sumk=100000 chain_len=5 num_chains=10000 mode=normal seed=2
tc g4-3 gen_rand sumk=100000 chain_len=5 num_chains=10000 mode=normal seed=3
tc g4-4 gen_rand sumk=100000 chain_len=5 num_chains=5000 mode=normal seed=4
tc g4-5 gen_rand sumk=100000 chain_len=5 num_chains=11000 mode=normal seed=5
tc g4-6 gen_rand sumk=100000 chain_len=5 num_chains=12000 mode=normal seed=6
tc g4-7 gen_rand sumk=100000 chain_len=5 num_chains=13000 mode=normal seed=7
tc g4-8 gen_rand sumk=100000 chain_len=5 num_chains=14000 mode=normal seed=8
tc g4-9 gen_rand sumk=100000 chain_len=5 num_chains=15000 mode=normal seed=9
tc g4-10 gen_rand sumk=100000 chain_len=5 num_chains=17000 mode=normal seed=10


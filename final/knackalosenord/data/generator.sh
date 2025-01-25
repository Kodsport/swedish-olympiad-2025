#!/usr/bin/env bash
REQUIRE_SAMPLE_REUSE=0
PPATH=$(realpath ..)

. ../testdata_tools/gen.sh

ulimit -s unlimited

use_solution ../printnothing.cpp

compile generate.py

N=50
K=2

group group1 15
limits n=$N klo=2 khi=2
tc g1-1 generate  n=$N k=$K mode=rainbow
tc g1-2 generate  n=$N k=$K mode=random
tc g1-3 generate  n=$N k=$K mode=random
tc g1-4 generate  n=$N k=$K mode=random shuffle=1
tc g1-5 generate  n=$N k=$K mode=random shuffle=1
tc g1-6 generate  n=$N k=$K mode=unbalanced
tc g1-7 generate  n=$N k=$K mode=unbalanced shuffle=1
tc g1-8 generate n=$N k=$K mode=rainbow shuffle=1
tc g1-9 generate n=$N k=$K mode=rainbow shuffle=1
tc g1-a generate n=$N k=$K mode=a
tc g1-b generate n=$N k=$K mode=b

N=30
K=3

group group2 15
limits n=$N klo=3 khi=3
tc g2-1 generate  n=$N k=$K mode=rainbow
tc g2-2 generate  n=$N k=$K mode=random
tc g2-3 generate  n=$N k=$K mode=random
tc g2-4 generate  n=$N k=$K mode=random shuffle=1
tc g2-5 generate  n=$N k=$K mode=random shuffle=1
tc g2-6 generate  n=$N k=$K mode=unbalanced
tc g2-7 generate  n=$N k=$K mode=unbalanced shuffle=1
tc g2-8 generate n=$N k=$K mode=rainbow shuffle=1
tc g2-9 generate n=$N k=$K mode=rainbow shuffle=1
tc g2-a generate n=$N k=$K mode=a
tc g2-b generate n=$N k=$K mode=b

N=100
K=26

group group3 70
limits n=$N klo=1 khi=26
tc g3-1 generate n=$N k=$K mode=rainbow
tc g3-2 generate n=$N k=$K mode=random
tc g3-3 generate n=$N k=$K mode=random
tc g3-4 generate n=$N k=$K mode=random shuffle=1
tc g3-5 generate n=$N k=$K mode=random shuffle=1
tc g3-6 generate n=$N k=$K mode=unbalanced
tc g3-7 generate n=$N k=$K mode=unbalanced shuffle=1
tc g3-8 generate n=$N k=5 mode=rainbow
tc g3-9 generate n=$N k=10 mode=rainbow
tc g3-10 generate n=$N k=5 mode=rainbow shuffle=1
tc g3-11 generate n=$N k=10 mode=rainbow shuffle=1

tc g3-a generate n=$N k=$K mode=a
tc g3-b generate n=$N k=$K mode=b
tc g3-c generate n=$N k=$K mode=c
tc g3-d generate n=$N k=$K mode=d
tc g3-e generate n=$N k=$K mode=e
tc g3-f generate n=$N k=$K mode=f
tc g3-g generate n=$N k=$K mode=g
tc g3-h generate n=$N k=$K mode=h
tc g3-i generate n=$N k=$K mode=i
tc g3-j generate n=$N k=$K mode=j
tc g3-k generate n=$N k=$K mode=k
tc g3-l generate n=$N k=$K mode=l
tc g3-m generate n=$N k=$K mode=m
tc g3-n generate n=$N k=$K mode=n
tc g3-o generate n=$N k=$K mode=o
tc g3-p generate n=$N k=$K mode=p
tc g3-q generate n=$N k=$K mode=q
tc g3-r generate n=$N k=$K mode=r
tc g3-s generate n=$N k=$K mode=s
tc g3-t generate n=$N k=$K mode=t
tc g3-u generate n=$N k=$K mode=u
tc g3-v generate n=$N k=$K mode=v
tc g3-w generate n=$N k=$K mode=w
tc g3-x generate n=$N k=$K mode=x
tc g3-y generate n=$N k=$K mode=y
tc g3-z generate n=$N k=$K mode=z

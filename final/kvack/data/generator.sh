#!/usr/bin/env bash

PPATH=$(realpath ..)
. gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_random.py

samplegroup
sample 1
sample 2
sample 3

group group1 100
include_group sample
tc random-01 gen_random n=1 k=1 length=1


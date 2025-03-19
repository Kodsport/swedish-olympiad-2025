#!/bin/bash
. ../testdata_tools/gen.sh

use_solution sol.cc


samplegroup
limits maxn=20 maxe=20
sample 1
sample 2
sample 3

group group1 40
limits maxn=1000 maxe=1000
include_group sample
tc_manual ../manual_data/01.01.01.in
tc_manual ../manual_data/01.01.02.in
tc_manual ../manual_data/01.01.03.in
tc_manual ../manual_data/01.01.04.in
tc_manual ../manual_data/01.01.05.in
tc_manual ../manual_data/01.01.06.in
tc_manual ../manual_data/01.01.07.in
tc_manual ../manual_data/01.01.08.in
tc_manual ../manual_data/01.01.09.in
tc_manual ../manual_data/01.01.10.in
tc_manual ../manual_data/01.01.11.in
tc_manual ../manual_data/01.01.12.in
tc_manual ../manual_data/01.01.13.in
tc_manual ../manual_data/01.01.14.in
tc_manual ../manual_data/01.01.15.in
tc_manual ../manual_data/01.01.16.in
tc_manual ../manual_data/01.01.17.in
tc_manual ../manual_data/01.01.18.in
tc_manual ../manual_data/01.01.19.in
tc_manual ../manual_data/01.01.20.in
tc_manual ../manual_data/01.02.01.in
tc_manual ../manual_data/01.02.02.in
tc_manual ../manual_data/01.02.03.in
tc_manual ../manual_data/01.02.04.in
tc_manual ../manual_data/01.02.05.in
tc_manual ../manual_data/01.02.06.in
tc_manual ../manual_data/01.02.07.in
tc_manual ../manual_data/01.02.08.in
tc_manual ../manual_data/01.02.09.in
tc_manual ../manual_data/01.02.10.in
tc_manual ../manual_data/01.02.11.in
tc_manual ../manual_data/01.02.12.in
tc_manual ../manual_data/01.02.13.in
tc_manual ../manual_data/01.02.14.in
tc_manual ../manual_data/01.02.15.in
tc_manual ../manual_data/01.02.16.in
tc_manual ../manual_data/01.02.17.in
tc_manual ../manual_data/01.02.18.in
tc_manual ../manual_data/01.02.19.in
tc_manual ../manual_data/01.02.20.in


group group2 24
limits maxn=100000 maxe=1000
include_group group1
tc_manual ../manual_data/02.01.in
tc_manual ../manual_data/02.02.in
tc_manual ../manual_data/02.03.in
tc_manual ../manual_data/02.04.in
tc_manual ../manual_data/02.05.in
tc_manual ../manual_data/02.06.in
tc_manual ../manual_data/02.07.in
tc_manual ../manual_data/02.08.in
tc_manual ../manual_data/02.09.in
tc_manual ../manual_data/02.10.in
tc_manual ../manual_data/02.11.in
tc_manual ../manual_data/02.12.in
tc_manual ../manual_data/02.13.in
tc_manual ../manual_data/02.14.in
tc_manual ../manual_data/02.15.in
tc_manual ../manual_data/02.16.in
tc_manual ../manual_data/02.17.in
tc_manual ../manual_data/02.18.in
tc_manual ../manual_data/02.19.in
tc_manual ../manual_data/02.20.in

group group3 20
limits maxn=100000 maxe=1000000000
include_group group2
tc_manual ../manual_data/03.01.in
tc_manual ../manual_data/03.02.in
tc_manual ../manual_data/03.03.in
tc_manual ../manual_data/03.04.in
tc_manual ../manual_data/03.05.in
tc_manual ../manual_data/03.06.in
tc_manual ../manual_data/03.07.in
tc_manual ../manual_data/03.08.in
tc_manual ../manual_data/03.09.in
tc_manual ../manual_data/03.10.in
tc_manual ../manual_data/03.11.in
tc_manual ../manual_data/03.12.in
tc_manual ../manual_data/03.13.in
tc_manual ../manual_data/03.14.in
tc_manual ../manual_data/03.15.in
tc_manual ../manual_data/03.16.in
tc_manual ../manual_data/03.17.in
tc_manual ../manual_data/03.18.in
tc_manual ../manual_data/03.19.in
tc_manual ../manual_data/03.20.in

group group4 16
limits maxn=500000 maxe=1000000000000
include_group group3
tc_manual ../manual_data/04.01.in
tc_manual ../manual_data/04.02.in
tc_manual ../manual_data/04.03.in
tc_manual ../manual_data/04.04.in
tc_manual ../manual_data/04.05.in
tc_manual ../manual_data/04.06.in
tc_manual ../manual_data/04.07.in
tc_manual ../manual_data/04.08.in
tc_manual ../manual_data/04.09.in
tc_manual ../manual_data/04.10.in
tc_manual ../manual_data/04.11.in
tc_manual ../manual_data/04.12.in
tc_manual ../manual_data/04.13.in
tc_manual ../manual_data/04.14.in
tc_manual ../manual_data/04.15.in
tc_manual ../manual_data/04.16.in
tc_manual ../manual_data/04.17.in
tc_manual ../manual_data/04.18.in
tc_manual ../manual_data/04.19.in
tc_manual ../manual_data/04.20.in

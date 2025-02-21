echo "Running verifyproblem ${@:1} -l debug > /tmp/analysis 2> /dev/null"
verifyproblem ${@:1} -l debug > /tmp/analysis 2> /dev/null
python3 testdata_tools/analyzetestgroups.py --file /tmp/analysis $1

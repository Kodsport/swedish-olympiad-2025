set -e


for ((i = 1; ;++i)); do
    pypy3 gen.py $i > randomInput
    pypy3 harry.py < randomInput > myOutput
    pypy3 harry-bug.py < randomInput > bruteOutput
    diff -w myOutput bruteOutput || break
    echo "Passed test: " $i
done

echo -e "\nWA on the following test:"
cat randomInput
echo "\nYour answer is: "
cat myOutput
echo "\nCorrect answer is: "
cat bruteOutput
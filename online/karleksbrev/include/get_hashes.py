#!/usr/bin/python3

# For each testcase, run a program and read the hash of the run
# Used to verify that the randomness is consistent across runnes

import os
import subprocess


test_case_dir = '../../data/secret'
stderr_outputs = []

lang = ["cpp", "py", "cs", "java"][1]

if lang == "py":
    directory = "python3"
    runcommand = ['pypy3', 'main.py']
if lang == "cpp":
    directory = "python3"
    runcommand = ["./hasher"]
if lang == "cs":
    directory = "csharp"
    runcommand = ["./bin/Debug/net8.0/kattis"]
if lang == "java":
    directory = "java"
    runcommand = ["java", "Main"]

os.chdir(directory)
unique_q = {}
for root, _, files in os.walk(test_case_dir):
    for file in files:
        test_case_path = os.path.join(root, file)
        if test_case_path.split(".")[-1] != "in":
            continue
        
        tc_name = test_case_path.split("/")[-1]
        if tc_name not in unique_q:
            unique_q[tc_name] = test_case_path

testcases = list(unique_q.values())
testcases.sort()


for tc_path in testcases:
    with open(tc_path, 'r') as test_case:
        result = subprocess.run(
            runcommand,
            stdin=test_case,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Store the stderr output
        stderr_outputs.append((file, result.stderr))
        print("another one")

# Write all stderr outputs to a file
with open(f'{lang}_hashes.txt', 'w') as f:
    for test_case_name, stderr in stderr_outputs:
        f.write(stderr)

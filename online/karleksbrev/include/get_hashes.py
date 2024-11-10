#!/usr/bin/python3

# For each testcase, run a program and read the hash of the run
# Used to verify that the randomness is consistent across runnes

import os
import subprocess


test_case_dir = '../data/secret'
stderr_outputs = []

lang = ["cpp", "py"][1]

if lang == "py":
    runcommand = ['pypy3', 'python3/main.py']
if lang == "cpp":
    runcommand = ["./cpp/hasher"]

for root, _, files in os.walk(test_case_dir):
    for file in files:
        test_case_path = os.path.join(root, file)
        if test_case_path.split(".")[-1] != "in":
            continue
        
        with open(test_case_path, 'r') as test_case:
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

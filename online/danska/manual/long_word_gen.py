import random
import string

m = 200
n = 100

test_case = []
for _ in range(m):
    random_string = ''.join(random.choices(string.ascii_lowercase, k=n))
    test_case.append(random_string)

print(f"{m} {n}")
print("\n".join(test_case))

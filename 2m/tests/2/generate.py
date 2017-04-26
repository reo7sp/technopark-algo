import random
import os
from tqdm import tqdm

n = int(os.sys.argv[1])
print(n)
for i in tqdm(range(n)):
    print(random.randint(1, 9999999), end=' ')
print()
print(int(os.sys.argv[2]))
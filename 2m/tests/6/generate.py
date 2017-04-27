import random, string, os

for _ in range(int(os.sys.argv[1])):
    print(''.join(chr(random.randint(33,126)) for _ in range(random.randint(1, int(os.sys.argv[2])))))


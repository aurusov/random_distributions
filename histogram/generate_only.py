from numpy import random

random.seed(12345)

for i in random.exponential(3.743, size=1000000):
    print i

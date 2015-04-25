from numpy import random
from matplotlib import pyplot

random.seed(12345)
sequence = random.normal(size=1000000, loc=30, scale=5)

pyplot.hist(sequence, bins=20)
pyplot.show()

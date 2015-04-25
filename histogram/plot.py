import numpy
from matplotlib import pyplot

a = numpy.genfromtxt('data.csv')

print "min=%f, max=%f, mean=%f, std_dev=%f" % (a.min(), a.max(), a.mean(), numpy.std(a))

pyplot.hist(a, bins=30)
pyplot.show()

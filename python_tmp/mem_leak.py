import time

class LeakTest(object):
    def __init__(self, desc):
        self.desc = desc
        print 'Object with id %d.%s born here.' % (id(self), self.desc)
    def __del__(self):
        print 'Object with id %d.%s dead here.' % (id(self), self.desc)
def test():
    T1 = LeakTest('T1')

test()
T2 = LeakTest('T2')
T3 = LeakTest('T3')
print 'will sleep 1 seconds'
time.sleep(1)
del T3
print 'will sleep 1 seconds'

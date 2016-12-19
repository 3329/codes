func = lambda x, y: x + y
print func(4, 5)

print "----------------------------------"
def func(x, y):
	return x + y
print func(4, 5)
def test(f, a, b):
	print "test"
	print f(a, b)

test(func, 3, 4)

test((lambda x, y: x**2 + y), 6, 9)
re = map((lambda x: x+3), [1, 3, 5, 6])

def func(a):
	if a > 100:
		return True
	else:
		return False

print filter(func, [10, 56, 101, 500])


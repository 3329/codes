def add_end(L=None):
	if L is None:
		L = []
	else:
		L.appaend('end')
	return L	

def power(x, n=2):
	s = 1
	while n > 0:
		n = n - 1
		s = s * x
	return s

def fact(n):
	if n==1:
		return 1
	return n * fact(n - 1)



for i in range(10):
	print i+1, "\t\b\b\b\b:", power(i+1)

print "---------------------"
print power(10, 3)


#!/usr/local/bin/python 

def fn(x, y):
	return x * 10 + y

print reduce(fn, [1, 3, 5, 7, 9])

print sorted([36, 10, 90, 89, 76])

def cmp_ignore_case(s1, s2):
	u1 = s1.upper()
	u2 = s2.upper()
	if u1 < u2:
		return -1
	elif u1 > u2:
		return 1
	else:
		return 0

print cmp_ignore_case("iiiiooio", "poop")
print cmp_ignore_case("Hello", "Hello")
print cmp_ignore_case("Hello", "Aello")

def sum(x, y):
	return x+y

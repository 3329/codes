L = []
n = 1
while n <= 99:
	L.append(n)
	n = n + 2

for i in L:
	print i

L = ["andy", "barry", "ice", "ken", "young"]
print L[0:3]
print L[:3]
print L[1:3]
print L[-2:]
print L[::2]

for x, y in [(1, 1), (2, 4), (3, 9)]:
	print x, "\t", y

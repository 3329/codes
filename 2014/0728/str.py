classmates = ["Young", "andy", "ice"]

print "------------------------"
print "classmates's len:", len(classmates)
for i in classmates:
	print i

classmates.append("linda")
classmates.insert(1, "jack")
print "------------------------"
print "classmates's len:", len(classmates)
for i in classmates:
	print i


classmates.pop(1)
classmates.pop()
print "------------------------"
print "classmates's len:", len(classmates)
for i in classmates:
	print i

print "------------------------"
t = (1, )
u = (1)
print len(t)
print u

print "------------------------"
t = ('a', 'b', ['A', 'B'])
t[2][0] = 'X'
t[2][1] = 'Y'
print t

age = 3
if age >= 10:
	print ">10"
elif age >= 20:
	print ">20"
else:
	print "others"

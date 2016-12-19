class Human(object):
	def __init__(self, input_gender):
		self.gender = input_gender
	def printGender(self):
		print self.gender

Young = Human('male')
print Young.gender
Young.printGender()

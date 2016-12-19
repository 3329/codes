#!/usr/bin/python

import fnmatch
import os
import string 


def doDecompressFileToTargetDir(dataSourceDir, targetDir):
	print "running ..."
	for filename in os.listdir(dataSourceDir):
		# 1. fllow the rule to pattern file(*.AVL.gz)
		if fnmatch.fnmatch(filename, '*.AVL.gz'):
			filename = os.path.join(dataSourceDir, filename)
			# 2. unzip file to the specidied directory
			decompressFileToDir(filename, targetDir)

	print "OK ..."

def decompressFile(filename):
	if os.path.isfile(filename):
		os.system(''.join(["gzip -d ", filename]))
	else:
		print "ERROR decompressFile(): file '", filename ,"' is not exist."


def decompressFileToDir(filename, targetDir):
	dirname = os.path.basename(filename)[6:11]
	dirname = os.path.join(targetDir, dirname)
	if not os.path.isdir(dirname):
		#print "mkdirs():", dirname
		os.makedirs(dirname)
	# 1. copy file to target directory
	os.system(''.join(["cp ", filename, " ", dirname]))
	# 2. decomporess file 
	target_filename = os.path.join(dirname, os.path.basename(filename))
	#print "targetFileName:", target_filename
	decompressFile(target_filename)


##################### do something ############################
# define data source directory & target data directory
DATA_SOURCE_DIR = "/home/young/AVL"
DATA_TARGET_DIR  = "/home/young/test/UNICOM/TARGET_DIR"


doDecompressFileToTargetDir(DATA_SOURCE_DIR, DATA_TARGET_DIR)

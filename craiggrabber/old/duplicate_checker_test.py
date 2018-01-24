import urllib.request, re, os, urllib, hashlib, getpass, requests, codecs, math, operator, sys
from bs4 import BeautifulSoup
from PIL import ImageChops, Image
from functools import reduce
from tkinter import Label, Entry, filedialog, Button, messagebox, Tk, StringVar
from collections import defaultdict
from functools import wraps

def cache_this_function(function):
	function.cache = {}
	@wraps(function)
	def wrapper(*args):
		try:
			return function.cache[args]
		except KeyError:
			function.cache[args] = result = function(*args)
			return result   
	return wrapper


def walk(ignore=['','tempxyz','./']):
	for directory in os.walk('./'):
		directory = directory[0]
		if directory in ignore:
			continue
		yield directory

def is_duplicate(this_path, other_path):
	md5 = md5hash(this_path)
	for otherfile in other_path:
		if md5hash(otherfile) != md5:
			return True

def remove_directory(directory):
	os.system('rm -rf "%s"' % directory)

def remove_duplicates():
	'''
	uses other function to walk the directories and remove duplicate files
	in directory
	'''
	found = defaultdict(set)
	for directory in walk():
		# since md5 is expensive, let's try and narrow the list of comparisons
		# by only checking duplicates against same sized files
		size = get_size(directory)
		if size in found:
			if is_duplicate(directory, found[size]):
				remove_directory(directory)
				# use continue to avoid excessive indentations
				continue
		# ok got a new unique file, so lets add it to our dictionary
		found[size].add(directory)

def get_size(directory):
	total_size = 0
	for dirpath, dirnames, filenames in os.walk(directory):
		for f in filenames:
			fp = os.path.join(dirpath, f)
			total_size += os.path.getsize(fp)
	return total_size

@cache_this_function
def md5hash(directory):
	'''
	return the md5 hash of a file
	This take a bit of time so use a simple cache so that you only do it once
	per file.  If you use py3 try functools, otherwise look up how to do this,
	it's easy
	'''
	return hashlib.md5(directory.encode('utf-8'))


remove_duplicates()

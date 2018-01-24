"""
This program takes a craiglist web page,
finds all the links that lead to craigslist pages.
It then goes into the pages, and puts all the images,
and text into one folder that pertain to the pages.
Requires:
	BeautifulSoup
	Python3
	Unix Shell
	requests
	tkinter
Credits and Thanks to:
	Stackoverflow
	reddit.com/r/learnpython
	Python Documentation
	BeautifulSoup Documentation
	Nikola Kovacevic: https://plus.google.com/+NikolaKovacevic1/posts
Future Desires:
Multi-Threading
Simplify
Check for potential Bugs
Make more pretty GUI (possibly with ttk)
"""

import urllib.request, queue, threading, re, os, urllib, hashlib, getpass, requests, codecs, math, operator, sys
from bs4 import BeautifulSoup
from functools import reduce
from tkinter import ttk, Label, Entry, filedialog, Button, messagebox, Tk, StringVar
from collections import defaultdict

class craiggrabber(object):

		def __init__(self,gui):
			self.gui = gui
			if gui:
				self.root_frame = Tk()
				self.path_var = StringVar()
				self.path_var.set('')
				Label(self.root_frame, text="Enter the data").grid(row=1, column=1)
				Label(self.root_frame, text="Directory to copy to:").grid(row=3)
				Label(self.root_frame, text="Url:").grid(row=4)
				self.path_entry = Entry(self.root_frame, textvariable=self.path_var)
				self.url_entry = Entry(self.root_frame)
				self.path_entry.grid(row=3, column=1)
				self.url_entry.grid(row=4, column=1)
				self.next_btn = Button(self.root_frame, text='Go', command=self.gui_start)
				self.directory_btn = Button(self.root_frame, text='Browse...', command=self.getting_path)
				self.directory_btn.grid(row=3, column=3)
				self.next_btn.grid(row=6, column=1)
				self.root_frame.mainloop()
			if not gui:
				self.paths()
				self.url = self.website()
				if self.isaccount:
					self.successful = False
					while not self.successful:
						self.username = input("Username(email) >")
						self.password = str(getpass.getpass("Passowrd(Does not display) >"))
						self.successful = self.login_session()
						if not self.successful:
							print("Bad Email or Password")
				else:
					self.generalwebpageparser()
				self.duplicates_checker()

		def user_type(self):
			"""
			It searches the url to see if it is a General Web page or an Account Web-page, if it is not a
			valid craigslist page it returns 500
			"""

			accounturl = "https://accounts.craigslist.org"
			match = re.search(r'^(https?:\/\/)?([a-z_-]+)\.craigslist\.org\/search\/(\w+)?', self.url)

			if self.url[0:31] == accounturl and not match: #Compares it to accounturl string
				return True
			elif match:
				return False
			else:
				return 500


		def accountwebpageparser(self):
			"""
			Parses through an account's inventory page(s) and takes the index
			"""
			trs = self.parsed_html.find_all('tr')
			tds = BeautifulSoup(str(BeautifulSoup(str(trs)).find_all('td')))
			self.links = []
			for self.link in tds('a'):
				if self.link.get('href')[0] == 'h':
					self.links.append(self.link.get('href'))
			self.postinginfograb()
			self.duplicates_checker()

		def login_session(self, justwantbool=False):
			"""
			Logs onto the website if it is an account web page, if it cannot log on
			it returns False
			Returns:
				boolean
			"""
			useragent = """Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko)
						Chrome/42.0.2311.90 Safari/537.36"""
			headers = {"User-Agent": useragent,
					   "Host": "accounts.craigslist.org",
					   "Origin": "https://accounts.craigslist.org",
					   "Referer": "https://accounts.craigslist.org/login"}

			data = {"step": "confirmation",
					"inputEmailHandle": self.username,
					"inputPassword": self.password}

			session = requests.Session()
			session.get("https://accounts.craigslist.org/login")
			sessionpg = session.post('https://accounts.craigslist.org/login', headers=headers, data=data)
			sessionpg = session.get(self.url)
			sessionpg.encoding = 'utf-8'
			self.parsed_html = BeautifulSoup(sessionpg.text)
			error = self.parsed_html.title.string
			if error != 'craigslist: account log in':
				if justwantbool:
					return True
				self.accountwebpageparser()
				return True
			return False


		def generalwebpageparser(self):
			"""
			Parses through the web page to find all of the web pages on the index page
			"""

			plain_text_html = self.site.read().decode('utf-8') #creates plain text of the website
			self.parsed_html = BeautifulSoup(plain_text_html) #makes it a BeautifulSoup obj
			paragraph = self.parsed_html.find_all('p') #finds the paragraph
			soup = BeautifulSoup(str(paragraph))
			self.links = [link.get('href') for link in soup('a')] #puts the links in a list
			reurl = re.search(r'^(https?:\/\/)?([a-z_-]+)\.craigslist\.org\/search\/(\w+)?', self.url)
			urlhead = reurl.group(1) + reurl.group(2) + ".craigslist.org" #formats the head of the url
			self.links = list(set(self.links)) #removes duplicates
			self.links = [i for i in self.links if len(str(i)) > 5]
			for index, link in enumerate(self.links): #adds the head of the url to all of the urls
				self.links[index] = urlhead+str(link)
			self.postinginfograb()
			self.duplicates_checker()

		def postinginfograb(self):
			"""
			Makes the folders for each of the links and names it by opening all of the links, and getting
			the titles
			"""
			for link in self.links:
				self.parsed_html = BeautifulSoup(urllib.request.urlopen(link).read().decode('utf-8'))
				self.string = self.parsed_html.title.string
				self.string = ''.join(e for e in self.string if e.isalnum() or e == ' ')
				if os.path.isdir(str(self.string)):
					self.same_file_test()
					os.chdir('..')
				else:
					os.system('mkdir ' + '"%s"' % str(self.string))
					os.chdir("%s" % str(self.string))
					self.imagegrabber()
					self.textmaker()
					os.chdir("..")

		def imagegrabber(self):
			"""
			It find all of the image urls and copies them to the current directory
			Creates:
				Images in the current directory
			"""
			paragraph = self.parsed_html.find(id='thumbs')
			soup = BeautifulSoup(str(paragraph))
			links = [link.get('href') for link in soup('a')] #all of the photo links
			for index, link in enumerate(links):
				urllib.request.urlretrieve(str(link), str(index)+".jpg") #saves the image

		def textmaker(self):
			"""
			This puts all of the web page text into a txt file in the current directory
			Creates:
				info file in the current directory with all of the textual information
			"""
			paragraph = str(self.parsed_html.find(id='postingbody'))
			paragraph = self.remove_tags(paragraph)
			price = str(self.parsed_html.find(class_='price'))
			price = self.remove_tags(price)
			header = str(self.parsed_html.title.string) + "\n\n"
			with codecs.open("info.txt", "a", "utf-8") as myfile:
				myfile.write(header + price + paragraph) #Creates the file
				myfile.close()

		def remove_tags(self, paragraph):
			"""
			Creates html text to have no tags
			Returns:
				text without tags
			"""
			return (BeautifulSoup(paragraph)).text

		def paths(self):
			"""
			Tests to see if the path and url(if GUI) are valid, if so it changes to that path and url
			"""
			while True: #tests if valid path and url(if GUI) and url to go to
				if not self.gui:
					self.path = input("Path >")
					if not os.path.isdir(self.path):
						print("Invalid path.")
					else:
						os.chdir(self.path)
						break
				if self.gui:
					if os.path.isdir(self.path_entry.get()):
						self.path = self.path_entry.get()
						os.chdir(self.path)
						return True
					else:
						messagebox.showinfo("Bad Path", "This Path is invalid")
						return False

		def website(self):
			"""
			Tests the url that it is given to see if it is valid and is able to connect to it
			Returns:
				url
			"""
			while True: #tests validity of the web page
				if not self.gui:
					self.url = input("Webpage >")
				if self.gui:
					self.url = self.url_entry.get()
				try:
					self.site = urllib.request.urlopen(self.url) #opens the website
				except ValueError:
					if self.gui:
						messagebox.showinfo("Bad Url", "This is an invalid Url")
						return False
					print("Check the connection and url then try again, it was invalid.")
				self.isaccount = self.user_type()
				if self.isaccount == 500:
					if self.gui:
						messagebox.showinfo("Bad Url", "This is not a page with craiglist items")
						return False
					else:
						print("Check the connection and url then try again, it was invalid.")
				else:
					if not self.gui:
						return self.url
					return True

		def gui_start(self):
			"""
			This is the initial steps the GUI has to take if it is a login, if not
			it calls generalwebpageparser
			"""
			if not self.paths():
				return
			if not self.website():
				return
			if self.isaccount:
				Label(self.root_frame, text="Enter Username:").grid(row=7)
				Label(self.root_frame, text="Enter Password:").grid(row=8)
				self.user_ent = StringVar(self.root_frame)
				username_ent = Entry(self.root_frame, textvariable=self.user_ent)
				self.pass_ent = StringVar(self.root_frame)
				password_ent = Entry(self.root_frame, show="*", textvariable=self.pass_ent)
				username_ent.grid(row=7, column=2)
				password_ent.grid(row=8, column=2)
				Button(self.root_frame, text='Next', command=(lambda: self.login_trial(self.user_ent.get(),self.pass_ent.get()))).grid(row=9, column=1)
			else:
				self.generalwebpageparser()

		def login_trial(self, username, password):
			self.username = username
			self.password = password
			if len(self.username) != 0:
				self.success = self.login_session(True)
				if self.success:
					messagebox.showinfo("Success!", "Logged in, will start process!")
					self.login_session()
					self.duplicates_checker()
				if not self.success:
					 messagebox.showinfo("Oh no!", "Login seems not to be correct")

		def getting_path(self):
			"""
			This is the function to get the directory when browsing through files (when browse button is
			clicked)
			"""
			self.path_var.set(filedialog.askdirectory())

		def same_file_test(self):
			"""
			This tests to see if the filename already exists, if so it continues to add
			a number to the end by one until there is a non existent filename then creates
			the directory using create_if_doesnt_exist
			"""

			my_dir_base = self.string
			self.my_dir_name = my_dir_base
			created = False
			i = 1
			while not created:
				self.my_dir_name = my_dir_base + ' ({})'.format(i)
				i += 1
				created = self.create_if_doesnt_exist()
			os.chdir(self.my_dir_name)
			self.imagegrabber()
			self.textmaker()

		def create_if_doesnt_exist(self):
			"""
			This creates a directory so long it does not exist
			Returns:
				boolean
			"""
			if self.my_dir_name not in os.listdir():
				os.mkdir(self.my_dir_name)
				return True
			return False


		def walk(self, ignore=['','tempxyz','./']):
			"""
			This walks through the directories
			yields:
				directory
			"""
			for directory in os.walk('./'):
				directory = directory[0]
				if directory in ignore:
					continue
				yield directory

		def is_duplicate(self, this_path, other_path):
			"""
			This compares the files using the md5 hash
			Returns:
				boolean
			"""
			md5 = self.md5hash(this_path)
			for otherfile in other_path:
				if self.md5hash(otherfile) != md5:
					return True

		def remove_directory(self, directory):
			os.system('rm -rf "%s"' % directory)

		def duplicates_checker(self):
			"""
			This finds the duplicates by comparing the size then calling is_duplicate.
			If it is not a duplicate adds it to the found dictionary.
			"""
			found = defaultdict(set)
			for directory in self.walk():
				size = self.get_size(directory)
				if size in found:
					if self.is_duplicate(directory, found[size]):
						self.remove_directory(directory)
						continue
				found[size].add(directory)

		def get_size(self, directory):
			"""
			Gets the size of the directory
			Returns:
				total_size(int)
			"""
			total_size = 0
			for dirpath, dirnames, filenames in os.walk(directory):
				for f in filenames:
					fp = os.path.join(dirpath, f)
					total_size += os.path.getsize(fp)
			return total_size

		def md5hash(self, directory):
			"""
			Returns a md5 hash of the directory
			"""
			return hashlib.md5(directory.encode('utf-8'))



if __name__ == '__main__':
	if len(sys.argv) == 1:
		print('made it here')
		craiggrabber(False)
	if len(sys.argv) == 2:
		if sys.argv[1] == '--graphics' or sys.argv[1] == '-g':
			craiggrabber(True)
		if sys.argv[1] == '--help' or sys.argv[1] == '-h':
			print("There is only one option for this, which is graphics -g or --g")
	else:
		print("This is not a correct flag or Entry, type --help or -h to get information on commands")
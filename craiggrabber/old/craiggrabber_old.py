"""
This program takes a craiglist webpage,
finds all the links that lead to craigslist pages.
It then goes into the pages, and puts all the images,
and text into one folder that pretain to the pages.

Requires:
	BeautifulSoup
	Python3
	Unix Shell
	requests
	Pillow

Credits and Thanks to:
	Nikola Kovacevic: https://plus.google.com/+NikolaKovacevic1/posts
	Stackoverflow
	reddit.com/r/learnpython
	Python Documentation
	BeautifulSoup Documentation
	effbot image comparing algorithm: http://effbot.org/zone/pil-comparing-images.htm

Future Desires:
Turning this into a Class
Merging with gui
"""
import urllib.request, re, os, urllib, getpass, requests, codecs, math, operator
from bs4 import BeautifulSoup
from PIL import ImageChops, Image
from functools import reduce


def main():
	"""
	Main function
	Gets a path where the program will write the files
	Gets an url from the page it gets its info from
	Account Page VS General Page: Account page is where the someone logs on
	and it shows all their posts while general
	is any page that is visible to the public
	"""
	paths()
	url = website()
	site = urllib.request.urlopen(url)
	isaccount = user_type(url) #checks to see ifaccount page or a general page
	if isaccount:
		successful = False
		while not successful:
			username = input("Username(email) >")
			password = str(getpass.getpass("Passowrd(Does not display) >"))
			successful = login_session(username, password, url)
			if not successful:
				print("Bad Email or Password")
	else:
		generalwebpageparser(site, url)
	duplicates_checker()

def user_type(url):
	"""
	It searches the url to see if it is a General Webpage or an Account Webpage, if it is not a
	vaild craigslist page it returns 500
	"""

	accounturl = "https://accounts.craigslist.org"
	match = re.search(r'^(https?:\/\/)?([a-z_-]+)\.craigslist\.org\/search\/(\w+)?', url)

	if url[0:31] == accounturl and not match: #Compares it to accounturl string
		return True
	elif match:
		return False
	else:
		return 500

def accountwebpageparser(parsed_html):
	"""
	Parses through an account's inventory page(s) and takes the index
	"""
	
	trs = parsed_html.find_all('tr')
	tds = BeautifulSoup(str(BeautifulSoup(str(trs)).find_all('td')))
	links = []
	for link in tds('a'):
		if link.get('href')[0] == 'h':
			links.append(link.get('href'))
	postinginfograb(links)

def generalwebpageparser(site, url):
	"""
	Parses through the webpage to find all of the webpages on the index page
	"""

	plain_text_html = site.read().decode('utf-8') #creates plain text of the website
	parsed_html = BeautifulSoup(plain_text_html) #makes it a BeautifulSoup obj
	paragraph = parsed_html.find_all('p') #finds the paragraph
	soup = BeautifulSoup(str(paragraph))
	links = [link.get('href') for link in soup('a')] #puts the links in a list
	reurl = re.search(r'^(https?:\/\/)?([a-z_-]+)\.craigslist\.org\/search\/(\w+)?', url)
	urlhead = reurl.group(1) + reurl.group(2) + ".craigslist.org" #formats the head of the url
	links = list(set(links)) #removes duplicates
	links = [i for i in links if len(str(i)) > 5]
	for index, link in enumerate(links): #adds the head of the url to all of the urls
		links[index] = urlhead+str(link)
	postinginfograb(links)


def postinginfograb(links):
	"""
	Makes the folders for each of the links and names it by opening all of the links, and getting
	the titles
	"""
	for link in links:
		parsed_html = BeautifulSoup(urllib.request.urlopen(link).read().decode('utf-8'))
		string = parsed_html.title.string
		string = ''.join(e for e in string if e.isalnum() or e == ' ')
		if os.path.isdir(str(string)):
			same_file_test(str(string), parsed_html)
			os.chdir('..')
		else:
			os.system('mkdir ' + '"%s"' % str(string))
			os.chdir("%s" % str(string))
			imagegrabber(parsed_html)
			textmaker(parsed_html)
			os.chdir("..")

def imagegrabber(parsed_html):
	"""
	It find all of the image urls and copies them to the current directory
	Creates:
		Images in the current directory
	"""
	paragraph = parsed_html.find(id='thumbs')
	soup = BeautifulSoup(str(paragraph))
	links = [link.get('href') for link in soup('a')] #all of the photo links
	for index, link in enumerate(links):
		urllib.request.urlretrieve(str(link), str(index)+".jpg") #saves the image

def textmaker(parsed_html):
	"""
	This puts all of the webpage text into a txt file in the current directory
	Creates:
		infofile in the current directory with all of the textual information
	"""
	paragraph = str(parsed_html.find(id='postingbody'))
	paragraph = remove_tags(paragraph)
	price = str(parsed_html.find(class_='price'))
	price = remove_tags(price)
	header = str(parsed_html.title.string) + "\n\n"
	with codecs.open("info.txt", "a", "utf-8") as myfile:
		myfile.write(header + price + paragraph) #Creates the file
		myfile.close()

def remove_tags(text):
	"""
	Creates html text to have no tags
	Returns:
		text without tags
	"""
	return (BeautifulSoup(text)).text

def paths(path=''):
	"""
	Tests to see if the path is vaild, if so it changes to that path
	"""
	while True: #tests if valid path to go to
		path = input("Path >")
		if not os.path.isdir(path):
			print("Invalid path.")
		else:
			os.chdir(path)
			break

def website(url=''):
	"""
	Tests the url that it is givin to see if it is vaild and is able to connect to it
	Returns:
		url
	"""
	while True: #tests vailidity of the webpage
		url = input("Webpage >")
		try:
			urllib.request.urlopen(url) #opens the website
			return url
		except ValueError:
			print("Check the connection and url then try again, it was invalid.")

def same_file_test(string, parsed_html):
	"""
	This tests to see if the filename already exists, if so it continues to add
	a number to the end by one until there is a non existant filename then creates
	the directory using create_if_doesnt_exist
	"""

	my_dir_base = string
	my_dir_name = my_dir_base
	created = False
	i = 1
	while not created:
		my_dir_name = my_dir_base + ' ({})'.format(i)
		i += 1
		created = create_if_doesnt_exist(my_dir_name)
	os.chdir(my_dir_name)
	imagegrabber(parsed_html)
	textmaker(parsed_html)

def create_if_doesnt_exist(dir_name):
	"""
	This creates a directory so long it does not exist
	Returns:
		boolean
	"""
	if dir_name not in os.listdir():
		os.mkdir(dir_name)
		return True
	return False

def duplicates_checker():
	"""
	duplicates_checker checks for duplicates by comparing every directory in the parent directory
	using the first image in the directories. It then deletes the second directory in the comapare
	if they are duplicates and adds it to the list donotwant1 which is a list that tells the for
	loop to ignore that directory when interating.
	"""
	subdirectories = [x[0] for x in os.walk('./')]
	subdirectories = subdirectories[1:] #gets rid of the ./ parent folder
	subdirectories.sort()
	donotwant1 = ['', 'tempxyz']
	for subdirectory1 in subdirectories:
		if not os.path.isdir('tempxyz'):
			os.mkdir('tempxyz')
		donotwant2 = donotwant1
		if subdirectory1 not in donotwant1:
			donotwant2.append(subdirectory1)
			for index2, subdirectory2 in enumerate(subdirectories):
				if subdirectory2 not in donotwant2:
					os.chdir(subdirectory1)
					os.system('cp 0.jpg ../tempxyz/0.jpg')
					os.chdir('..')
					os.chdir(subdirectory2)
					os.system('cp 0.jpg ../tempxyz/1.jpg')
					os.chdir('../tempxyz/')
					if rmsdiff(Image.open('0.jpg'), Image.open('1.jpg')) == 0:
						os.system('rm *')
						os.chdir('..')
						os.system('rm -rf "%s"' % subdirectory2)
						donotwant1.append(subdirectories[index2])
						donotwant2.append(subdirectories[index2])
					else:
						os.chdir('..')
	os.system('rm -rf tempxyz')


def rmsdiff(im1, im2):
	"""Calculate the root-mean-square difference between two images
		Taken from
		http://effbot.org/zone/pil-comparing-images.htm"""

	histogram = ImageChops.difference(im1, im2).histogram()

	# calculate rms
	return math.sqrt(reduce(operator.add,
		map(lambda histogram, i: histogram*(i**2), histogram, range(256))
	) / (float(im1.size[0]) * im1.size[1]))

def login_session(username, password, url,justwantbool=False):
	"""
	Logs onto the website if it is an account webpage, if it cannot log on
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
			"inputEmailHandle": username,
			"inputPassword": password}

	session = requests.Session()
	session.get("https://accounts.craigslist.org/login")
	sessionpg = session.post('https://accounts.craigslist.org/login', headers=headers, data=data)
	sessionpg = session.get(url)
	sessionpg.encoding = 'utf-8'
	parsed_html = BeautifulSoup(sessionpg.text)
	error = parsed_html.title.string
	if error != 'craigslist: account log in':
		if justwantbool:
			return True
		accountwebpageparser(parsed_html)
		return True
	return False
	

if __name__ == "__main__":
	main()

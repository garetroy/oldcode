import urllib.request, re, os
nothing = input()
os.environ['http_proxy']=''
def newsitechecker(site):
	site = urllib.request.urlopen(site)
	html = site.read()
	html = html.decode('utf-8')
	nothing = 0
	print(html)
	for s in html.split():
		if s.isdigit():
			nothing = int(''.join(s))
	same_thing = 'and the next nothing is %s' % str(nothing)
	next_site = 'http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s' % str(nothing)
	print(next_site)
	if html == same_thing:
		newsitechecker(next_site)
	else:
		print(html)

newsitechecker('http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s' % nothing)


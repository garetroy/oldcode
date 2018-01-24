import  zipfile
start = 90052
comments = []


def zipfilesearch(numb):
	archive = zipfile.ZipFile('channel.zip')
	data = archive.read('%s.txt' % str(numb))
	data = data.decode('utf-8')
	nothing = 0
	print(data)
	for s in data.split():
		if s.isdigit():
			nothing = int(''.join(s))
	same_sentence = 'Next nothing is %s' % str(nothing)
	if same_sentence == data:
		comments.append((archive.getinfo('%s.txt' % nothing).comment).decode('utf-8'))
		zipfilesearch(nothing)
	else:
		print(''.join(comments))
		


zipfilesearch(start)
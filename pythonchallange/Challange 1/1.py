import sys

#alpha = 'abcdefghijklmnopqrstuvwxyz'

#def translate(phrase1):
#	phrase =[]
#	for i in phrase1:
		#phrase.append(i)
#	for idx, i in enumerate(phrase):
#		if i in alpha and alpha.index(i) <= 23:
#			phrase[idx] = alpha[alpha.index(i) + 2]
#		elif i in alpha:
#			phrase[idx] = alpha[(alpha.index(i) + 2) - 26]
#	phrase = ''.join(phrase)
#	print(phrase)

### To do it write

#define the original
original = 'abcdefghijklmnopqrstuvwxyz'

#define the shift/translation
shift = 'cdefghijklmnopqrstuvwxyzab'

#translateit using maketrans
text = sys.argv[1]
text.maketrans(original,shift)
### this will make a == c and so on, it compares the two


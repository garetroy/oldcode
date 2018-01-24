from random import randint
from os import system

hangman_versions = ['''
 +---+
 |   |
     |
     |
     |
     |
 ========''','''

 +---+
 |   |
 o   |
     |
     |
     |
 ========''', '''

 +---+
 |   |
 o   |
 |   |
     |
     |
 ========''','''

 +---+
 |   |
 o   |
 |\  |
     |
     |
 ========''','''

 +---+
 |   |
 o   |
/|\  |
     |
     |
 ========''','''

 +---+
 |   |
 o   |
/|\  |
  \  |
     |
 ========''','''

 +---+
 |   |
 o   |
/|\  |
/ \  |
     |
 ========'''
]


def main():
	done = False
	#This part will get a random word
	dic = open('dic.txt')
	possible_words = []
	for i in dic:
		 possible_words.append(i.strip('\n'))
	dic.close()
	word = possible_words[randint(0,len(possible_words))]
	#############################
	#defining all other variables
	incorrect_guessees = 0
	bad_letters =''
	good_letters =''
	hidden_letters = ''
	############################
	while not done:
		system('clear')
		print('Wrong letters guessed so far: %s' % bad_letters)
		print('')
		print(hangman_versions[incorrect_guessees])
		print('')
		hidden_letters = ''
		for letter in word:
			if letter == "-":
				hidden_letters += '-'
			if letter in good_letters:
				hidden_letters += letter
			else:
				hidden_letters += '_ '
		print(hidden_letters)
		#########################
		print('')
		print('What letter do you guess?')
		guess = input('>')
		guess = guess.lower()
		if guess in word:
			good_letters += guess
		if guess not in word:
			bad_letters += guess
			incorrect_guessees += 1
		if '_' not in hidden_letters:
			print('You win!')
			done = True
			print('')
			print(word)
		if incorrect_guessees >=6:
			print('You lose!')
			done = True
			print('')
			print(word)
	play_again = 'yes'
	play_again = input('Play again? (yes/no) >')
	if play_again == 'yes':
		main()
	if play_again == 'no':
		return





main()
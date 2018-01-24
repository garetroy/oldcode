from os import system
import random


def main():
	system('clear')
	num = random.randint(100,999)
	number_guesses = 1
	if playing():
		system('clear')
		print('I am thinking of a 3-digit number. Try to guess what it is.')
		print("Here are some clues:")
		print("""When I say:	That means:
				    Pico        One digit is correct but in the wrong position.
				    Fermi       One digit is correct and in the right position.
				    Bagels      No digit is correct.
				""")
		print('I have thought up a number. You have 10 guesses to get it.')
		while number_guesses < 10:
			print('Guess #%i:' % number_guesses)
			current_guess = int(input('>'))
			while len(str(current_guess)) < 3:
				current_guess = int(input('Enter a 3-digit number >'))
			if current_guess == num:
				print('You guessed it!')
				input('Press Enter to Continue...')
				main()

			else:
				compare(num, current_guess)
				number_guesses += 1
		print('You lost!')
		input('Press Enter to Continue')
		main()





def compare(computer_guess, player_guess):
	computer_str = str(computer_guess)
	player_str = str(player_guess)
	hints = []
	for i in range(len(computer_str)):
		if computer_str[i] == player_str[i]:
			hints.append('Fermi')
		elif computer_str[i] in player_str:
			hints.append('Pico')
		else:
			continue
	if hints == []:
		print('Bagels')
	else:
		hints.sort()
		print(' '.join(hints))


def playing():
	print('Do you want to play?')
	play = input('>')
	if play.lower() == 'yes':
		play = 'y'
	if play.lower() == 'no':
		play = 'n'
	if play.lower() == 'y':
		return True
	if play.lower() == 'n':
		return False


main()


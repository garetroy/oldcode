import random


print('Hello! What is your name?')
user_name = str(input('>'))

print('Well, %s, I am thinking of a number between 1 and 20.' % user_name)
cpu_guess = random.randomint(1,20)
user_trys = 0
while user_trys < 6
	print('Take a guess.')
	user_guess = input('>')

	if user_guess < cpu_guess:
		print('You guess is too high.')
		user_guess += 1

	if user_guess > cpu_guess:
		print('your guess is too low')
		user_guess += 1

	if user_guess == cpu_guess:
		print('Good job, %s! You guessed my number in 3 guesses!' % user_name)
		break

if user_trys == 6:
	print('Nope. The number I was thinking of was %i' % cpu_guess)


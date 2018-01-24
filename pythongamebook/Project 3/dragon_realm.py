import time
import random
import os

def displayIntro():
	print('You are in a land full of dragons. In front of you,')
	print('you see two caves. In one cave, the dragon is friendly')
	print('and will share his treasure with you. The other dragon')
	print('is greedy and hungry, and will eat you on sight.')
	print()
	input('Push any button to continue...')

def chooseCave():
	cave = ''
	while cave != '1' and cave != '2':
		print('Which cave will you go into? (1 or 2)')
		cave = input('>')
	return cave

def checkCave(choice):
	print('You approach the cave...')
	time.sleep(2)
	print('It is dark and spooky...')
	time.sleep(2)
	print('A large dragon jumps out in front of you! He opens his jaws and...')
	print()
	time.sleep(2)

	good_cave = random.randint(1,2)
	if good_cave == int(choice):
		print('Gives you his treause!')
		input('Push any button to continue....')
	if good_cave != int(choice):
		print('Gobbles you down in one bite!')
		input('Push any button to continue....')


def playagain():
	print('Do you want to play?')
	playagain1 = input('>')
	if playagain1 == True:
		playagain1 = True
	else:
		playagain1 = False

os.system('clear')
playagain1 = True
while playagain:
	os.system('clear')
	displayIntro()
	os.system('clear')
	cave = chooseCave()
	os.system('clear')
	checkCave(cave)
	os.system('clear')
	playagain()


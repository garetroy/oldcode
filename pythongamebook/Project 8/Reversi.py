import random
from os import system
import sys

def main():
	csym = 'X'
	usym = 'O'
	upoints = 0 
	cpoints = 0
	cturn = random.randint(0,1)
	uturn = 0
	if cturn == 0:
		uturn = 1
	board = []
	for i in range(8):
		board.append([' '] * 8)
	board[3][3] = 'O'
	board[4][4] = 'O'
	board[3][4] = 'X'
	board[4][3] = 'X'
	print('Welcome to reversi!')
	print('Do you want to be X or O?')
	usym = input('>').upper()
	if usym == 'X':
		csym = 'O'
	elif usym != 'O':
		print('Come back when you want to be serious')
		return
	while True:
		upoints,cpoints = points(usym,csym,board,upoints,cpoints)
		if cturn == 0:
			computerturn(csym,board)
			playerturn(usym,board,upoints,cpoints)
			if hasmoves(board):
				pass
			else:
				return False
		else:
			playerturn(usym,board,upoints,cpoints)
			computerturn(csym,board)
			if hasmoves(board):
				pass
			else:
				return False
	system('clear')
	drawboard(board)
	whowon(upoints,cpoints)
	playagain()


def drawboard(board):
	hline ='  +---+---+---+---+---+---+---+---+'
	vline ='  |   |   |   |   |   |   |   |   |'
	print('    1   2   3   4   5   6   7   8')
	print(hline)
	for y in range(8):
		print(vline)
		print(y+1, end=' ')
		for x in range(8):
			print('| %s' % (board[x][y]), end=' ')
		print('|')
		print(vline)
		print(hline)

def playerturn(usym,board,upoints,cpoints):
	while True:
		system('clear')
		print('You have ' + str(upoints) + ' points. The computer has ' + str(cpoints) + ' points.')
		print('Enter your move(two digit integer), or type quit to end the game, or hints to turn off/on hints.')
		drawboard(board)
		move = input('>')
		if len(move) == 2:
			if int(move) > 88 or int(move) < 11:
				print('Not an correct value entered')
				input('Press enter to continue...')
			elif checkmove(usym,move,board):
				board = makemove(board,usym,move)
				return False
			else:
				print('Not an possible move.')
				input('Press enter to continue...')
		elif move.lower() == 'quit':
			print('Thanks for playing young grasshopper...')
			input('Press enter to exit....')
			system('clear')
			sys.exit()
		elif move.lower() == 'hints':
			hints(usym,board)
		else:
			print('Not an correct value entered')
			input('Press enter to continue...')

def checkmove(sym,move,board):
	check = 0
	xmove = int(move[0]) - 1
	ymove = int(move[1]) - 1
	#check if one in the same x axis ( left and right)
	return True


	#check if one in the same y axis
	#check if it is in diagonal axis

def makemove(board,sym,move):
	#add X to the board
	board[int(move[0]) - 1][int(move[1]) - 1] = sym
	return board
	#check for O's to turn into X's on horizontal, diagnal, verticle
	
def hints(usym,board):
	pass

def hasmoves(board):
	return True

def computerturn(csym,board):
	pass

def points(usym,csym,board,upoints,cpoints):
	cpoints = 0
	upoints = 0
	for i in board:
		for w in i:
			if w == usym:
				upoints += 1
			elif w == csym:
				cpoints += 1
			elif w == ' ':
				pass
	return upoints,cpoints

def whowon(upoints,cpoints):
	if upoints > cpoints:
		print('You won! Congratulations! You: ' + upoints + ' Computer: ' + cpoints)

def playagain():
	pass

main()
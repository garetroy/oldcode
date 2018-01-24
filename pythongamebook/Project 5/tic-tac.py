from random import randint
from os import system


board = [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ']
player_symbol = ''
computer_symbol = ''


def __init__():
    play = True
    global computer_symbol
    global player_symbol
    system('clear')
    print('Do you want to play?')
    temp = input('>')
    if temp.lower() == 'yes':
        temp = 'y'
    if temp.lower() == 'no':
        temp = 'n'
    if temp.lower() == 'y':
        play = True
        player_symbol = user_symbols()
        who_first = player_first()
        if player_symbol == 'o':
            computer_symbol = 'x'
        else:
            computer_symbol = 'o'
    if temp.lower() == 'n':
        play = False
    while play:
        if ' ' in board:
            if who_first:
                system('clear')
                computer_turn()
                draw_board()
                player_turn()
            elif not who_first:
                system('clear')
                draw_board()
                player_turn()
                computer_turn()
        else:
            print('Cats game!!')
            input('Press Enter to Continue....')
            for i in range(len(board)):
                board[i] = ' '
            __init__()


def user_symbols():
    system('clear')
    print("Do you want to be x's or o's?")
    player_symbol_now = input('>')
    player_symbol_now = player_symbol_now.lower()
    if player_symbol_now != 'o' and player_symbol_now != 'x':
        user_symbols()
    elif player_symbol_now == 'x':
        return 'x'
    elif player_symbol_now == 'o':
        return 'o'
    system('clear')


def draw_board():
    print('   |   |   ')
    print(' ' + board[0] + ' | ' + board[1] + ' | ' + board[2])
    print('   |   |   ')
    print('-----------')
    print('   |   |   ')
    print(' ' + board[3] + ' | ' + board[4] + ' | ' + board[5])
    print('   |   |   ')
    print('-----------')
    print('   |   |   ')
    print(' ' + board[6] + ' | ' + board[7] + ' | ' + board[8])
    print('   |   |   ')


def check_win():
    if board[0] == board[1] and board[1] == board[2] and board[0] != ' ':
        return True
    elif board[3] == board[4] and board[4] == board[5] and board[3] != ' ':
        return True
    elif board[6] == board[7] and board[7] == board[8] and board[6] != ' ':
        return True
    elif board[0] == board[3] and board[3] == board[6] and board[0] != ' ':
        return True
    elif board[1] == board[4] and board[4] == board[7] and board[1] != ' ':
        return True
    elif board[2] == board[5] and board[5] == board[8] and board[2] != ' ':
        return True
    elif board[0] == board[4] and board[4] == board[8] and board[0] != ' ':
        return True
    elif board[2] == board[4] and board[4] == board[6] and board[2] != ' ':
        return True
    else:
        return False


def player_first():
    number = randint(0, 1)
    if number == 0:
        print('You are First!')
        input('Press Enter to Continue....')
        return False
    if number == 1:
        print('The Computer is First!')
        input('Press Enter to Continue....')
        return True


def player_turn():
    print("It's your turn, choose a spot where you want to go (1-9)")
    spot = input('>')
    spot = int(spot)
    if spot > 9 or spot < 1:
        print("Please pick a valid number between 1-9")
        input('Press Enter to Continue....')
        system('clear')
        draw_board()
        player_turn()
    spot -= 1
    if board[spot] == player_symbol or board[spot] == computer_symbol:
        print('That spot is already taken, try again')
        input('Press Enter to Continue....')
        system('clear')
        draw_board()
        player_turn()
    elif board[spot] == ' ':
        board[spot] = player_symbol
        system('clear')
        if check_win():
            draw_board()
            print('You just won!')
            input('Press Enter to Continue....')
            for i in range(len(board)):
                board[i] = ' '
            __init__()
        else:
            pass


def computer_turn():
    for i in range(0, 8):
        if board[i] == ' ':
            board[i] = computer_symbol
            if check_win():
                system('clear')
                draw_board()
                print('The computer won!')
                input('Press Enter to Continue....')
                for w in range(len(board)):
                    board[w] = ' '
                __init__()
            else:
                board[i] = player_symbol
                if check_win():
                    system('clear')
                    board[i] = computer_symbol
                    return
                else:
                    board[i] = ' '

    if board[0] == ' ' or board[2] == ' ' or board[6] == ' ' or board[8] == ' ':
        check_corners()
        return
    elif board[4] == ' ':
        board[4] = computer_symbol
        return
    else:
        side_rand = randint(0, 3)
        if side_rand == 0 and board[1] == ' ':
            board[1] = computer_symbol
        if side_rand == 1 and board[3] == ' ':
            board[3] = computer_symbol
        if side_rand == 2 and board[5] == ' ':
            board[5] = computer_symbol
        if side_rand == 3 and board[7] == ' ':
            board[7] = computer_symbol
        return


def check_corners():
    corner_rand = randint(0, 3)
    if board[0] == ' ' and corner_rand == 0:
        board[0] = computer_symbol
    elif board[2] == ' ' and corner_rand == 1:
        board[2] = computer_symbol
    elif board[6] == ' ' and corner_rand == 2:
        board[6] = computer_symbol
    elif board[8] == ' ' and corner_rand == 3:
        board[8] = computer_symbol




__init__()
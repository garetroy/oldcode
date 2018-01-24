key = 0
alphabet = 'abcdefghijklmnopqrstuvwxyz'

def main():
	print('Do you wish to encrypt or decrypt a message?')
	eord = input('>')
	eord.lower()
	if eord == 'encrypt':
		encrypt()
	elif eord == 'decrypt':
		decrypt()


def encrypt():
	print("Enter your message:")
	message = input('>')
	keys()
	message = make_list(message)
	for i in range(len(message)):
		if message[i] not in alphabet:
			pass
		else:
			indexnum = alphabet.index(message[i])
			total = key - indexnum
			message[i] = alphabet[total]
	print(''.join(message))

def decrypt():
	print("Enter your message:")
	message = input('>')
	keys()
	message = make_list(message)
	for i in range(len(message)):
		if message[i] not in alphabet:
			pass
		else:
			indexnum = alphabet.index(message[i])
			total = key - indexnum
			message[i] = alphabet[total]
	print(''.join(message))


def keys():
	global key
	print('Enter Key Number (1-26)')
	key = int(input('>'))

def make_list(message):
	listt = []
	for i in message:
		listt.append(i)
	return listt

main()
import pickle


filez = open('p.p', 'rb')
filez2 = pickle.load(filez)
filez.close()
for line in filez2:
    print(''.join(c * n for c, n in line))
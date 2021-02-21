import random
import sys

x=1
text="E' uscito il numero {}"

while x==1:
    x=int(input(("Premere 1 per tirare il dado, 0 per uscire dal programma.")))
    if x==1: print(text.format(random.randrange(1,6)))
    elif x==0: sys.exit()
    else: print("ERRORE NELL'INSERIMENTO")


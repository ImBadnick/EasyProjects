import random
import sys

x=random.randrange(0,100)

print("Range:0-100")
chosen=int(input("Indovina il numero: "))

if chosen==x:
    print("HAI VINTO!")
    sys.exit()
elif chosen>x: print("Numero troppo grande")
else: print("Numero troppo piccolo")

while chosen!=x:
    chosen=int(input("Indovina il numero: "))
    if chosen==x: 
        print("HAI VINTO!")
        break
    elif chosen>x: print("Numero troppo grande")
    else: print("Numero troppo piccolo")

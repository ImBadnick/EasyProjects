import DiceRolling as dr
import numpy as ny
from scipy import stats

times=int(input("Quante volte vuoi lanciare il dado?: "))

values=[]
for x in range(times):
    values.append(dr.dice())

print("Values:",values)
print("AvarangeValue:",ny.mean(values))
print("MostTimeValue:",int(stats.mode(values).mode))

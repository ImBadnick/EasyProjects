import BinarySearchALG as bs

nums=input("Quanti valori vuoi inserire(Ordine Crescente): ")
values=[]
for x in range(int(nums)):
    newvalue=input("Valore:")
    values.append(int(newvalue))

search=input("Quale numero vuoi cercare?: ")
print(bs.binarysearch(values,0,len(values)-1,int(search)))

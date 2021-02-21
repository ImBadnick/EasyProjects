def binarysearch(values,sx,dx,x):
    if sx>dx:
        return False
    if x<values[sx] or x>values[dx]:
        return False
    cx=int((sx+dx)/2)
    if values[cx]==x:
        return True
    elif values[cx]>x:
        return binarysearch(values,sx,cx-1,x)
    else:
        return binarysearch(values,cx+1,dx,x)



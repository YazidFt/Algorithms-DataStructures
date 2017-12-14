def gcd(a,b):
    if(b==0):
        return a
    else:
        return gcd(b,a%b)



n = int(input())
a = [2,3,11,13]
res=0
for i in range(1,(1<<4)):
    cnt=0
    p=1
    for j in range(4):
        if(i & (1<<j)):
            cnt+=1
            p*=a[j]

    if(cnt%2==0):
        res-= n//p
    else:
        res+= n//p

#Results
g = gcd(n,res)
print(res//g,end=" ")
print(n//g)








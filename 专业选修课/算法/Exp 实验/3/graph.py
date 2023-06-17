import matplotlib.pyplot as plt
s = input()
s = s.split(' ')
pointlength = eval(s[0])
edgelength = eval(s[1])
arr0 = []
arr1 = []
arr2 = []
for x in range(pointlength):
    st = input()
    st = st.split(' ')
    t = 0
    while st[t]=="":
        t = t+1
    arr0.append(eval(st[t]))
    t = t+1
    while st[t]=="":
        t = t+1
    arr1.append(eval(st[t]))
    t = t+1
    while st[t]=="":
        t = t+1
    arr2.append(eval(st[t]))
plt.plot(arr1,arr2,'ro')


for i in range(edgelength):
    s1 = input()
    s1 = s1.split(' ')
    t = 0
    while s1[t]=="":
        t = t+1
    x1 = arr1[eval(s1[t])]
    y1 = arr2[eval(s1[t])]
    t = t+1
    while s1[t]=="":
        t = t+1
    x2 = arr1[eval(s1[t])]
    y2 = arr2[eval(s1[t])]
    plt.plot([x1,x2],[y1,y2],color = 'black')
s = input()
ar1 = []
ar2 = []
while s!="q":
    s = s.split("->")
    t = 0
    while s[t]=="":
        t = t+1
    x1 = arr1[eval(s[t+0])]
    y1 = arr2[eval(s[t+0])]
    t =t +1
    while s[t]=="":
        t = t+1
    x2 = arr1[eval(s[t])]
    y2 = arr2[eval(s[t])]
    plt.plot([x1,x2],[y1,y2],color = 'blue')
    s = input()
plt.show()
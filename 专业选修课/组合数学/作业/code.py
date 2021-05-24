import math
import random
for i in range(1,11):
    a = math.factorial(7301)
    b = math.factorial(3343) * math.factorial(3958)
    c = a//b
    a = math.factorial(7301-i)*(7301-i+2)
    b = math.factorial(3343-i) * math.factorial(3958)
    d = a//b
    print(i,"\t" ,+ d/c)

rs = [[0 for col in range(100)] for row in range(10000)]
for J in range(100):
    hot_hand = J/100
    for i in range(100):
        hit_time = [0 for n in range(20)]
    shot_success = 0
    max_shot = 0
    for j in range(10000):
        p = 0.45
        r = random.random()
        if r<p:
            shot_success += 1
            if max_shot < shot_success:
                max_shot = shot_success
            p = p*(1+hot_hand)
        else:
            hit_time[shot_success] +=1;
            shot_success = 0
            p = 0.45
    for i in range(len(hit_time)):
        print("hit ",i,",",hit_time[i],"times whit hot hand", J)
        rs[J][i] = hit_time[i]
    print(max_shot)


考试范围

1. Algorithm analysis
2. Union-find
3. Sorting and Searching (BST)
4. Heap & Priority Queue
5. MST
6. Shortest Paths
7. String sorting
8. Algorithm Design

不涉及：suffix arrays，data compression, MSD(Most significant Digit first)



1. 考试试卷是英文的。考试试卷最后一页有“单词释义表”
2. 算法描述不限具体语言，可以是高级语言抽象描述
3. 内容涵盖上课讲述的内容
4. 要求中文作答



复习以作业为主(作业答案可以参照这个[仓库](https://github.com/reneargento/algorithms-sedgewick-wayne))，普林斯顿题库为辅



2021.1考试

1.Analysis of algorithms. 

(1)You observe the following running times for a program with an input of size N.

| N     | time   |
| ----- | ------ |
| 1000  | 0.1s   |
| 2000  | 0.3s   |
| 4000  | 2.5s   |
| 8000  | 19.8   |
| 16000 | 160.1s |

Estimate the running time of the program (in seconds) on an input of size N = 80, 000.

(2)

 1+2+3+4+...+N

 n^2/2

 n^3

 A.O(n^2)  B.~n^2/2  C. both a and b D. neither A or B

2.union-find, 画一个quick-union的过程图

3.sort，写mergesort heapsort lsd排序的过程

4.Dijkstra 跟题库里的fin-f12.pdf中第五题基本一样，数据变了一下

5.lazy-Prim算法，写过程

6.算法设计 ThreeSum 复杂度O（N^2）



整体难度远低于数据结构考试。考试只要掌握那几个算法：并查集 排序 最小生成树 最短路径。比较水的一门课，啥也没学到。我刚开始看的是英文橙书，感觉特别啰嗦，看完感觉啥也没学到。ppt写的要比课本好得多。这本书的优点也就在于 他给出了Java实现，但是他里面很多东西又要调 出书人自己写的包，不知道为啥不用Java自带的库。
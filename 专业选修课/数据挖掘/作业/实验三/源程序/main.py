import networkx
import numpy as np
import math
import matplotlib.pyplot as plt


def generateNetwork(k2):
    k1 = 16 - k2
    graph = np.eye(128)
    allNode = np.array(range(128))
    np.random.shuffle(allNode)
    groups = np.split(allNode, 4)
    for i in range(len(groups)):
        for node in groups[i]:
            ingroupNode = np.random.choice(np.delete(groups[i], groups[i] == node), k1, replace=False)
            outgroupNode = np.random.choice(np.delete(groups, i, axis=0).flatten(), k2, replace=False)
            graph[node, ingroupNode] = 1
            graph[node, outgroupNode] = 1

    return (Graph(graph), groups)


class Graph:
    G = np.array([])

    def __init__(self, graph: np.ndarray):
        self.G = graph

    def getNeighbor(self, i: int) -> list:
        """
        获取节点 i 所有的邻居节点
        :param i: 节点序号
        :return: list 所有邻居节点的序号
        """
        result = []
        for j in range(len(net.node)):
            if self.G[i][j] and i != j:
                result.append(j)
        return result

    def getSimilarity(self, i: int, j: int) -> float:
        """
        计算节点 i 和节点 j 的相似性
        :param i: 节点 i 序号
        :param j: 节点 j 序号
        :return: float 相似性
        """
        Ni = self.getNeighbor(i)
        Nj = self.getNeighbor(j)
        intersection = set(Ni).intersection(set(Nj))
        union = set(Ni).union(set(Nj))
        try:
            return len(intersection) / len(union)
        except Exception:
            return 0


class group:
    node = []
    neighbor = set()
    edgeNum = 0
    density = 0.0

    def __init__(self, node: list, graph):
        self.node = node
        self.graph = graph
        self.neighbor = set()
        for n in node:
            self.neighbor = self.neighbor.union(graph.getNeighbor(n))
        subgraph = graph.G[node][:, node]
        self.edgeNum = np.count_nonzero(subgraph)
        self.density = self.edgeNum / (len(self.node) * len(self.node))

    def tryAddNode(self, i):
        nodeNum = self.graph.G.shape[0]  # 获取社团节点个数
        addedge = 0
        for j in range(nodeNum):
            if self.graph.G[i][j] and j in self.node:
                addedge += 1
        return (self.edgeNum + addedge) / ((len(self.node) + 1) * (len(self.node) + 1))

    def addNode(self, i):
        self.node.append(i)
        subgraph = self.graph.G[self.node][:, self.node]
        self.edgeNum = np.count_nonzero(subgraph)
        self.neighbor.union(self.graph.getNeighbor(i))
        self.density = self.edgeNum / (len(self.node) * len(self.node))


def BDA(graph: Graph, treshold):
    """
    基于社团密度的社团发现算法
    :param graph: 社团网络
    :param treshold: 聚类社团密度阈值
    :return:
    """

    nodeNum = graph.G.shape[0]  # 获取社团节点个数
    isInGroup = np.zeros(len(graph.G), dtype=bool) #初始化未划分节点集为所有节点
    result = []

    while False in isInGroup: #判断是否有节点还未划分
        grouptestList = []  # 初始化候选社团集合
        for i in range(nodeNum):
            if not isInGroup[i]:
                iandNeighbor = [i]
                for j in graph.getNeighbor(i):
                    if not isInGroup[j]:
                        iandNeighbor.append(j)
                grouptestList.append(group(iandNeighbor, graph))
        grouptestList.sort(key=lambda x: x.density, reverse=True) #根据候选社团的密度进行排序

        groupselect = grouptestList[0]  #选取社团密度最大的社团作为预备社团
        isInGroup[groupselect.node] = True
        while groupselect.density >= treshold: #判断社团密度是否小于阈值
            max_density = 0
            max_node = 0
            for i in range(nodeNum):
                if i not in groupselect.node and not isInGroup[i]:
                    #分别将既不属于候选社团，又处于未划分集合的节点逐个尝试加入当前社团
                    trydensity = groupselect.tryAddNode(i)
                    if trydensity > max_density:
                        max_density = trydensity
                        max_node = i
            if max_density != 0:
                #寻找使得当前社团密度降低最小的节点加入当前社团
                groupselect.addNode(max_node)
                isInGroup[max_node] = True
            else:
                break
        result.append(groupselect) #将当前社团确定为正式社团加入结果集
    return result


def NMI(A, B):
    # len(A) should be equal to len(B)
    total = len(A)
    A_ids = set(A)
    B_ids = set(B)
    # Mutual information
    MI = 0
    eps = 1.4e-45
    for idA in A_ids:
        for idB in B_ids:
            idAOccur = np.where(A == idA)
            idBOccur = np.where(B == idB)
            idABOccur = np.intersect1d(idAOccur, idBOccur)
            px = 1.0 * len(idAOccur[0]) / total
            py = 1.0 * len(idBOccur[0]) / total
            pxy = 1.0 * len(idABOccur) / total
            MI = MI + pxy * math.log(pxy / (px * py) + eps, 2)
    # Normalized Mutual information
    Hx = 0
    for idA in A_ids:
        idAOccurCount = 1.0 * len(np.where(A == idA)[0])
        Hx = Hx - (idAOccurCount / total) * math.log(idAOccurCount / total + eps, 2)
    Hy = 0
    for idB in B_ids:
        idBOccurCount = 1.0 * len(np.where(B == idB)[0])
        Hy = Hy - (idBOccurCount / total) * math.log(idBOccurCount / total + eps, 2)
    MIhat = 2.0 * MI / (Hx + Hy)
    return MIhat

def testGraph():
    """
    测试聚类
    :return:
    """
    Ggraph, Ggroup = generateNetwork(2)
    rs = BDA(Ggraph, 0.45)
    mG = networkx.DiGraph()
    i = 1
    for group in rs:
        for n in group.node:
            mG.add_node(n)
            mG.nodes[n]['class'] = i
        i+=1

    for i in range(Ggraph.G.shape[0]):
        for j in range(Ggraph.G.shape[0]):
            if Ggraph.G[i][j]:
                mG.add_edge(i, j)

    networkx.write_gml(mG, 'my_group.gml', stringizer=lambda x: str(x))

if __name__ == '__main__':
    print("对跆拳道社团网络进行聚类...")
    net = networkx.read_gml('karate.gml', label='id')  # 读取网络社团数据
    networkx.draw(net, with_labels=True)
    plt.show()
    G = np.eye(len(net.node) + 1)  # 用全 0 初始化邻接矩阵
    SimilarityGraph = np.zeros((len(net.node) + 1, len(net.node) + 1))  # 用全 0 初始化相似度矩阵

    for e in net.edges:  # 对网络中的边进行遍历，邻接矩阵相应位置置1
        G[e[0]][e[1]] = 1
        G[e[1]][e[0]] = 1
    G = G[1:, 1:]
    karateGraph = Graph(G)
    """
    生成相似度矩阵
    """
    for i in range(len(net.node)):
        for j in range(len(net.node)):
            SimilarityGraph[i][j] = karateGraph.getSimilarity(i, j)
            SimilarityGraph[j][i] = SimilarityGraph[i][j]

    """
    计算聚类结果
    """
    rs = BDA(karateGraph, 0.27)
    print("聚类完成")

    print("网络共被分为 ",len(rs), " 个类")

    i = 1  #聚类完成，为每一个节点更新标签
    for g in rs:
        for n in g.node:
            net.nodes[n+1]['class'] = i
            print(n + 1, end=" "),
        print("\n")
        i+=1

    color = [net.nodes[i+1]['class'] for i in range(len(net.node))] #设定节点的颜色

    networkx.draw(net, with_labels=True, node_color=color)
    plt.show()

    networkx.write_gml(net, 'karate_group.gml')

    print("")

    """
    模拟数据
    """
    testGraph()
    for k2 in [2,4,6,8]:
        x = []
        y = []
        for I in range(50):
            Ggraph, Ggroup = generateNetwork(k2)
            rs = BDA(Ggraph, 0.15 + I * 0.5 / 50)
            nmia = []
            for g in range(len(rs)):
                for i in rs[g].node:
                    nmia.append(g)
            nmib = []
            for g in range(len(rs)):
                for n in rs[g].node:
                    for j in range(4):
                        if n in Ggroup[j]:
                            nmib.append(j)
            print(0.15 + I * 0.5 / 50.0, " ", NMI(np.array(nmia), np.array(nmib)))
            x.append(0.15 + I * 0.5 / 50.0)
            y.append(NMI(np.array(nmia), np.array(nmib)))

        plt.plot(x, y, label=f"k2: {k2}")

    plt.title('The clustering accuracy under different threshold')
    plt.xlabel('threshold')
    plt.ylabel('NMI')

    plt.legend(loc = 'best')
    plt.grid()
    plt.show()

    Ggraph, Ggroup = generateNetwork(4)

    rs = BDA(Ggraph, 0.23)
    print("Group Num is ", len(rs))
    nmia = []
    for g in range(len(rs)):
        for i in rs[g].node:
            nmia.append(g)
    nmib = []
    for g in range(len(rs)):
        for n in rs[g].node:
            for i in range(4):
                if n in Ggroup[i]:
                    nmib.append(i)
    print(NMI(np.array(nmia), np.array(nmib)))

    for g in rs:
        for n in g.node:
            for i in range(4):
                if n in Ggroup[i]:
                    print(i, end=" ")
        print("\n")



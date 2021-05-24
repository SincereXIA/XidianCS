import csv
import numpy as np
import matplotlib.pyplot as plt

MOVIESNUM = 9744
MOVIESMAXID = 193610
USERNUM = 611

binaryNet = np.zeros((MOVIESNUM, USERNUM), dtype=int)
kj = np.zeros(MOVIESNUM, dtype=int)
kl = np.zeros(USERNUM, dtype=int)
url2id = np.empty(MOVIESMAXID, dtype=int)
id2url = np.empty(MOVIESNUM, dtype=int)
unlike = []


def ReadDataSet():
    """
    读取数据集
    :return:
    """
    with open('movies.csv', 'r', encoding='UTF-8') as csvfile:
        # 读取 movies 文件，为每个电影重新分配其 id 值
        reader = csv.reader(csvfile)
        id = 0
        for row in reader:
            try:
                url = int(row[0])
                id2url[id] = url
                url2id[url] = id
                id += 1
            except Exception as e:
                print(e)

    with open('ratings.csv') as csvfile:
        # 读取用户评分表
        reader = csv.reader(csvfile)
        for row in reader:
            try:
                i = int(row[0])
                j = url2id[int(row[1])]
                if int(float(row[2])) > 3:  # 为打分超过三分的电影添加二部图中的边
                    binaryNet[j][i] = 1
                else:
                    unlike.append((i, j))
                    # 打分小于三分的电影视作用户不喜欢的电影，将其记录，用于 ROC曲线绘制
            except Exception as e:
                print(e)
    print("数据读取完毕")


def ResourcesQuota(train_set):
    """
    计算资源配额矩阵
    :param train_set: 训练集
    :return: W 资源配额矩阵
    """
    kl = np.count_nonzero(train_set, axis=0)  # 计算有多少用户
    kj = np.count_nonzero(train_set, axis=1)  # 计算有多少电影

    temp = np.true_divide(train_set, kl)
    temp[np.isnan(temp)] = 0  # 计算过程中会产生 nan 元素，将其置为 0
    temp2 = np.true_divide(temp.T, kj).T
    temp2[np.isnan(temp2)] = 0  # 计算过程中会产生 nan 元素，将其置为 0
    W = np.dot(train_set, temp2.T)  # 完成资源配额矩阵的计算
    print("资源配额矩阵 W 计算完毕")
    return W


def recommend(W, f):
    return np.dot(W, f)


def getTrainSetandTestSet():
    """
    划分训练集和测试集
    :return:
    """
    # pos记录二部图的边，即对应邻接矩阵元素为 1 的位置
    pos = np.where(binaryNet == 1)
    # 随机选取二部图中边的 10%
    testpos = np.random.choice(len(pos[0]), int(len(pos[0]) * 0.1))
    tp = ([], [])
    # 取得测试集的元素位置
    for i in testpos:
        tp[0].append(pos[0][i])
        tp[1].append(pos[1][i])
    TrainSet = np.copy(binaryNet)
    # 将邻接矩阵这些位置的元素置为 0
    TrainSet[tp] = 0
    return TrainSet, list(zip(tp[1], tp[0]))


def getAccuracy(W, train, test):
    """
    计算精确度 （测试数据集中数据在预测结果中的相对位置）绘制 ROC 曲线
    返回值越小，效果越好

    :param W: 计算资源配额矩阵
    :param test: 测试集
    :return:
    """

    pos = np.zeros((USERNUM, MOVIESNUM))  # 存储预测结果 pos[i][j] 表示 用户 i 对电影 j 的预测喜好排名
    mark = np.zeros((USERNUM, MOVIESNUM))  # 存储预测结果 mark[i][j] 表示 用户 i 对电影 j 的预测打分

    print("对所有用户进行预测排名中，时间较长...")
    # 对每个用户分别预测
    for i in range(USERNUM):
        r = recommend(W, train[:, i])
        reslut = zip(r, range(len(r)))
        reslut = sorted(reslut, reverse=True)
        # 对结果完成排序
        j = 0
        for r in reslut:
            k, v = r
            pos[i, v] = j  # 存储排序值
            mark[i, v] = k
            j += 1
        print(f'user:{i}, Finish Recommend')

    r = 0
    kl = np.count_nonzero(train, axis=0)
    kj = np.count_nonzero(train, axis=1)
    for t in test:
        r += pos[t[0]][t[1]] / (MOVIESNUM - kl[t[0]])
        print(f'Test Set: (user {t[0]}, movie {t[1]}), Rank: {pos[t[0]][t[1]]}, UserUnSelectNum: {MOVIESNUM-kl[t[0]]}')
    print("平均 r 为：", r / len(test))

    print("选取不同阈值计算 ROC 曲线...")
    x = []
    y = []
    for i in range(100):
        TP = 0
        FP = 0
        FN = 0
        TN = 0
        for t in test:
            if pos[t[0]][t[1]] / (MOVIESNUM - kl[t[0]]) < i / 100:
                # 相对位置在前 百分之i 的电影为推荐电影
                TP += 1
            else:
                FN += 1
        for t in unlike:
            # unlike 集里面是用户不喜欢的电影
            if pos[t[0]][t[1]] / (MOVIESNUM - kl[t[0]]) > i / 100:
                TN += 1
            else:
                FP += 1
        print(np.array([[TP, FN], [FP, TN]]))
        TPR = TP / (TP + FN)
        FPR = FP / (FP + TN)
        print(f"TPR: {TPR},  FPR: {FPR}")
        # 对不同阈值下的 TPR 和 FPR 进行记录
        x.append(FPR)
        y.append(TPR)

    # 使用 plt 库完成图像绘制
    plt.title('ROC')
    plt.xlabel('FPR')
    plt.ylabel('TPR')

    plt.plot(x, y, 'r', label='roc')

    plt.legend(bbox_to_anchor=[0.3, 1])
    plt.grid()
    plt.show()

    x1 = []
    y1 = []
    for i in range(100):
        TP = 0
        FP = 0
        FN = 0
        TN = 0
        for t in test:
            if mark[t[0]][t[1]] > 0.3 * i / 100:
                TP += 1
            else:
                FN += 1
        for t in unlike:
            if mark[t[0]][t[1]] < 0.3 * i / 100:
                TN += 1
            else:
                FP += 1
        print(np.array([[TP, FN], [FP, TN]]))
        TPR = TP / (TP + FN)
        FPR = FP / (FP + TN)
        print(f"TPR: {TPR},  FPR: {FPR}")
        x1.append(FPR)
        y1.append(TPR)

    plt.title('ROC')
    plt.xlabel('FPR')
    plt.ylabel('TPR')

    plt.plot(x1, y1, 'r', label='roc')

    plt.legend(bbox_to_anchor=[0.3, 1])
    plt.grid()
    plt.show()

    return r / len(test)


if __name__ == '__main__':
    ReadDataSet()  # 读取数据集
    train, test = getTrainSetandTestSet()  # 划分测试集和训练集
    W = ResourcesQuota(train)  # 计算资源矩阵 W
    r = getAccuracy(W, train, test)  # 推荐和推荐结果评价
    print(r)

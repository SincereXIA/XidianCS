import pandas as pd
import numpy as np

df = pd.read_excel('成绩关系型数据集.xlsx')
df = df.drop(df.index[-1])
df.drop(columns=['姓名'], inplace=True)
#df.drop(columns=['性别'], inplace=True)
#df['姓名']="*"
df['性别']="*"
df['平均成绩']=df['平均成绩'].round().astype(int)

n = 3  # 将范围分成n段
def divide_range(n):
    start = 60
    end = 101
    range_length = end - start
    segment_length = range_length // n
    remainder = range_length % n
    segments = []

    for i in range(n):

        if remainder > 0:
            segment_end = start + segment_length + 1
            remainder -= 1
        else:
            segment_end = start + segment_length
        segments.append((start, segment_end))
        start = segment_end

    return segments

# 对成绩进行阶梯处理
def discretize_score(score):

    segments = divide_range(n)
    for segment in segments:
        if score>=int(segment[0]) and score <=int(segment[1] - 1):
            return f"{segment[0]}~{segment[1] - 1}"

for subject in ['语文成绩', '数学成绩', '外语成绩']:
    df[subject] = df[subject].apply(discretize_score)

df.rename(columns={
    '语文成绩': '成绩1',
    '数学成绩': '成绩2',
    '外语成绩': '成绩3'
}, inplace=True)

df.to_excel('匿名成绩数据2.xlsx', index=False)

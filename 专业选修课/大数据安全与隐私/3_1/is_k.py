import pandas as pd
from collections import Counter

file_path = '匿名成绩数据.xlsx'
df = pd.read_excel(file_path)
unique_row_counts = Counter(tuple(row) for _, row in df[['性别','语文成绩', '数学成绩', '外语成绩']].iterrows())

#计算每行的唯一性及其出现次数
print("每行（三门成绩的组合）的出现次数:")
for row, count in unique_row_counts.items():
    print(f"{row}: {count}")
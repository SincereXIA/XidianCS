import pandas as pd
from collections import Counter

file_path = '匿名成绩数据2.xlsx'
df = pd.read_excel(file_path)

# 先对成绩进行排序，然后再转换为元组（如果不考虑顺序的话）
df_sorted = df[['性别', '成绩1', '成绩2', '成绩3']].copy()
df_sorted[['成绩1', '成绩2', '成绩3']] = df_sorted[['成绩1', '成绩2', '成绩3']].apply(
    lambda x: sorted(x), axis=1, result_type='expand')

# 计算每行的唯一性及其出现次数
unique_row_counts = Counter(tuple(row) for _, row in df_sorted.iterrows())

print("每行（三门成绩的组合）的出现次数:")
for row, count in unique_row_counts.items():
    print(f"{row}: {count}")
import numpy as np

class OPE:
    def __init__(self, plaintext_range=(0, 100), ciphertext_range=(1000, 2000)):
        self.plaintext_range = plaintext_range
        self.ciphertext_range = ciphertext_range
        self.slope = (ciphertext_range[1] - ciphertext_range[0]) / (plaintext_range[1] - plaintext_range[0])

    def encrypt(self, plaintext):
        return self.ciphertext_range[0] + self.slope * (plaintext - self.plaintext_range[0])

    def decrypt(self, ciphertext):
        return self.plaintext_range[0] + (ciphertext - self.ciphertext_range[0]) / self.slope

size = input('输入数据集大小:')
data = np.random.randint(0, 100, size=int(size))
print("原始数据: ", data)

ope = OPE()
encrypted_data = [ope.encrypt(i) for i in data]
print("加密后的数据: ", encrypted_data)

def range_query(encrypted_data, low, high):
    return [i for i in encrypted_data if low <= ope.decrypt(i) <= high]

low = input('输入查询最小值：')
high = input('输入查询最大值：')
print("范围查询结果: ", range_query(encrypted_data, int(low), int(high)))

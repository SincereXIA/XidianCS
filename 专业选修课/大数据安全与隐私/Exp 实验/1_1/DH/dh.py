import random
from sympy import isprime

def generate_prime():
    while True:
        prime_candidate = random.randint(10**5, 10**6)
        if isprime(prime_candidate):
            return prime_candidate

# 随机生成大素数p和g
p = generate_prime()
g = generate_prime()

# 生成私钥a和公钥A
a = random.randint(1, p)
A = (g ** a) % p

# 生成私钥b和公钥B
b = random.randint(1, p)
B = (g ** b) % p

session_key_a = (B ** a) % p
session_key_b = (A ** b) % p

def encrypt_decrypt(message, key):
    return ''.join(chr(ord(c) ^ key) for c in message)

message = input('输入密文：')
encrypted_message = encrypt_decrypt(message, session_key_a)
decrypted_message = encrypt_decrypt(encrypted_message, session_key_b)

print(f"原始消息: {message}")
print(f"加密后的消息: {encrypted_message}")
print(f"解密后的消息: {decrypted_message}")

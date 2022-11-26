# Study: https://cs.stackexchange.com/questions/10318/the-math-behind-converting-from-any-base-to-any-base-without-going-through-base

# Convert a positive number n to its digit representation in base b.
def toDigits(n, b):
    digits = []
    while n > 0:
        digits.insert(0, n % b)
        n  = n // b
    return digits

# Compute the number given by digits in base b.
def fromDigits(digits, b):
    n = 0
    for d in digits:
        n = b * n + d
    return n

# toDigits(42, 2)
# [1, 0, 1, 0, 1, 0]

# toDigits(42, 3)
# [1, 1, 2, 0]

# fromDigits([1,1,2,0], 3)
# 42

# Convert the digits representation of a number from base b to base c.
def convertBase(digits, b, c):
    return toDigits(fromDigits(digits, b), c)

# print(convertBase([1,1,2,0], 3, 2))
# [1, 0, 1, 0, 1, 0]

# print(toDigits(42, 2))
# [1, 0, 1, 0, 1, 0]

print(toDigits(1100, 60))
print(toDigits(1100, 4))

# list = ["a", "b", "c"]
# list.insert(0, "d")
# list.insert(3, "e")
# list.insert(0, "x")
# print(list)

# print(1100 % 60)
# print(1100 // 60)
# print(18 % 60)

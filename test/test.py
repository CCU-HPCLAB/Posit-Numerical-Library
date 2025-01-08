import libpositWrapperPy as posit
import numpy as np

print("posit(64, 0)")

rawBit = posit.getRawBit_64_0(1e+307)
print(bin(rawBit))

doubleVal = posit.getDouble_64_0(rawBit)
print(doubleVal)

print("posit(64, 1)")

rawBit = posit.getRawBit_64_1(1e+307)
print(bin(rawBit))

doubleVal = posit.getDouble_64_1(rawBit)
print(doubleVal)

print("posit(64, 2)")

rawBit = posit.getRawBit_64_2(1e+307)
print(bin(rawBit))

doubleVal = posit.getDouble_64_2(rawBit)
print(doubleVal)

print("posit(64, 3)")

rawBit = posit.getRawBit_64_3(1e+307)
print(bin(rawBit))

doubleVal = posit.getDouble_64_3(rawBit)
print(doubleVal)

print("posit(8, 2)")

rawBit = posit.getRawBit_8_2(3.14)
print(bin(rawBit))

doubleVal = posit.getDouble_8_2(rawBit)
print(doubleVal)

# binary to i8
rawBit = 0b11000000
doubleVal = posit.getDouble_8_2(rawBit)

# binary to i32
rawBit = 0b11000000110000001100000011000000
doubleVal = posit.getDouble_32_2(rawBit)
print(doubleVal)

# test getDoubleArray_8_2

array = np.array([[1, 2, 4, 8, -32], [1, 2, 4, 8, -255]], dtype=np.int8)
doubleArray = posit.getDoubleArray_8_2(array)
print(doubleArray)
array = posit.getRawBitArray_8_2(doubleArray)
print(array)

# test getRawBitArray_8_2

array = np.array([[2.4, 4, 8, -6.9, -11111111111111.111111111111111111],
                 [2.4, 4, 8, -6.9, 11111111111111.111111111111111111]], dtype=np.float32)
print(array)
doubleArray = posit.getRawBitArray_8_2(array)
print(doubleArray)
rawBitArray = posit.getDoubleArray_8_2(doubleArray)
print(rawBitArray)
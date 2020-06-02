import numpy as np
import ctypes
import cv2

#载入dll文件的路径
test = ctypes.cdll.LoadLibrary("..\\x64\\Release\\dll2py.dll")
#读入图片
frame = cv2.imread('..\\circle.png')
#将opencv的mat数据类型转换为char*的数据格式
frame_data = np.asarray(frame, dtype=np.uint8)
frame_data = frame_data.ctypes.data_as(ctypes.c_char_p)
#定义输出数据格式（此处似乎有一个bug，即x64框架下仅支持uint64格式，其他格式会报错）
test.py2cpp.restype = ctypes.c_uint64
test.lenght.restype = ctypes.c_uint64
#调用dll的接口函数
buf = test.py2cpp(frame.shape[0], frame.shape[1], frame_data)
mlenght = test.lenght()
#打印返回值的指针首地址
print('地址值：')
print('%#x'%buf)
#打印返回框的个数
print('框个数：')
print(mlenght)
#数据解析：返回的指针是short类型（16位），但返回地址是按照8位存储的（此处实际上是存储的二进制数据，但是是以ASCII码形式存储的，因此仅能一次性存储8位）。我们的16位返回数据，是被拆解为高8位和低8位分别存储的，且先读出来的是低位，厚度出来的是高位，按照这一原则进行数据拼接。
bit_typr = 4*2
for num in range(0, mlenght):#框的个数循环
    #x数据解析，先读低8位，后读高8位
    L8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr, 1), byteorder='big', signed=False)
    H8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 1, 1), byteorder='big', signed=False)
    x = H8 << 8
    x = x + L8
    #y数据解析，先读低8位，后读高8位
    L8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 2, 1), byteorder='big', signed=False)
    H8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 3, 1), byteorder='big', signed=False)
    y = H8 << 8
    y = y + L8
    #w数据解析，先读低8位，后读高8位
    L8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 4, 1), byteorder='big', signed=False)
    H8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 5, 1), byteorder='big', signed=False)
    w = H8 << 8
    w = w + L8
    #h数据解析，先读低8位，后读高8位
    L8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 6, 1), byteorder='big', signed=False)
    H8 = int.from_bytes(ctypes.string_at(buf + num * bit_typr + 7, 1), byteorder='big', signed=False)
    h = H8 << 8
    h = h + L8
    print(x, y, w, h)
    cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 1, 8)

cv2.namedWindow('src', cv2.WINDOW_AUTOSIZE)
cv2.imshow('src', frame)
cv2.waitKey(0)
cv2.destroyAllWindows()

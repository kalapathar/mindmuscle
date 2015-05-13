import mindwave
import socket   #for sockets
import sys  #for exit
import time

headset = 0;

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = '127.0.0.1';
port = 1442;

s.sendto(b'idle', (host, port))



def init_connect():
	global headset;
	headset = mindwave.Headset('/dev/ttyUSB0')
	#print("Initial connect",headset)

def attempt_connect():
	global headset;
	if(headset != 0):
		headset.connect();
		#print("Connect")
	else:
		print("Not connected")

def get_status():
	global headset;
	if(headset != 0):
		return headset.status;
	else:
		print("Not connected")
		return "None"
	

def get_focus():
	global headset;

	if(headset != 0):
		if(headset.poor_signal > 10):
			return 0;
		return headset.attention;
	else:
		return -1;

def disconnect():
	global headset;
	if(headset != 0):
		#print("Disconnecting")
		headset.disconnect()
	else:
		print("Not connected")

die = False;

while(True):
	d = s.recvfrom(1024)
	data = d[0]
	print("Receive",data)

	if(data == "idle"):
		#Don't do anything
		s.sendto(b'idle', (host, port))
	if(data == "init_connect"):
		init_connect();
		s.sendto(b'initialized_connection', (host, port))
	if(data == "attempt_connect"):
		attempt_connect();
		s.sendto(b'attempted_connect', (host, port))
	if(data == "get_status"):
		st = get_status();
		status = "status" + str(st);
		bites = bytes(status)
		s.sendto(bites, (host, port))
	if(data == "get_focus"):
		f = get_focus();
		focus = "focus" + str(f);
		bites = bytes(focus)
		s.sendto(bites, (host, port))
	if(data == "disconnect"):
		disconnect();
		s.sendto(b'disconnecting', (host, port))
		die = True;

	time.sleep(0.2);
	if(die):
		break

print("python dead")
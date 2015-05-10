import mindwave, time

headset = 0;
#states = {'None':-1,'standby':0,'scanning':1,'connected':2}

def init_connect():
	global headset;
	headset = mindwave.Headset('/dev/ttyUSB0')
	print("Initial connect",headset)

def attempt_connect():
	global headset;
	if(headset != 0):
		headset.connect();
		print("Connect")
	else:
		print("Not connected")

def get_status():
	global headset;
	print(headset.status)
	if(headset == 0):
		return -1;
	if(headset.status == 'standby'):
		print(headset.status)
		return 0;
	if(headset.status == 'scanning'):
		print(headset.status)
		return 1;
	if(headset.status == 'connected'):
		print(headset.status)
		return 2;
	

def get_focus():
	global headset;
	if(headset != 0):
		print("Attention",headset.attention)
		return headset.attention;
	else:
		return -1;

def disconnect():
	global headset;
	if(headset != 0):
		print("Disconnecting")
		headset.disconnect()
	else:
		print("Not connected")

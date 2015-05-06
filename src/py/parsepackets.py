import mindwave, time

headset = mindwave.Headset('/dev/ttyUSB0')
time.sleep(2)

headset.connect()
print "c" #Connecting

while headset.status != 'connected':
    time.sleep(0.5)
    if headset.status == 'standby':
        headset.connect()
        print "c"#Still connected
        
print "success"#Start reading!

count = 0;

while True:
	count += 1;
	time.sleep(0.2)
	print "%s %s" % (headset.attention, headset.meditation)#Attention and meditation seperated by space

def cleanDisconnect():
	headset.disconnect()

import atexit
atexit.register(cleanDisconnect)


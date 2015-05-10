import mindwave, time

headset = mindwave.Headset('/dev/ttyUSB0')
time.sleep(2)

headset.connect()
print "Connecting..."

while headset.status != 'connected':
    time.sleep(0.5)
    if headset.status == 'standby':
        headset.connect()
        print "Retrying connect..."
        
print "Connected."

count = 0;

while True:
	count += 1;
	time.sleep(0.2)
	if(count > 50):
		break
	print "Attention: %s, Meditation: %s" % (headset.attention, headset.meditation)

headset.disconnect()
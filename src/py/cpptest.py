import parsepackets
import Tkinter as tk

inited = 0;

def handleKeypress(event):
	global inited
	if(event.char == 'c' and inited == 0):
		parsepackets.init_connect();
		print "init connect"
		inited = 1;
	elif(event.char == 'c' and inited != 0):
		parsepackets.attempt_connect();
		print "connect"
	if(event.char == 'd'):
		parsepackets.disconnect();
	if(event.char == 'f'):
		print parsepackets.get_focus();
	if(event.char == 's'):
		print parsepackets.get_status();



mainHandle = tk.Tk()
mainHandle.bind_all('<Key>', handleKeypress)
mainHandle.mainloop()

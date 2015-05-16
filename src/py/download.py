import urllib2
import webbrowser
import os
import sys

picture_page = "http://chart.apis.google.com/chart?chs=256x256&cht=qr&choe=UTF-8&&chl=" + sys.argv[1];

opener1 = urllib2.build_opener()
page1 = opener1.open(picture_page)
my_picture = page1.read()

filename = "Images/brain.png";

fout = open(filename, "wb")
fout.write(my_picture)
fout.close()
#!/usr/bin/python3
# -*- coding: utf-8 -*-

import cgitb
import cgi
import socket

cgitb.enable()
form = cgi.FieldStorage()

animList = { 0:"Farben", 1:"Gr&uuml;n" }
anim = -1

status = ""

try:
	animStr = form["anim"].value
	anim = int(animStr)
except:
	pass

if anim in animList.keys():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(("192.168.4.1",60000))
	s.sendall( ("a%02x\n" % anim).encode() )
	ans = s.recv(3).decode().strip()
	if ans == "A1":
		status = "Erfolgreich!"
	else:
		status = "Fehlgeschlagen."
	s.close()

html = \
"""
<html>
<head>
<style>
	h1 { font-family: Arial, Helvetica, sans-serif; front-size: 30px; }
	p { font-family: Arial, Helvetica, sans-serif; font-size: 20px; }
	li { font-family: Arial, Helvetica, sans-serif; font-size: 20px; }
</style>
</head>
<body>
<p><img src="fellowship_franken.png" width="400px"></img>
<h1>Plussy Display</h1>
	<p>
	Dieses Display kann mit freier Software gesteuert werden.<br>F&uuml;r Android
	steht hier eine App zur Verf&uuml;gung.<br> (Lizenz: GNU GPLv3):
		<ul>
			<li><a href="EFELMA.apk">APK Download</a></li>
			<li><a href="EFELMA.zip">Quellcode der App</a></li>
		</ul>
	</p>
	
	<p>
	Interesse an mehr freier Software? Die gibt's im <a href="FDroid.apk">F-Droid Store</a>.
	</p>
	
	<p>
	Und hier noch ein paar Extras: Animationen!
		<ul>
			%s
		</ul>
	</p>
	
	<p>
	Status: %s
	</p>
<p>
</body>
</html>
"""

animListHTML = ""
for k in animList.keys():
	animListHTML += "<li><a href=\"?anim=%d\">%s</a></li>" % (k,animList[k])
	
print("Content-Type: text/html;charset=utf-8\n\n")
print(html % (animListHTML, status))

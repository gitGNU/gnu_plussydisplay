#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
#	Plussy Display
#	Copyright (C) 2015  Christian Carlowitz <chca@cmesh.de>
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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
<link rel="stylesheet" href="pure-min.css"/>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<style>
	h1 { font-family: Arial, Helvetica, sans-serif; front-size: 30px; }
	p { font-family: Arial, Helvetica, sans-serif; font-size: 20px; }
	li { font-family: Arial, Helvetica, sans-serif; font-size: 20px; }
	.content { padding: 2em 1em 0; }
</style>
</head>
<body>
<div id="layout" class="pure-g">
<div class="content pure-u-1">
<p><img src="fellowship_franken.png" width="400px"></img>
<h1>Plussy Display</h1>
	<p>
	Dieses Display kann mit freier Software gesteuert werden.<br>F&uuml;r Android
	steht hier eine App zur Verf&uuml;gung.<br> (Lizenz: GNU GPLv3):
	<p><a class="pure-button" href="EFELMA.apk">Andoid APK Download</a>
	<a class="pure-button" href="EFELMA.zip">Quellcode der App</a></p>
	</p>
	
	<p>
	Interesse an mehr freier Software? Die gibt's im <a href="FDroid.apk">F-Droid Store</a>.
	</p>
	
	<p>
	Und hier noch ein paar Extras: Animationen!
		%s
	</p>
	
	<p>
	Status: %s
	</p>
<p>
</div>
</div>
</body>
</html>
"""

animListHTML = ""
for k in animList.keys():
	animListHTML += "<p><a class=\"pure-button\" href=\"?anim=%d\">%s</a></p>" % (k,animList[k])
	
print("Content-Type: text/html;charset=utf-8\n\n")
print(html % (animListHTML, status))

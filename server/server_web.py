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
<body>
<h1>Plussy Display</h1>
	<p>
	Dieses Display kann mit freier Software gesteuert werden. F&uuml;r Android
	steht hier eine App zur Verf&uuml;gung (Lizenz: GNU GPLv3):
		<ul>
			<li><a href="plussy.apk">APK Download</a></li>
			<li><a href="plussy.zip">Quellcode der App</a></li>
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

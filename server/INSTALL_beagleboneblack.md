# License

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.  This file is offered as-is,
without any warranty.

# Installation on BeagleBoneBlack

Note: This script has been updated for Debian jessie based images; particularly these: http://elinux.org/Beagleboard:BeagleBoneBlack_Debian#Debian_Image_Testing_Snapshots

Log of all steps performed:
* remove `contrib` and `non-free` flags in `/etc/apt/sources.list` (use free software only)
* `apt-get update` and `apt-get upgrade`
* disable graphical interface: `update-rc.d -f lightdm remove`
* disable network service: `update-rc.d -f wicd remove`
* disable xrdp service: `update-rc.d -f xrdp remove`
* disable avahi: `update-rc.d -f avahi-daemon remove`
* `apt-get purge avahi-daemon`
* some error with led_aging startup script, added missing LSB info
* install `lsof`
* disable beagle bone services (occupying, e.g., port 80):
	* `systemctl disable bonescript.service`
	* `systemctl disable bonescript.socket`
	* `systemctl disable bonescript-autorun.service`
	* `systemctl disable cloud9.service`
	* `systemctl disable cloud9.socket`
* since some services are somehow enabled again by systemd:
	* `cd /lib/systemd/system`
	* `mv cloud9.service cloud9.service.disabled`
	* `mv cloud9.socket cloud9.socket.disabled`
* hostapd
	* install: `apt-get install hostapd  iw iwconfig wpa-supplicant`
	* add config `/etc/hostapd/hostapd.conf`
	* register config in `/etc/default/hostapd`
	* setup wlan0 in `/etc/network/interfaces`
* udhcpd
	* add config `/etc/udhcpd.conf.wlan0`
	* add post-up call to udhcpd
* set root password, set debian user password
* install python3: `apt-get install python3 python3-serial`
* install plussy server script:
	* copy to /usr/local/sbin
	* create user: `adduser --system --home /tmp --shell /bin/bash --no-create-home --disabled-login --ingroup dialout plussy`
	* register with systemd (copy script to `/etc/systemd/system/`)
* read-only rootfs:
	* add "ro" to to /boot/uboot/uEnv.txt (mmcargs)
	* add "ro" to "/" and "/boot/uboot" in /etc/fstab
	* add some temp filesystems (see fstab)
	* enhance bashrc (see bash.bashrc)
* apache
	* /etc/apache2/envvars: move log dir to /var/log (no subdir)
	* mv default site on 8080 to available (which disables it)
	* add new default site ("default" file, see below)
	* enable new default site with symlink
	* enable cgi with `a2enmod cgi`
* bind
	* `apt-get install bind9`
	* copy zone files, register fsfe zone (see files below)
* using UART different than UART1
	* install capemgr stuff according to `https://github.com/beagleboard/bb.org-overlays`
	* disable HDMI in /boot/uEnv.txt (uncomment `dtb=am335x-boneblack-emmc-overlay.dtb`)
	* enable UART5 with `cape_enable=bone_capemgr.enable_partno=BB-UART5`
	* change port to ttyO5 in `/etc/systemd/system/plussy-server.service`

Files:
* `/etc/hostapd/hostapd.conf`
* `/etc/udhcpd.conf.wlan0`
* `/etc/network/interfaces`
* `/etc/bash.bashrc`
* `/etc/fstab`
* `/etc/apache2/sites-available/default`
* `/etc/bind/{db.4.168.192,db.fsfe,named.conf.local}`
* `/etc/systemd/system/plussy-server.service`
* `/usr/local/sbin/server.py`
* `/var/www/server_web.py`

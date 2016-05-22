# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

# System-wide .bashrc file for interactive bash(1) shells.

# To enable the settings / commands in this file for login shells as well,
# this file has to be sourced in /etc/profile.

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# set a fancy prompt (non-color, overwrite the one in /etc/profile)
#PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fs_mode=$(mount | sed -n -e "s/^\/dev\/disk\/by-uuid\/3c220583-6327-454d-af8d-4ff1572d37c2 on \/ .*(\(r[w|o]\).*/\1/p")
 
alias ro='mount -o remount,ro / ; fs_mode=$(mount | sed -n -e "s/^\/dev\/disk\/by-uuid\/3c220583-6327-454d-af8d-4ff1572d37c2 on \/ .*(\(r[w|o]\).*/\1/p")'
alias rw='mount -o remount,rw / ; fs_mode=$(mount | sed -n -e "s/^\/dev\/disk\/by-uuid\/3c220583-6327-454d-af8d-4ff1572d37c2 on \/ .*(\(r[w|o]\).*/\1/p")'
 
# setup fancy prompt
export PS1='\[\033[01;32m\]\u@\h${fs_mode:+($fs_mode)}\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '


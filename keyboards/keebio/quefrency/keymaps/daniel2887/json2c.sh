#/usr/bin/bash
qmk json2c *.json | sed 's/#include.*//g' > daniel2887_keymap.h

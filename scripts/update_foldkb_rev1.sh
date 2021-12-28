#/usr/bin/bash
set -e

echo Updating keymap from json
cd ../keyboards/keebio/foldkb/keymaps/daniel2887/
qmk json2c *.json | sed 's/#include.*//g' > daniel2887_keymap.h
cd -

echo Compiling and Flashing
qmk flash -j4 -kb keebio/foldkb/rev1 -km daniel2887

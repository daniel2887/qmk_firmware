#/usr/bin/bash
set -e

cd qmk_firmware

echo Updating keymap from json
cd keyboards/keebio/quefrency/keymaps/daniel2887/
qmk json2c *.json | sed 's/#include.*//g' > daniel2887_keymap.h
cd -

echo Compiling and Flashing
qmk flash -j4 -kb keebio/quefrency/rev4 -km daniel2887

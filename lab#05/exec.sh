#!/bin/bash

touch output.txt
cat /dev/null > output.txt

gnome-terminal -- ./run_1.sh
gnome-terminal -- ./run_2.sh

gnome-terminal -- tail --pid=$(pidof lab\#05_1 || pidof lab\#05_2) -f output.txt

rm lab#05_1
rm lab#05_2

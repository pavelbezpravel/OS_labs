#!/bin/bash

touch output.txt
cat /dev/null > output.txt

g++ lab_05_1.cpp -lpthread -o lab_05_1
g++ lab_05_2.cpp -lpthread -o lab_05_2

gnome-terminal -- ./lab_05_1
gnome-terminal -- ./lab_05_2

gnome-terminal -- tail --pid=$(pidof lab_05_1 || pidof lab_05_2) -f output.txt

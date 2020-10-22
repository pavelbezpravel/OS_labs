#!/bin/bash

g++ lab_06_1.cpp -lpthread -o lab_06_1 -lrt
g++ lab_06_2.cpp -lpthread -o lab_06_2 -lrt

gnome-terminal -- ./lab_06_2
gnome-terminal -- ./lab_06_1


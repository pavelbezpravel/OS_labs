#!/bin/bash

g++ lab_08_1.cpp -lpthread -o lab_08_1 -lrt
g++ lab_08_2.cpp -lpthread -o lab_08_2 -lrt

gnome-terminal -- ./lab_08_1
gnome-terminal -- ./lab_08_2

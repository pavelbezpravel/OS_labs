#!/bin/bash

g++ lab_07_1.cpp -lpthread -o lab_07_1
g++ lab_07_2.cpp -lpthread -o lab_07_2

gnome-terminal -- ./lab_07_2
gnome-terminal -- ./lab_07_1

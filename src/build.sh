#!/bin/bash

set -eu

mkdir -p out
gcc -c -o out/DEV_Config.o -DDEBUG -DRPI -DUSE_WIRINGPI_LIB -O3 third_party/e-paper/DEV_Config.c
gcc -c -o out/EPD_4in2.o -DDEBUG -DRPI -DUSE_WIRINGPI_LIB -O3 third_party/e-paper/EPD_4in2.c
g++ -c -o out/display.o -std=c++17 lib/display.cpp
g++ -shared -fPIC -o out/libepdisplay.so out/DEV_Config.o out/EPD_4in2.o out/display.o
g++ -o out/epdisplay -std=c++17  -lwiringPi -lm -L ./out -lepdisplay bin/epdisplay.cpp -Wl,-R,\$ORIGIN

#!/bin/bash
#
gcc -o xas_exit main.c xas_spc.c `pkg-config --libs --cflags gtk+-2.0`

#!/bin/bash
gcc -g -Wall main.c
valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./a.out

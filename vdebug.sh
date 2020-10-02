#!/bin/bash
gcc -g -Wall main.c arrayimpl.c
valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./a.out

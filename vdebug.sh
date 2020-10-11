#!/bin/bash
gcc -g -Wall shell.c arrayimpl.c
valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./a.out

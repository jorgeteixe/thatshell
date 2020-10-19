#!/bin/bash
gcc -g -Wall shell.c arrayimpl.c create.c delete.c list.c
valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./a.out

#!/bin/bash
gcc -g -Wall shell.c arrayimpl.c create.c delete.c listimpl.c -o shell.out
valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./shell.out

gcc -g -Wall listimpl.c list.c -o list.out

#! /bin/bash 

gcc main.c -o spinning-cube.exe -I ./include -L ./lib -lraylib -lm -ldl -lpthread


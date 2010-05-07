#!/bin/bash

echo "gcc -c subString.c"
gcc -c subString.c

echo "gcc -c tokMensagem.c"
gcc -c tokMensagem.c

echo "gcc -c serie.c"
gcc -c serie.c

echo "gcc -g -o server server.c subString.o tokMensagem.o serie.o"
gcc -g -o server server.c subString.o tokMensagem.o serie.o


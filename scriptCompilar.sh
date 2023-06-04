#!/bin/bash
bison -d sintactico.y
flex lexico.l
gcc -fPIC -shared -o functions.so functions.c
gcc abb.c TS.c sintactico.tab.c main.c errores.c pila.c lista.c -lfl -lm -ldl -o p3
./p3
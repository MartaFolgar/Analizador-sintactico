#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.c"
#include "sintactico.tab.h"
#include "TS.h"


int main(int argc,char* argv[]){
	//creación e iniciacion de la TS
	crearTS();	

	printf("Bienvenido/a!!\n\n");
	
	//indicar al analizador lexico (Flex) que se va a usar la entrada estandar (teclado)
	yyin=stdin;
	
	//llamada al analizador sintáctico (Bison) para comenzar su ejecución	
	while(1){
		yyparse();
	}	
}
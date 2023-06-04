%{
	#include <string.h>
	#include <dlfcn.h>
	#include <string.h>
	#include "estructuras.h"
	#include "sintactico.tab.h"
	#include "TS.h"	
	#include "errores.h"	
	#include "pila.h"
	#include "lista.h"

	void help(){
		printf("***************************************************AYUDA*********************************************************\nEsta calculadora permite dos modos de procesamiento de intrucciones:\n\t\t- a = 1+2;  Incluyendo un punto y coma al final de la instrucción se muestra el resultado.\n\t\t- a = 1+2   Sin punto y coma se ejecuta la instrucción pero no se muestra el resultado.\n\n");
		printf("***************************************************COMANDOS******************************************************\n\t\t- help/HELP : Se muestra la ayuda.\n\t\t- history/HISTORY : Se muestra el historial de todos los comandos e intrucciones ejecutados.\n\t\t- load/LOAD rutaFichero : Se carga un fichero y se ejecutan las instrucciones indicadas en él.\n\t\t- add/ADD nombreLibreria : Se abre la libreria indicada.\n\t\t- workspace/WORKSPACE : Se imprimen por pantalla todas las variables de la tabla de símbolos.\n\t\t- functions/FUNCTIONS : Se imprimen por pantalla todas las funciones disponibles en la tabla de símbolos.\n\t\t- clean/CLEAN : Se eliminan todas las variables de la tabla de símbolos.\n\t\t- clean/CLEAN var : Se elimina la variable indicada de la tabla de símbolos.\n\t\t- quit/QUIT : Se cierra el programa.\n\n");
		printf("***************************************************OPERADORES****************************************************\n\t\t+ Suma: a+a\n\t\t- Resta: a-a\n\t\t* Producto: a*a\n\t\t/ División: a/a\n\t\t^ Exponenciación: a^a\n\t\t= Asignación: a=a\n"); 
		printf("***************************************************FIN AYUDA*****************************************************\n");
	}

	void *handle;

%}

%option noyywrap

SIGNO \+|-|\*|=|^|\(|\)|;|\/

ID [a-zA-Z_][a-zA-Z0-9_]*

DIGIT [0-9]
DECINTEGER [1-9](_?{DIGIT})*|0+(_?0)*

DIGITPART {DIGIT}(_?{DIGIT})*
FRACTION \.{DIGITPART}
POINTFLOAT {DIGITPART}?{FRACTION}|{DIGITPART}\.

EXPONENT (e|E)[+|-]?{DIGITPART}
EXPONENTFLOAT ({DIGITPART}|{POINTFLOAT}){EXPONENT}

/*Comandos*/
HELP "help"|"HELP"
CARGA "load"|"LOAD"
FICHERO ("\.\/")?([\(\)/_\-a-zA-Z0-9])+
EXTENSION ([a-zA-Z])*
RUTA {FICHERO}"."?{EXTENSION}
ADD "add"|"ADD"
WORKSPACE "workspace"|"WORKSPACE"
FUNCS "functions"|"FUNCTIONS"
CLEAN "clean"|"CLEAN"[ {ID}]
HISTORY "history"|"HISTORY"
QUIT "quit"|"QUIT"

%x limpiar

%%

{SIGNO} {return yytext[0];}
{DECINTEGER}|{POINTFLOAT}|{EXPONENTFLOAT} {yylval.NUMERO = atof(yytext); return NUMERO;}

{HELP} { insertarEnHistorial(yytext); help();}

{ADD}" "{RUTA} {
	handle = dlopen(yytext+4, RTLD_LAZY); //apertura de nuestra libreria
	if (!handle) { //error al abrir la libreria
		handle=NULL;
		error(2, yytext+4);
	}
	insertarEnHistorial(yytext);
}

{CARGA}" "{RUTA} {
	if(es_vacia_pila()){ /*Si es el primer fichero que se carga, se crea la pila*/
		crear_pila();
	}

	FILE *fd;
	if((fd=fopen(yytext+5, "rt"))!=NULL){ //Apertura del fichero: el nombre del fichero empieza en la posicion 5: load [fichero]
		if(!es_vacia_pila()){ //si la pila no está vacía:
			if(strcmp(tope().nombreFichero, yytext+5)==0){ //si el fichero que se intenta abrir es el mismo que el del tope de la pila: error (apertura recursiva del mismo fichero)
				error(6, yytext+5);
				fclose(fd);
			}else{
				if(strcmp(tope().llamadoPor, yytext+5)==0){ //si un fichero intenta cargar el mismo fichero desde el que fue abierto: error (dos ficheros abriendose recursivamente entre ellos)
					error(10, "");
					fclose(fd);
				}else{
					yyin=fd; //se establece como entrada del analizador el nuevo fichero que se acaba de cargar
					push(fd, yytext+5, tope().nombreFichero); //se inserta el fichero en la pila
				}
			}
		}else{ //si la pila está vacía:
			yyin=fd; //se establece como entrada del analizador el nuevo fichero que se acaba de cargar
			push(fd, yytext+5, "null"); //se inserta el fichero en la pila
		}		
	}else{
		error(0, yytext+5); //error en la apertura del fichero
		yyin=stdin; //se establece como entrada del analizador la entrada estandar (teclado)
	}
	insertarEnHistorial(yytext);
}

{WORKSPACE} {insertarEnHistorial(yytext); imprimir('v');}

{FUNCS} {insertarEnHistorial(yytext); imprimir('f');}

{CLEAN} {BEGIN(limpiar);}
<limpiar>\n {insertarEnHistorial("clean"); suprimir(); BEGIN(INITIAL);} //comando "clean": elimina todas las variables
<limpiar>\b {}
<limpiar>{ID} {
	char *clean=(char *)malloc(strlen(yytext)+7);
	strcpy(clean, "clean ");
	strcat(clean, yytext);
	insertarEnHistorial(clean);
	free(clean);
	suprimirVar(yytext); 
	BEGIN(INITIAL);
} //comando "clean [var]": elimina solo la variable indicada

{HISTORY} {insertarEnHistorial(yytext); imprimirHistorial();}

{QUIT} {
	if(handle!=NULL){
		dlclose(handle);		
	}
	//liberación del analizador léxico de Flex
	fclose(yyin);
	yy_delete_buffer(YY_CURRENT_BUFFER);
	return EXIT;
}

{ID} {
	tipoelem *c=buscar_nodoTS(yytext); //se busca en la TS
	if(c==NULL){ //elemento no existente en la TS

		if (handle!=NULL){
			double (*func)(double);
			dlerror(); 

			*(void **) (&func) =  dlsym(handle, yytext); //se comprueba si es una de las funciones de la libreria

			if (dlerror() != NULL)  { //no es una de las funciones
				yylval.ID=yytext;
				return ID; //se devuelve un tipo desconocido. En Bison se comprobará si se realiza una inicialización (en ese caso se inserta en la TS) o no (se genera un error)
			}else{
				//se inserta la función en la TS
	    		tipoelem *nodo=insertarTS(yytext, FUNCION);
		        nodo->valor.func=func;
		        yylval.FUNCION=nodo;
				return FUNCION;	
			}
		}else{
			yylval.ID=yytext;
			return ID;
		}


	}else if(c->compLexico==VAR){ //variable
		yylval.VAR=c;
		return VAR;
	}else if(c->compLexico==CTE){ //constante
		yylval.CTE=c;
		return CTE;
	}else if(c->compLexico==FUNCION){ //funcion
		yylval.FUNCION=c;
		return FUNCION;
	}
}

[ \t\r\b\f]  

\n {return '\n';}

. {error(1, yytext);} //Cualquier cadena no contemplada: error

<<EOF>> {
    fclose(tope().fichero); //cierre del fichero cuando se llega al End Of File
    pop(); //se elimina el fichero de la pila
    if(es_vacia_pila()){ //si no quedan ficheros abiertos: se destruye la pila + se vuelve a la entrada estandar (teclado)
    	destruir_pila();
    	yyin=stdin;
    }else{ //si aun quedan ficheros abiertos: se usa como entrada el ultimo fichero abierto
    	yyin=tope().fichero;
    }
    yyrestart(yyin); //se reinicia la entrada
    BEGIN(INITIAL);
}

%%


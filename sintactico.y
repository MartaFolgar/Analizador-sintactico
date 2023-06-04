%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "errores.h"
#include "estructuras.h"
#include "TS.h"
#include "lista.h"

int yylex();
void yyerror(char *s);
int errores=0;
%}


%define api.value.type union
%token EXIT
%token <char *> ID
%token <double> NUMERO
%token <tipoelem*> VAR FUNCION CTE
%type <double> exp //simbolos no terminales

//precedencia de operadores
%right '='
%left '-' '+'
%left '*' '/'
%left NEG
%right '^'


%%

input:  	
	| input line
;


line: '\n' 
	| exp '\n' {
		if(errores==1){
			errores=0;
		}
	}
	| exp ';' '\n' {
		if(errores==0){
			printf("\t%.10g\n", $1);
		}else{
			errores=0;
		}
	}
	| error '\n' {yyerrok;}
	| EXIT {
		//liberación de la memoria reservada para la TS
		destruirTS();

		printf("Hasta pronto!!\n");
		exit(0);
	}
;

exp: NUMERO {$$=$1;}
	| VAR {$$=$1->valor.var;}
	| CTE {$$=$1->valor.var;}
	| ID {
		errores=1;
		error(5,""); //no se encuentra en la TS, no está inicializado
	}
	| VAR '=' exp {
		$1->valor.var=$3; $$=$3; //se actualiza el valor
	}	
	| ID '=' exp { //si no está almacenado en la TS y se realiza una asignación: se crea el elemento y se inicializa
		char *token = strtok($1, "=");
		int i=0, cont=0; 

		//se comprueba si el lexema esta en mayusculas: en ese caso se inserta como CTE
		for(i=0; i<strlen(token); i++){
			if(isupper(token[i])){
				cont++;
			}
		}
		if(cont==strlen(token)){
			insertarTS(token, CTE)->valor.var=$3; 
		}else{
			insertarTS(token, VAR)->valor.var=$3; 
		}
		$$=$3;
		
	}
	| FUNCION '('exp')'  {
		$$ = (*($1->valor.func))($3);
	}
	| ID '('exp')'  { //si se intenta usar una función que no se encuentra en la TS ni en nuestra librería: error
		errores=1;
		error(8,"");
	}
	| exp '+' exp { $$ = $1 + $3; }
	| exp '-' exp { $$ = $1 - $3; }
	| exp '*' exp { $$ = $1 * $3; }
	| exp '/' exp { 
		if($3!=0){
			$$ = $1 / $3; 
		}else{
			$$=0;
			error(9, "");
			errores=1;
		}
	}	
	| '-' exp %prec NEG { $$ = -$2; }
	| exp '^' exp {$$ = pow ($1, $3);}
	| '(' exp ')' { $$ = $2; }
;


%%

void yyerror(char *s){ 
    error(7, s);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Estructura de cada nodo de la lista
struct Nodo
{
	char *dato;
	struct Nodo* sig; 
};

struct Nodo* nodo;


//Inicializacion de la lista
void inicializarHistorial(){
	nodo=(struct Nodo*)malloc(sizeof(struct Nodo)); //reserva de memoria para el primer nodo
	nodo->sig = NULL;
	nodo->dato=NULL;
};

//Imprime por pantalla el contenido de la lista: todos los comandos que se han ejecutado
void imprimirHistorial(){
		struct Nodo* n=nodo->sig;

		printf("***************************************HISTORIAL DE COMANDOS************************************************\n");
		while(n)		{
			printf("%s\n",n->dato);// Imprime el comando
			n=n->sig;// Apunta al siguiente nodo 
		}
		printf("************************************************************************************************************\n");
};


//Inserta un nodo en la lista: un nuevo comando
void insertarEnHistorial(char *dato){
	struct Nodo* p;
	struct Nodo* nuevo=(struct Nodo*)malloc(sizeof(struct Nodo)); //reserva de memoria para el nuevo nodo
	nuevo->dato=(char *)malloc(strlen(dato)+1);
	strcpy(nuevo->dato, dato);

	//se inserta al final de la lista
	nuevo->sig = NULL;
	if (nodo != NULL){
		p = nodo;
		while (p->sig != NULL){			
			p = p->sig;
		}
		p->sig = nuevo;
	}	
};


//Liberacion de la memoria reservada para la lista
void destruirHistorial(){
	 struct Nodo* actual; //Puntero auxiliar
  
    while(nodo != NULL){ 
        actual = nodo; 
        nodo = nodo->sig;   
        free(actual->dato); 
        free(actual); 
        actual=NULL;    
    }
}

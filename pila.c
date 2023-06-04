#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"


struct celdapila {
	tipoelempila elemento;
	struct celdapila *sig;
};

pila P; 


//Inicializacion de la pila
void crear_pila() {
	P = NULL;
}

//Libera la memoria de cada celda de la pila
void destruir_pila() {
	pila aux;
	aux = P;
	while (aux != NULL) {
		aux = aux->sig;
		free(P->elemento.llamadoPor);
		free(P->elemento.nombreFichero);
		free(P);
		P = aux;
	}
}

//Comprueba si la pila está vacía
unsigned es_vacia_pila() {
	return P == NULL;
}

//Devuelve el elemento tope de la pila
tipoelempila tope() {
	if (!es_vacia_pila(P)) {	
		return P->elemento;
	}
}

//Introduce un nuevo elemento en el tope de la pila
void push(FILE *fd, char *nombreFichero, char *llamadoPor) {
	pila aux;
	aux = (pila) malloc(sizeof(struct celdapila));
	aux->elemento.fichero=fd;
	aux->elemento.nombreFichero=(char *) malloc(strlen(nombreFichero)+1);	
	strcpy(aux->elemento.nombreFichero, nombreFichero);
	aux->elemento.llamadoPor=(char *) malloc(strlen(llamadoPor)+1);	
	strcpy(aux->elemento.llamadoPor, llamadoPor);
	aux->sig = P;
	P = aux;
}

//Elimina de la pila el elemento tope
void pop() {
	pila aux;
	if (!es_vacia_pila()) {	
		aux = P;
		P = (P)->sig;
		free(aux->elemento.llamadoPor);
		free(aux->elemento.nombreFichero);
		free(aux);
	}
}
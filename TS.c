#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "TS.h"
#include "abb.h"
#include "errores.h"
#include "sintactico.tab.h"

TS tabla;


//Crea el arbol vacio e introduce las funciones y las constantes iniciales
void crearTS() {
    tabla=NULL;
    crearABB(&tabla);
}


//Inserta una variable en la TS
tipoelem * insertarTS(char *nombre, int compLexico){
    return insertarABB(&tabla, nombre, compLexico);
}


//Destruye la TS recursivamente
void destruirTS() {
    destruirABB(&tabla);
}


//Busca un nodo en la TS
tipoelem * buscar_nodoTS(tipoclave cl) {
 return buscar_nodoABB(tabla, cl);
}


//Imprime por pantalla las variables o funciones de la TS
void imprimir(char tipo){
    if(tipo=='v'){
        printf("Las variables de la TS son:\n");
    }else if(tipo=='f'){
        printf("Las funciones disponibles son:\n");
    }    
    imprimirABB(tabla, tipo);
}

//Elimina la variable indicada de la TS
void suprimirVar(char *nombre){
    tipoelem *b=buscar_nodoABB(tabla, nombre);
    if(b!=NULL){
        if(b->compLexico==VAR){
            eliminar_nodoABB(&tabla, *b);
        }else if(b->compLexico==FUNCION){
             error(3, nombre);
        }else if(b->compLexico==CTE){
             error(4, nombre);
        }         
    }else{
        error(5, nombre);
    }   
}

//Elimina todas las variables de la TS
void suprimir(){
    suprimirABB(&tabla);
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "estructuras.h"
#include "inicializaciones.h"
#include "abb.h"
#include "sintactico.tab.h"
#include "lista.h"


//estructura de cada elemento del arbol
struct celda {
    tipoelem info;
    struct celda *izq, *der;
};


//---------------FUNCIONES PRIVADAS-----------------
//Extraer la clave de una celda 
tipoclave _extraerClave(tipoelem * E) {
    return E->lexema;
}


//Comparar dos claves
int _compararClaves(tipoclave cl1, tipoclave cl2) {

    if (strcmp(cl1,cl2) == 0){
        return 0;
    }
    else if (strcmp(cl1,cl2) <0){
        return -1;
    }
    else{
        return 1;
    }    
}


//Indica si el arbol esta vacio
unsigned _esVaciaTS(TS A) {
    return A == NULL;
}


//Devuelve el subarbol izquierdo
TS _izqTS(TS A) {
    return A->izq;
}


//Devuelve el subarbol derecho
TS _derTS(TS A) {
    return A->der;
}


//Devuelve el contenido del nodo
void _leerTS(TS A, tipoelem *E) {
    *E = A->info;
}


//Informar si una clave está en el árbol
unsigned _esMiembroClave(TS A, tipoclave cl) {

    if (_esVaciaTS(A)) {
        return 0;
    }
    int comp=_compararClaves(cl, _extraerClave(&(A->info)));

    if (comp == 0) { //cl == A->info
        return 1;
    }
    if (comp > 0) { //cl > A->info
        return _esMiembroClave(A->der, cl);

    //cl < A->info
        return _esMiembroClave(A->izq, cl);
    }
}


//Devuelve mínimo de subárbol dcho 
tipoelem _suprimir_min(TS *A) {//Se devuelve el elemento más a la izquierda
    TS aux;
    tipoelem ele;
    if (_esVaciaTS((*A)->izq)) {//Si izquierd vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux->info.lexema);
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}




//---------------FUNCIONES PUBLICAS-----------------
//Crea e inserta un elemento en la TS y devuelve el elemento creado
tipoelem * insertarABB(TS *A,  char *nombre, int compLexico) {
    if (_esVaciaTS(*A)) {
        *A = (TS) malloc(sizeof (struct celda));

        (*A)->info.lexema=malloc(strlen(nombre)+1);  
        strcpy((*A)->info.lexema, nombre);
        (*A)->info.compLexico=compLexico;
        
        (*A)->izq = NULL;
        (*A)->der = NULL;

        return &(*A)->info;
    }
    int comp = _compararClaves(nombre, _extraerClave(&(*A)->info));
    if (comp > 0) {
        insertarABB(&(*A)->der, nombre, compLexico);
    } else {
        insertarABB(&(*A)->izq, nombre, compLexico);
    }
}



//Crea el arbol vacio e introduce las funciones y las constantes iniciales
void crearABB(TS *A) {
    int i;
    for (i = 0; funciones[i].nombreFuncion != 0; i++) {   
        tipoelem *nodo=insertarABB(A, funciones[i].nombreFuncion, FUNCION);
        nodo->valor.func=funciones[i].ptrFuncion;
    }

    for (i = 0; constantes[i].nombreCte != 0; i++) {   
        tipoelem *nodo=insertarABB(A, constantes[i].nombreCte, CTE);
        nodo->valor.var=constantes[i].valorCte;
    }     

    //inicializacion del historial de comandos
    inicializarHistorial();
}



//Destruye la TS recursivamente
void destruirABB(TS *A) {
    if (!_esVaciaTS(*A)) {        
        destruirABB(&((*A)->izq));
        free(((*A)->info).lexema);
        destruirABB(&((*A)->der));    
        free(*A);
        *A = NULL;
    }

    //liberacion de memoria del historial de comandos
    destruirHistorial();
}


//Busca un nodo en el arbol y, si existe, devuelve un puntero a dicho nodo
tipoelem * buscar_nodoABB(TS A, tipoclave cl) {
    if (_esVaciaTS(A)) {
        return NULL;
    }

    if(_esMiembroClave(A, cl)){
        int comp = _compararClaves(cl, _extraerClave(&A->info));

        if (comp == 0) { // cl == A->info
            return &A->info;            
        } else if (comp < 0) { // cl < A->info
            buscar_nodoABB(A->izq, cl);
        } else { // cl > A->info
            buscar_nodoABB(A->der, cl);
        }
    }else{
        return NULL;
    }

}


//Imprime las variables o funciones de la TS (dependiendo del parametro que se le pase)
void imprimirABB(TS A, char tipo){
    tipoelem b;
    if(!_esVaciaTS(A)){
        imprimirABB(_izqTS(A), tipo);
        _leerTS(A, &b);   
        if(tipo=='v' && (b.compLexico==VAR || b.compLexico==CTE)){ //se imprimen solo las variables
            printf("\t%s = ", b.lexema);
            printf("%g\n", b.valor.var);
        }else if(tipo=='f' && b.compLexico==FUNCION){ //se imprimen solo las funciones
            printf("\t%s\n", b.lexema);
        }
        imprimirABB(_derTS(A), tipo);
    }
}


//Elimina la variable indicada de la TS
void eliminar_nodoABB(TS *A, tipoelem E) {
    TS aux;
    if (_esVaciaTS(*A)) {
        return;
    }

    tipoclave cl = _extraerClave(&E);
    int comp = _compararClaves(cl, _extraerClave(&(*A)->info));
    if (comp < 0) { //if (E < (*A)->info) {
        eliminar_nodoABB(&(*A)->izq, E);
    } else if (comp > 0) { //(E > (*A)->info) {
        eliminar_nodoABB(&(*A)->der, E);
    } else if (_esVaciaTS((*A)->izq) && _esVaciaTS((*A)->der)) {
        free((*A)->info.lexema);
        free(*A);
        *A = NULL;
    } else if (_esVaciaTS((*A)->izq)) { // pero no es vacio derecha
        aux = *A;
        *A = (*A)->der;
        free(aux->info.lexema);
        free(aux);
    } else if (_esVaciaTS((*A)->der)) { //pero no es vacio izquierda
        aux = *A;
        *A = (*A)->izq;
        free(aux->info.lexema);
        free(aux);
    } else { //ni derecha ni izquierda esta vacio, busco mínimo subárbol derecho
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}


//Elimina todas las variables de la TS
void suprimirABB(TS *A){
    tipoelem b;

    if (!_esVaciaTS(*A)) {        
        suprimirABB(&((*A)->izq));
        _leerTS(*A, &b);
        if(b.compLexico==VAR){
            free(((*A)->info).lexema);
        }        
        suprimirABB(&((*A)->der));    
        _leerTS(*A, &b);
        if(b.compLexico==VAR){
            free(*A);
            *A = NULL;
        } 
        
    }
}
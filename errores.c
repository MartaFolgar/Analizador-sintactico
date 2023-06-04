#include <stdio.h>
#include <stdlib.h>
#include "errores.h"

//Imprime por pantalla los distintos errores encontrados durante la ejecución del programa
void error(int tipo, char *error){
	switch (tipo){
		case 0:
			printf("Error al abrir el fichero de entrada \"%s\".\n\n", error);
		break;	
		case 1:
			printf("Error. Cadena inesperada.\n\n");
		break;
		case 2:
			printf("Error. No se puede cargar la libreria externa: %s.\n\n", error);
		break;
		case 3:
			printf("Error. No se puede eliminar una funcion, en este caso: %s.\n\n", error);
		break;
		case 4:
			printf("Error. No se puede eliminar una constante, en este caso: %s.\n\n", error);
		break;
		case 5:
			printf("Error. Variable no definida.\n\n");
		break;
		case 6:
			printf("Error. Intento de apertura recursiva del mismo fichero: %s.\n\n", error);
		break;
		case 7:
			printf("Error de tipo: %s.\n\n", error);
		break;
		case 8:
			printf("Error. Funcion no encontrada.\n\n");
		break;
		case 9:
			printf("Error. Intento de divison por cero.\n\n");
		break;
		case 10:
			printf("Error. Dos ficheros tratando de abrirse recursivamente el uno al otro.\n\n");
		break;
	}
}
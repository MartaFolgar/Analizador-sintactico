
typedef struct celdapila *pila;	

// Tipo de elemento de la pila
typedef struct{
    FILE *fichero;
    char *nombreFichero;
    char *llamadoPor;
}tipoelempila;


/**
 * Inicializacion de la pila
 */
void crear_pila();

/**
 * Libera la memoria de cada celda de la pila
 */
void destruir_pila();

/**
 * Comprueba si la pila está vacía
 * @return 1 si la pila está vacía y 0 en otro caso
 */
unsigned es_vacia_pila();

/**
 * Devuelve el elemento tope de la pila
 * @return Tope de la pila
 */
tipoelempila tope();

/**
 * Introduce un nuevo elemento en el tope de la pila
 * @param fd Fichero a introducir
 * @param nombreFichero Nombre del fichero a introducir
 */
void push(FILE *fd, char *nombreFichero, char *llamadoPor);

/**
 * Elimina de la pila el elemento tope
 */
void pop();


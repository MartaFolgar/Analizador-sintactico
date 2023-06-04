/**
 * Crea el arbol vacio e introduce las funciones y las constantes iniciales
 */
void crearABB(TS *A);

/**
 * Crea e inserta un elemento en la TS y devuelve el elemento creado
 * @param A Puntero a TS, es el arbol donde se va a insertar el nuevo elemento
 * @param nombre Puntero a char, es el lexema del elemento a insertar
 * @param compLexico Indica el tipo de elemento a insertar (VAR, FUNCION, CTE)
 */
tipoelem * insertarABB(TS *A,  char *nombre, int compLexico);

/**
 * Destruye el arbol recursivamente
 * @param A Puntero a TS, es el arbol que se va a destruir
 */
void destruirABB(TS *A);

/**
 * Busca un nodo en el arbol y, si existe, devuelve un puntero a dicho nodo
 * @param A Arbol donde se busca el nodo
 * @param cl clave (lexema) del nodo que se está buscando
 */
tipoelem * buscar_nodoABB(TS A, tipoclave cl);

/**
 * Imprime las variables o funciones de la TS (dependiendo del parametro que se le pase)
 * @param A Arbol que se quiere imprimir
 * @param tipo indica el tipo de elementos que se deben imprimir (variables o funciones)
 */
void imprimirABB(TS A, char tipo);

/**
 * Elimina la variable indicada de la TS
 * @param A Puntero a TS, es el arbol donde se encuentra la variable a eliminar
 * @param E Elemento que se quiere eliminar
 */
void eliminar_nodoABB(TS *A, tipoelem E);

/**
 * Elimina todas las variables de la TS
 * @param A Puntero a TS, es el arbol donde se encuentran las variables a eliminar
 */
void suprimirABB(TS *A);



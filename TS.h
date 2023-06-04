/**
 * Crea el arbol vacio e introduce las funciones y las constantes iniciales
 */
void crearTS();

/**
 * Crea e inserta un elemento en la TS y devuelve el elemento creado
 * @param nombre Puntero a char, es el lexema del elemento a insertar
 * @param compLexico Indica el tipo de elemento a insertar (VAR, FUNCION, CTE)
 */
tipoelem * insertarTS(char *nombre, int compLexico);

/**
 * Destruye el arbol recursivamente
 */
void destruirTS();

/**
 * Busca un nodo en el arbol y, si existe devuelve un puntero a dicho nodo
 * @param cl clave (lexema) del nodo que se está buscando
 */
tipoelem * buscar_nodoTS(tipoclave cl);

/**
 * Imprime las variables o funciones de la TS (dependiendo del parametro que se le pase)
 * @param tipo indica el tipo de elementos que se deben imprimir (variables o funciones)
 */
void imprimir(char tipo);

/**
 * Elimina la variable indicada de la TS
 * @param nombre Puntero a char, es el lexema del elemento a eliminar
 */
void suprimirVar(char *nombre);


/**
 * Elimina todas las variables de la TS
 */
void suprimir();

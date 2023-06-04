typedef char *tipoclave; 

typedef struct {
    int compLexico; //tipo de elemento: VAR, CTE, FUNCION
    char *lexema; //nombre de la variable, constante o funcion
    union {
        double var; // valor de una variable o constante 
        double (*func)(double); // puntero a una función 
    } valor;
}tipoelem;

typedef struct celda *TS;


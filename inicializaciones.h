//Estructura de las constantes
struct constante{ 
    char *nombreCte;
    double valorCte;
};

//Constantes que se cargarán al inicio del programa
struct constante const constantes[] ={
    { "PI", M_PI    },
    { "E" ,  M_E    },
    { 0   ,    0    },
};


//Estructura de las funciones
struct funcion{ 
    char *nombreFuncion;
    double (*ptrFuncion) (double); 
};


//Funciones que se cargarán al inicio del programa
struct funcion const funciones[] ={
    { "sin",  sin   },
    { "cos",  cos   },
    { "tan",  tan   },
    { "asin", asin  },
    { "acos", acos  },
    { "atan", atan  },
    { "exp",  exp   },
    { "log",  log   },
    { "sqrt", sqrt  },
    { 0,      0     }, 
};

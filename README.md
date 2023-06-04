# Analizador-sintactico
Analizador sintáctico desarrollado en C para la asignatura de Compiladores e Intérpretes.

En esta práctica se han utilizado las herramientas Flex y Bison con el fin de construir un intérprete de expresiones de cálculo matemático. Esta herramienta permite interpretar expresiones desde un fichero de la forma: 

x = 3;

y = 2 * pi * x;

z = x * sin (y + pi/6);

Como resultado de la ejecución se presentan los valores que toman las distintas variables y el intérprete incorpora algunas de las operaciones aritméticas y funciones propias de una calculadora científica (sin(),cos(),log(),exp(),…), aplicadas a números tanto enteros como reales en notación científica. Además, la herramienta contiene un juego de comandos que facilitarán su uso, y que permitirán solicitar ayuda, cargar ficheros de expresiones, imprimir el contenido de las variables definidas en el espacio de trabajo, eliminar el propio espacio de trabajo o salir del programa, entre otros.

La versión de Flex utilizada ha sido la 2.5.4 y la de Bison la 3.5.1. 
Todo el código fue desarrollado y probado en un entorno Ubuntu versión 20.04.3 LTS.


*******************************EJECUCIÓN*********************************
El primer paso para ejecutar el programa será descomprimir el fichero "Analizador Sintactico.zip" que contiene todos los archivos del programa.

Una vez descomprimido, se deberá acceder a esa carpeta desde la terminal.

Por último, una vez situados en el directorio "Analizador Sintactico" desde la terminal, será necesario ejecutar el script incluido:
> bash scriptCompilar.sh


*********************************NOTAS***********************************
- Además de los archivos que contienen el propio código de la práctica, se incluye un fichero "functions.c", en el que se definen varias funciones que se podrán incluir en la calculadora de forma dinámica. Para su correcta ejecución, este fichero debe estar situado en el mismo directorio que el resto de ficheros de la práctica.
Para cargar una librería se debe emplear el siguiente comando: add/ADD rutaLibreria. 
En caso de que la librería se encuentre en el mismo directorio que el resto de archivos, se empleará la ruta: "./libreria.so".

- En la calculadora se ofrece la posibilidad de ejecutar los comandos indicados en un fichero, mediante el comando load [fichero]. Para ello será necesario indicar la ruta del fichero. En el zip de la practica se incluyen dos ejemplos de ficheros de entrada: "prueba.txt" y "prueba2.txt".

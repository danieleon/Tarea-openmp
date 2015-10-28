#openmp
Carpeta openmp

En esta carpeta se encuentran los códigos de los dos programas propuestos.

- pi-mod.c: En este programa se paralelizó el código en la sentencia for. Se comprobó la eficiencia de la solución midiendo el tiempo de ejecución y comparándolo con el caso secuencial; encontrando que efectivamente es un programa más ágil.

- montecarlopi-mod.c: Este programa tuvo más detalles que revisar. Se paralelizó el for también, esta vez usando la directiva "dynamic", y la manera en que se logró tener una sumatoria cercana al resultado real fue usando la sentencia #pragma omp atomic antes del Ncirc++;



Este repositorio contiene dos programas en C que utilizan Pthreads para realizar cálculos concurrentes. Los programas se enfocan en el cálculo paralelo de la Serie de Fibonacci y una serie matemática (1 / 2^n), demostrando la utilización de hilos y sincronización mediante mutex.

## Serie de Fibonacci Paralela
*Archivo: fibonacci_pthreads.cpp*
Este programa calcula los números de la Serie de Fibonacci hasta un número n proporcionado por el usuario, utilizando múltiples hilos.

- Características:
Usa un vector global para almacenar los números de Fibonacci calculados.
Implementa un mutex para proteger el acceso concurrente a la variable total_sum.
Cada número de Fibonacci es calculado por un hilo independiente.
- Entrada:
Un número entero n entre 0 y 100.
- Salida:
Los números de Fibonacci calculados hasta n.
La suma total de los números de Fibonacci.

## Sumatoria de 1 / 2^n Paralela
*Archivo: serie_pthreads.cpp*
Este programa calcula los términos de la serie matemática 1 / 2^n y su sumatoria utilizando múltiples hilos.

- Características:
Cada término 1 / 2^n es calculado por un hilo independiente.
Los resultados son almacenados en una estructura que comparte información entre los hilos.
Los resultados son sumados después de que todos los hilos han finalizado.
- Entrada:
Un número entero n no negativo, que indica el máximo término de la serie a evaluar.
- Salida:
Los valores de cada término 1 / 2^n calculados.
La sumatoria de todos los términos.

##Compilación
```
gcc fibonacci_pthreads.cpp -o fibonacci_pthreads -pthread
gcc serie_pthreads.cpp -o serie_pthreads -pthread
```
## Ejecución
```
./fibonacci_pthreads
./serie_pthreads

# Explicación Técnica
### Uso de Pthreads
Pthreads permite ejecutar múltiples hilos concurrentemente, lo cual acelera el cálculo al dividir las tareas entre los hilos.

Los programas demuestran:
- Sincronización: Uso de pthread_mutex_t para proteger variables compartidas.
- Creación y unión de hilos: Uso de pthread_create y pthread_join.
### Mutex
En el programa de Fibonacci, un mutex asegura que múltiples hilos no modifiquen la suma total al mismo tiempo, previniendo condiciones de carrera.
### Estructuras Compartidas
En la sumatoria de 1 / 2^n, los resultados de los hilos son almacenados en una estructura compartida, facilitando la recopilación de resultados.

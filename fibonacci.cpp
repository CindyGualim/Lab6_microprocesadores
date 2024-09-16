//
//Librerías
#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

//Definir Variables goblales para almacenar números Fibonacci
vector<int> fibonacci_series;
int total_sum = 0;
pthread_mutex_t mutex_sum; //mutex permite manejar el acceso seguro a total_sum desde multiples hilos


//función para calcular los numeros 
void* calculate_fibonacci(void* arg) {
    int n = *(int*)arg;
    pthread_mutex_lock(&mutex_sum);  // Bloquear el mutex para acceso seguro a la suma

    if (n == 0) {
        fibonacci_series.push_back(0);
    } else if (n == 1) {
        fibonacci_series.push_back(1);
    } else {
        int fib = fibonacci_series[n-1] + fibonacci_series[n-2];
        fibonacci_series.push_back(fib);
    }

    total_sum += fibonacci_series.back(); // Sumar el último número de la serie
    pthread_mutex_unlock(&mutex_sum);  // Liberar el mutex

    pthread_exit(NULL);  // Salida segura para el hilo
    return nullptr;  // Retorna un puntero nulo
}


//Funcion principal 
int main() {
    int n;
    cout << "Ingresa un número entre 0 y 100: ";
    cin >> n;

    if (n < 0 || n > 100) {
        cout << "El número debe estar entre 0 y 100." << endl;
        return 1;
    }

    // Inicializar el mutex
    pthread_mutex_init(&mutex_sum, NULL);

    // Crear un arreglo de hilos
    pthread_t threads[n+1];

    // Inicializar los primeros dos números de Fibonacci
    fibonacci_series.push_back(0);
    fibonacci_series.push_back(1);

    for (int i = 2; i <= n; ++i) {
        pthread_create(&threads[i], NULL, calculate_fibonacci, (void*)&i);
        pthread_join(threads[i], NULL); // Esperar a que cada hilo termine
    }

    // Mostrar los números de Fibonacci calculados
    cout << "Serie de Fibonacci: ";
    for (int i = 0; i <= n; ++i) {
        cout << fibonacci_series[i] << " ";
    }
    cout << endl;

    // Mostrar la suma total de los números de Fibonacci
    cout << "La suma total es: " << total_sum << endl;

    // Destruir el mutex
    pthread_mutex_destroy(&mutex_sum);

    return 0;
}


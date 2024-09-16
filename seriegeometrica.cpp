#include <iostream>
#include <pthread.h>
#include <cmath>

struct SeriesParams {
    int n;
    double result;
};

void* calculateTerm(void* arg) {
    SeriesParams* params = (SeriesParams*)arg;
    params->result = 1.0 / std::pow(2, params->n);  // Cálculo de 1 / 2^n
    pthread_exit(nullptr);
}

int main() {
    int num;
    std::cout << "Ingrese el valor máximo de n a evaluar: ";
    std::cin >> num;

    if (num < 0) {
        std::cerr << "El valor de n debe ser no negativo!" << std::endl;
        return -1;
    }

    pthread_t threads[num + 1];
    SeriesParams params[num + 1];

    // Crear hilos para evaluar cada término de la serie
    for (int i = 0; i <= num; i++) {
        params[i].n = i;
        pthread_create(&threads[i], nullptr, calculateTerm, (void*)&params[i]);
    }

    double sum = 0.0;

    // Unir hilos y sumar resultados
    for (int i = 0; i <= num; i++) {
        pthread_join(threads[i], nullptr);
        sum += params[i].result;
        std::cout << "Término para n=" << i << " es: " << params[i].result << std::endl;
    }

    std::cout << "La sumatoria de la serie es: " << sum << std::endl;

    return 0;
}

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int suma_total = 0;
const int NUM_OPERACIONES = 5;  // Número de sumas a realizar

void sumar(int id) {
    for (int i = 0; i < NUM_OPERACIONES; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        suma_total += 10;
        std::cout << "Hilo " << id << " sumó 10. Total: " << suma_total << std::endl;
    }
}

int main() {
    std::thread hilo1(sumar, 1);
    std::thread hilo2(sumar, 2);

    hilo1.join();
    hilo2.join();

    std::cout << "Suma final consistente: " << suma_total << std::endl;
    return 0;
}



#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool dijo_hola = false;

void decir_hola() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pequeña pausa para evitar consumo excesivo de CPU
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Hola\n";
        dijo_hola = true;
        cv.notify_one(); // Desbloquea al hilo que dice "Adiós"
    }
}

void decir_adios() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return dijo_hola; }); // Espera a que se diga "Hola"
        std::cout << "Adiós\n";
        dijo_hola = false;
    }
}

int main() {
    std::thread hilo1(decir_hola);
    std::thread hilo2(decir_adios);

    hilo1.join();
    hilo2.join();

    return 0;
}





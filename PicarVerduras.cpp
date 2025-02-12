#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int verduras = 0;
const int LIMITE = 10; // Número de verduras a picar

void picar(const std::string& nombre) {
    while (true) {
        std::lock_guard<std::mutex> lock(mtx);
        if (verduras >= LIMITE) break;
        ++verduras;
        std::cout << nombre << " picó la verdura número " << verduras << std::endl;
    }
}

int main() {
    std::thread cocinero1(picar, "Cocinero 1");
    std::thread cocinero2(picar, "Cocinero 2");

    cocinero1.join();
    cocinero2.join();

    std::cout << "Ambos cocineros terminaron con " << verduras << " verduras picadas.\n";
    return 0;
}



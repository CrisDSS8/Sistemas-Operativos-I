#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>  

using namespace std;

// Variables globales para los valores x, y, z
int x, y, z;

// Función para la suma: (x + y)
void suma() {
    int result = x + y;
    cout << "Th1 -> Suma (x + y): " << result << " | ID: " << gettid() << endl;
}

// Función para la resta: (y - z) - (x - z)
void resta() {
    int result = (y - z) - (x - z);
    cout << "Th2 -> Resta ((y - z) - (x - z)): " << result << " | ID: " << gettid() << endl;
}

// Función para la multiplicación: (x + y) + z
void multiplicacion() {
    int result = (x * y) + z;
    cout << "Th3 -> Multiplicación (x * y) + z: " << result << " | ID: " << gettid() << endl;
}

int main() {

    cout << "---CALCULADORA---\n" << endl;

    // Pedir los valores de x, y, z al usuario
    cout << "Introduce el valor de x: ";
    cin >> x;
    cout << "Introduce el valor de y: ";
    cin >> y;
    cout << "Introduce el valor de z: ";
    cin >> z;
    cout << endl;

    // Crear un vector de funciones que se corresponden con las operaciones
    vector<void(*)()> operaciones = {suma, resta, multiplicacion};

    // Crear un vector para almacenar los hilos
    vector<thread> hilos;

    // Usar un bucle para crear y lanzar los hilos
    for (int i = 0; i < operaciones.size(); ++i) {
        hilos.push_back(thread(operaciones[i]));  // Lanzamos cada operación en un hilo
    }

    // Esperar a que todos los hilos terminen su ejecución
    for (auto& hilo : hilos) {
        hilo.join();
    }

    cout << "\nTodos los hilos han terminado." << endl;

    return 0;
}

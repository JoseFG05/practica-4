#include <iostream>
#include <cmath>
using namespace std;

struct Punto {
    double x, y;
};

// Función auxiliar para calcular el determinante
inline double determinante(double a, double b, double c, double d) {
    return a * d - b * c;
}

// 1. Determinar si las líneas se cruzan, son paralelas o no se cruzan
int verificarCruceLineas(Punto p1, Punto p2, Punto p3, Punto p4) {
    double det = determinante(p2.x - p1.x, p3.x - p4.x, p2.y - p1.y, p3.y - p4.y);

    if (det == 0) { // Líneas paralelas
        return 0;
    }

    // Comprobar si se cruzan dentro del segmento
    double t = determinante(p3.x - p1.x, p3.x - p4.x, p3.y - p1.y, p3.y - p4.y) / det;
    double u = determinante(p2.x - p1.x, p3.x - p1.x, p2.y - p1.y, p3.y - p1.y) / det;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        return 1;
    }

    return -1;
}

// 2. Sobrecargar para verificar si son perpendiculares, paralelas o se cruzan
int verificarCruceLineas(Punto p1, Punto p2, Punto p3, Punto p4, bool verificarPerpendicular) {
    double dx1 = p2.x - p1.x;
    double dy1 = p2.y - p1.y;
    double dx2 = p4.x - p3.x;
    double dy2 = p4.y - p3.y;

    if (dx1 * dy2 == dy1 * dx2) { // Paralelas
        return 0;
    }

    if (dx1 * dx2 + dy1 * dy2 == 0) { // Perpendiculares
        return 1;
    }

    return -1; // Se cruzan pero no son perpendiculares
}

// 3. Calcular el ángulo en el cruce de dos líneas
const double PI = 3.141592653589793;

double calcularAngulo(Punto p1, Punto p2, Punto p3, Punto p4, bool enGrados = false) {
    double dx1 = p2.x - p1.x;
    double dy1 = p2.y - p1.y;
    double dx2 = p4.x - p3.x;
    double dy2 = p4.y - p3.y;

    double dotProduct = dx1 * dx2 + dy1 * dy2;
    double magnitudes = sqrt(dx1 * dx1 + dy1 * dy1) * sqrt(dx2 * dx2 + dy2 * dy2);

    double angulo = acos(dotProduct / magnitudes);

    if (enGrados) {
        angulo = angulo * 180 / PI;
    }

    return angulo;
}

// 4. Función que realiza un proceso y un contador de invocaciones
int contadorLlamadas = 0;

void realizarProceso() {
    contadorLlamadas++;
    cout << "Proceso realizado." << endl;
}

int obtenerContadorLlamadas() {
    return contadorLlamadas;
}

int main() {
    // Ejemplo de uso de las funciones
    Punto p1 = {0, 0}, p2 = {4, 4}, p3 = {0, 4}, p4 = {4, 0};

    // 1 y 2
    cout << "Cruce de lineas (1): " << verificarCruceLineas(p1, p2, p3, p4) << endl;
    cout << "Cruce de lineas (2 - Perpendicular): " << verificarCruceLineas(p1, p2, p3, p4, true) << endl;

    // 3
    cout << "Angulo en radianes: " << calcularAngulo(p1, p2, p3, p4) << endl;
    cout << "Angulo en grados: " << calcularAngulo(p1, p2, p3, p4, true) << endl;

    // 4
    realizarProceso();
    realizarProceso();
    cout << "Numero de llamadas a la funcion: " << obtenerContadorLlamadas() << endl;

    return 0;
}
#include <iostream>
#include "camposmatriz.h"

int main() {
    MatrizDinamica<int> dinamica(3, 3);
    MatrizEstatica<int, 3, 3> estatica;
    MatrizDinamica<float> dinamicaFloat(3, 3);
    MatrizEstatica<float, 3, 3> estaticaFloat;
    MatrizBase<int>* resultado1 = nullptr;
    MatrizBase<int>* resultado2 = nullptr;
    
    std::cout << "Programa de Matrices Dinamicas y Estaticas" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "matrices enteras:" << std::endl;
    std::cout << "Generamos la matriz dinamica" << std::endl;
    dinamica.cargarValores();
    dinamica.imprimir();
    
    std::cout << "Generamos la matriz estatica" << std::endl;
    estatica.cargarValores();
    estatica.imprimir();

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "matrices flotantes:" << std::endl;
    std::cout << "Generamos la matriz dinamica" << std::endl;
    dinamicaFloat.cargarValores();
    dinamicaFloat.imprimir();

    std::cout << "Generamos la matriz estatica" << std::endl;
    estaticaFloat.cargarValores();
    estaticaFloat.imprimir();

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Realizamos la suma POLIMORFICA de las dos matrices" << std::endl;
    std::cout << "Primero dinamica.sumar(estatica):" << std::endl;
    resultado1 = dinamica.sumar(estatica);
    
    std::cout << "Ahora estatica.sumar(dinamica):" << std::endl;
    resultado2 = estatica.sumar(dinamica);

    if (resultado1 != nullptr) {
        std::cout << "\nSuma (Dinamica + Estatica):" << std::endl;
        resultado1->imprimir();
    }
    
    if (resultado2 != nullptr) {
        std::cout << "\nSuma (Estatica + Dinamica):" << std::endl;
        resultado2->imprimir();
    }

    MatrizBase<float>* resultadoFloat1 = dinamicaFloat.sumar(estaticaFloat);
    MatrizBase<float>* resultadoFloat2 = estaticaFloat.sumar(dinamicaFloat);
    
    if (resultadoFloat1 != nullptr) {
        std::cout << "\nSuma de Matriz Dinamica Float:" << std::endl;
        resultadoFloat1->imprimir();
    }

    if (resultadoFloat2 != nullptr) {
        std::cout << "\nSuma de Matriz Estatica Float:" << std::endl;
        resultadoFloat2->imprimir();
    }

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "restando las dos matrices (mismo tipo)" << std::endl;
    std::cout << "Primero la dinamica:" << std::endl;
    MatrizDinamica<int> restaDinamica = dinamica - dinamica;
    restaDinamica.imprimir();
    std::cout << "Ahora la estatica:" << std::endl;
    MatrizEstatica<int, 3, 3> restaEstatica = estatica - estatica;
    restaEstatica.imprimir();

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Multiplicando las dos matrices (mismo tipo)" << std::endl;
    std::cout << "Primero la dinamica:" << std::endl;
    MatrizDinamica<int> multDinamica = dinamica * dinamica;
    multDinamica.imprimir();
    std::cout << "Ahora la estatica:" << std::endl;
    MatrizEstatica<int, 3, 3> multEstatica = estatica * estatica;
    multEstatica.imprimir();

    delete resultado1;
    delete resultado2;
    delete resultadoFloat1;
    delete resultadoFloat2;
    
    return 0;
}
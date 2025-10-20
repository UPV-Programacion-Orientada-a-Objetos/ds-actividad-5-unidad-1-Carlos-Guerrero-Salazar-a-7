#ifndef CAMPOSMATRIZ_H
#define CAMPOSMATRIZ_H
#include <iostream>

template <typename T>
class MatrizBase {
protected:
    int _filas;
    int _columnas;

public:
    MatrizBase(int f, int c) : _filas(f), _columnas(c) {}
    virtual ~MatrizBase() {}
    MatrizBase(const MatrizBase<T>& otro) : _filas(otro._filas), _columnas(otro._columnas) {}
    MatrizBase<T>& operator=(const MatrizBase<T>& otro) {
        if (this != &otro) {
            _filas = otro._filas;
            _columnas = otro._columnas;
        }
        return *this;
    }
    
    virtual void cargarValores() = 0;
    virtual void imprimir() const = 0;
    virtual T* operator[](int fila) = 0;
    virtual const T* operator[](int fila) const = 0;
    
    int getFilas() const { return _filas; }
    int getColumnas() const { return _columnas; }
};


template <typename T>
class MatrizDinamica : public MatrizBase<T> {
private:
    T **_datos;

public:
    // Constructor
    MatrizDinamica(int f, int c) : MatrizBase<T>(f, c), _datos(nullptr) {
        _datos = new T*[f];
        for (int i = 0; i < f; ++i) {
            _datos[i] = new T[c];
            for (int j = 0; j < c; ++j) {
                _datos[i][j] = T();
            }
        }
    }

    // Destructor
    ~MatrizDinamica() {
        for (int i = 0; i < this->_filas; ++i) {
            delete[] _datos[i];
        }
        delete[] _datos;
    }

    // Constructor de copia
    MatrizDinamica(const MatrizDinamica<T>& otro) : MatrizBase<T>(otro._filas, otro._columnas) {
        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; ++i) {
            _datos[i] = new T[this->_columnas];
            for (int j = 0; j < this->_columnas; ++j) {
                _datos[i][j] = otro._datos[i][j];
            }
        }
    }

    // Operador de asignación (Regla de los Cinco)
    MatrizDinamica<T>& operator=(const MatrizDinamica<T>& otro) {
        if (this != &otro) {
            // Liberar memoria existente
            for (int i = 0; i < this->_filas; ++i) {
                delete[] _datos[i];
            }
            delete[] _datos;
            
            // Copiar dimensiones
            this->_filas = otro._filas;
            this->_columnas = otro._columnas;
            
            // Asignar nueva memoria y copiar datos
            _datos = new T*[this->_filas];
            for (int i = 0; i < this->_filas; ++i) {
                _datos[i] = new T[this->_columnas];
                for (int j = 0; j < this->_columnas; ++j) {
                    _datos[i][j] = otro._datos[i][j];
                }
            }
        }
        return *this;
    }

    // Operador de suma
    MatrizDinamica<T> operator+(const MatrizDinamica<T>& otra) const {
        MatrizDinamica<T> resultado(this->_filas, this->_columnas);
        for (int i = 0; i < this->_filas; ++i) {
            for (int j = 0; j < this->_columnas; ++j) {
                resultado[i][j] = _datos[i][j] + otra._datos[i][j];
            }
        }
        return resultado;
    }

    // Operador de resta
    MatrizDinamica<T> operator-(const MatrizDinamica<T>& otra) const {
        MatrizDinamica<T> resultado(this->_filas, this->_columnas);
        for (int i = 0; i < this->_filas; ++i) {
            for (int j = 0; j < this->_columnas; ++j) {
                resultado[i][j] = _datos[i][j] - otra._datos[i][j];
            }
        }
        return resultado;
    }

    // Operador de multiplicación matricial CORREGIDO
    MatrizDinamica<T> operator*(const MatrizDinamica<T>& otra) const {
        // Verificar que las dimensiones sean compatibles
        if (this->_columnas != otra._filas) {
            std::cout << "Error: Para multiplicar AxB, las columnas de A deben ser iguales a las filas de B." << std::endl;
            std::cout << "Dimensiones: [" << this->_filas << "x" << this->_columnas << "] * [" 
                      << otra._filas << "x" << otra._columnas << "]" << std::endl;
            return MatrizDinamica<T>(this->_filas, otra._columnas);
        }
        
        // El resultado tiene dimensiones: filas de A x columnas de B
        MatrizDinamica<T> resultado(this->_filas, otra._columnas);
        for (int i = 0; i < this->_filas; ++i) {
            for (int j = 0; j < otra._columnas; ++j) {
                resultado[i][j] = T(); // Inicializar en 0
                for (int k = 0; k < this->_columnas; ++k) {
                    resultado[i][j] += _datos[i][k] * otra._datos[k][j];
                }
            }
        }
        return resultado;
    }
    MatrizDinamica<T>* sumar(const MatrizBase<T>& otra) {
        if (this->_filas != otra.getFilas() || this->_columnas != otra.getColumnas()) {
            std::cout << "Error: Las matrices deben tener las mismas dimensiones para sumar." << std::endl;
            return nullptr;
        }
        
        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(this->_filas, this->_columnas);
        for (int i = 0; i < this->_filas; ++i) {
            for (int j = 0; j < this->_columnas; ++j) {
                (*resultado)[i][j] = _datos[i][j] + otra[i][j];
            }
        }
        return resultado;
    }
    void cargarValores() override {
        for (int i = 0; i < this->_filas; ++i) {
            for (int j = 0; j < this->_columnas; ++j) {
                std::cout << "Ingrese el valor para la posición [" << i << ", " << j << "]: ";
                std::cin >> _datos[i][j];
            }
        }
    }

    void imprimir() const override {
        for (int i = 0; i < this->_filas; ++i) {
            std::cout << "| ";
            for (int j = 0; j < this->_columnas; ++j) {
                std::cout << _datos[i][j];
                if (j < this->_columnas - 1) std::cout << " | ";
            }
            std::cout << " |" << std::endl;
        }
    }

    T* operator[](int fila) override {
        return _datos[fila];
    }

    const T* operator[](int fila) const override {
        return _datos[fila];
    }
};


template <typename T, int M, int N>
class MatrizEstatica : public MatrizBase<T> {
private:
    T _datos[M][N];

public:
    // Constructor
    MatrizEstatica() : MatrizBase<T>(M, N) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                _datos[i][j] = T();
            }
        }
    }

    // Destructor
    ~MatrizEstatica() {}

    // Constructor de copia
    MatrizEstatica(const MatrizEstatica<T, M, N>& otro) : MatrizBase<T>(M, N) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                _datos[i][j] = otro._datos[i][j];
            }
        }
    }

    MatrizEstatica<T, M, N>& operator=(const MatrizEstatica<T, M, N>& otro) {
        if (this != &otro) {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    _datos[i][j] = otro._datos[i][j]; // COPIA, no suma
                }
            }
        }
        return *this;
    }

    // Operador de suma
    MatrizEstatica<T, M, N> operator+(const MatrizEstatica<T, M, N>& otra) const {
        MatrizEstatica<T, M, N> resultado;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                resultado[i][j] = _datos[i][j] + otra._datos[i][j];
            }
        }
        return resultado;
    }

    // Operador de resta
    MatrizEstatica<T, M, N> operator-(const MatrizEstatica<T, M, N>& otra) const {
        MatrizEstatica<T, M, N> resultado;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                resultado[i][j] = _datos[i][j] - otra._datos[i][j];
            }
        }
        return resultado;
    }

    // Operador de multiplicación matricial CORREGIDO
    // Solo funciona para matrices cuadradas MxM
    MatrizEstatica<T, M, N> operator*(const MatrizEstatica<T, N, N>& otra) const {
        MatrizEstatica<T, M, N> resultado;
        
        // Algoritmo de multiplicación matricial: C[i][j] = Σ(A[i][k] * B[k][j])
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                resultado[i][j] = T(); // Inicializar en 0
                for (int k = 0; k < N; ++k) {
                    resultado[i][j] += _datos[i][k] * otra._datos[k][j];
                }
            }
        }
        return resultado;
    }

    void cargarValores() override {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cout << "Ingrese el valor para la posición [" << i << ", " << j << "]: ";
                std::cin >> _datos[i][j];
            }
        }
    }

    MatrizBase<T>* sumar(const MatrizBase<T>& otra) {
        if (this->_filas != otra.getFilas() || this->_columnas != otra.getColumnas()) {
            std::cout << "Error: Las matrices deben tener las mismas dimensiones para sumar." << std::endl;
            return nullptr;
        }
        
        MatrizEstatica<T, M, N>* resultado = new MatrizEstatica<T, M, N>();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                (*resultado)[i][j] = _datos[i][j] + otra[i][j];
            }
        }
        return resultado;
    }

    void imprimir() const override {
        for (int i = 0; i < M; ++i) {
            std::cout << "| ";
            for (int j = 0; j < N; ++j) {
                std::cout << _datos[i][j];
                if (j < N - 1) std::cout << " | ";
            }
            std::cout << " |" << std::endl;
        }
    }

    T* operator[](int fila) override {
        return _datos[fila];
    }

    const T* operator[](int fila) const override {
        return _datos[fila];
    }
};

#endif
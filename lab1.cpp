using namespace std;

#include <iostream>
#include <random>
template <typename T>

class Vector {

private:
    T* data;       // Указатель на данные (координаты вектора)
    size_t _size;  // Размерность (количество координат)
public:
    size_t get_size() const 
    {
        return _size;
    }

    
    Vector(size_t size, T value): _size(size)
    {
        if (_size <= 0)
        {
            throw std::invalid_argument("Размерность вектора должна быть больше нуля");
        }
        data = new T[_size];
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = value;
        }
    }

    Vector(size_t size, T min, T max): _size(size)
    {
        data = new T[_size];
        /*Создание генератора случайных чисел
         Использует аппаратный генератор
         Инициализирует генератор*/ 
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<T> dist(min, max); 

        for (size_t i = 0; i < size; ++i) {
            data[i] = dist(gen); 
        }
    }

};



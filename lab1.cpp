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

    Vector(const Vector& other) : _size(other._size)
    {
        data = new T[_size]
            for (size_t i = 0, i < _size, ++i)
            {
                data[i] = other.data[i];
            }
    }

    ~Vector() 
    {
        delete[] data;
    }

    T& operator[] (size_t index) const
    {
        if (index >= _size || index < _size) {
            throw std::out_of_range("Индекс выходит за пределы вектора");
        }
        return data[index];  
    }

    Vector operator+ (const Vector& other) const
    {
        if (_size != other._size)
        {
            throw std::invalid_argument("Вектора должны быть одинаковой размерности");
        }
        Vector result(_size, 0);
        for (size_t i = 0, i < _size, ++i)
        {
            result[i] = data[i] + other.data[i];
        }
        return result;
    }

    Vector operator- (const Vector& other) const
    {
        if (_size != other._size)
        {
            throw std::invalid_argument("Вектора должны быть одинаковой размерности");
        }
        Vector result(_size, 0);
        for (size_t i = 0, i < _size, ++i)
        {
            result[i] = data[i] - other.data[i];
        }
        return result;
    }

    T operator* (const Vector& other) const
    {
        if (_size != other._size)
        {
            throw std::invalid_argument("Вектора должны быть одинаковой размерности");
        }
        T result = 0;
        for (size_t i = 0, i < _size, ++i)
        {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector operator* (T val) const
    {
        Vector result(_size, 0);
        for (size_t i = 0, i < _size, ++i)
        {
            result[i] = val * data[i];
        }
        return result;
    }

    friend Vector operator*(T val, const Vector& other) //коммутативность для умножения вектора на скаляр
    {
        return other * val;  
    }

    Vector operator/ (T val) const
    {
        if (val == 0) 
        {
            throw std::invalid_argument("Деление на ноль невозможно");
        }

        Vector result(_size, 0);
        for (size_t i = 0, i < _size, ++i)
        {
            result[i] = data[i]/val;
        }
        return result;
    }
};



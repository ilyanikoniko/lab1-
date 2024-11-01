using namespace std;

#include <iostream>
#include <random>
template <typename T>
class Vector {

private:
    T* _data;          
    size_t _size;      
    size_t _capacity;
public:
    size_t get_size() const 
    {
        return _size;
    }

    size_t get_capacity() const
    {
        return _capacity;
    }

    Vector(): size(0), capacity(1) 
    {  
        data = new T[capacity];   
    }

    Vector(size_t size, const T& value): _size(size), _capacity(size)
    {
        data = new T[_capacity];
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = value;
        }
    }

    Vector(size_t size, T min, T max): _size(size), _capacity(_size)
    {
        data = new T[_capacity];
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



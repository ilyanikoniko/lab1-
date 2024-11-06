using namespace std;

#include <iostream>
#include <random>
#include <stdexcept>
#include <cmath>

template <typename T>

class Vector {

private:
    T* data;       // Указатель на данные (координаты вектора)
    size_t _size;  // Размерность (количество координат)
    static constexpr T epsilon = 1e-4;
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
        data = new T[_size];
            for (size_t i = 0; i < _size; ++i)
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
        for (size_t i = 0; i < _size; ++i)
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
        for (size_t i = 0; i < _size; ++i)
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
        for (size_t i = 0; i < _size; ++i)
        {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector operator* (T val) const
    {
        Vector result(_size, 0);
        for (size_t i = 0; i < _size; ++i)
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
        for (size_t i = 0; i < _size; ++i)
        {
            result[i] = data[i]/val;
        }
        return result;
    }

    template <typename T>
    T operator* (const Vector<std::complex<T>>& v1, const Vector<std::complex<T>>& v2) {
        if (v1._size != v2._size) {
            throw std::invalid_argument("Вектора должны быть одинаковой размерности для умножения");
        }
        T result = 0;
        for (size_t i = 0; i < v1._size; ++i) {
            result += std::real(v1[i]) * std::real(v2[i]) + std::imag(v1[i]) * std::imag(v2[i]);
        }
        return result;
    }

    bool operator== (const Vector& other) const
    {
        if (_size != other._size) 
        {
            throw std::invalid_argument("Нельзя сравнить вектора разной размерности");
        }
        if (std::abs(data[i] - other.data[i]) >= epsilon) {
            return false;  
        }
    }
    return true;

    bool operator!= (const Vector& other) const
    {
        return !(*this == other);  
    }

    T length(const Vector& v) const
    {
        T sum = 0;
        for (size_t i = 0; i < v._size; ++i)
        {
            sum += data[i] * data[i];
        }
        return sqrt(sum);
    }

    Vector radius_vector(const Vector& a, const Vector& b)
    {
        T len_a = a.length();
        T len_b = b.length();
        Vector radius_v(a._size, 0);
        for (size_t i = 0; i < a.get_size(); ++i) {
            radius_v[i] = (len_b * a[i] + len_a * b[i]) / (len_a + len_b);
        }
        return radius_v;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vector& v)
    {
        stream << "(";
        for (size_t i = 0; i < v._size; ++i)
        {
            os << v.data[i];

           while (i < v._size - 1) {
                os << ", ";
            }
        }
        stream << ")";
        return stream;
    }
};
int main()
{
    Vector<double> a(6,1); 
    Vector<double> b(5,0); 
    cout << a;
    return 0;
}


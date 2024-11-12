using namespace std;

#include <iostream>
#include <random>
#include <stdexcept>
#include <cmath>
#include <complex>
#include <windows.h>
#include <typeinfo>
template <typename T>

class Vector {

private:
    T* data;       // Указатель на данные (координаты вектора)
    size_t _size;  // Размерность (количество координат)
    static constexpr double epsilon = 1e-6;

public:

    size_t get_size() const
    {
        return _size;
    }

    Vector(size_t size, T value) : _size(size)
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

    Vector(size_t size, T min, T max) : _size(size)
    {
        data = new T[_size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = random(min, max);
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
        if (index >= _size || index < 0) {
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

    Vector operator* (const T val) const
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

    Vector operator/ (const T val) const
    {
        if (val == 0)
        {
            throw std::invalid_argument("Деление на ноль невозможно");
        }

        Vector result(_size, 0);
        for (size_t i = 0; i < _size; ++i)
        {
            result[i] = data[i] / val;
        }
        return result;
    }


    bool operator== (const Vector& other) const
    {
        if (_size != other._size)
        {
            throw std::invalid_argument("Нельзя сравнить вектора разной размерности");
        }
        for (size_t i = 0; i < _size; ++i) {
            if (abs(data[i] - other.data[i]) > epsilon)
            {
                return false;
            }
        }
        return true;
    }

    bool operator== (const Vector<complex<T>>& other) const
    {
        if (_size != other._size)
        {
            throw std::invalid_argument("Нельзя сравнить вектора разной размерности");
        }
        for (size_t i = 0; i < _size; ++i) {
            if (abs(real(data[i]) - real(other.data[i])) > epsilon || abs(imag(data[i]) - imag(other.data[i])) > epsilon)
            {
                return false;
            }
        }
        return true;
    }

    bool operator!= (const Vector& other) const
    {
        return !(*this == other);
    }

    T length() const
    {
        T sum = 0;
        for (size_t i = 0; i < _size; ++i)
        {
            sum += data[i] * data[i];
        }
        return sqrt(sum);
    }

    Vector& operator= (const Vector& other)
    {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        _size = other._size;
        data = new T[_size];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Vector<T> radius_vector(const Vector& a, const Vector& b)
    {
        T len_a = a.length();
        T len_b = b.length();
        Vector radius_v(a._size, 0);
        for (size_t i = 0; i < a._size; ++i) {
            radius_v[i] = (len_b * a[i] + len_a * b[i]) / (len_a + len_b);
        }
        return radius_v;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vector& v)
    {
        stream << "(";
        for (size_t i = 0; i < v._size; ++i)
        {
            stream << v.data[i];

            if (i < v._size - 1) {
                stream << ", ";
            }
        }
        stream << ")";
        return stream;
    }

    std::complex<double> random(complex<double> min, complex<double> max)
    {
        string str3 = "class std::complex<double>";
        if (typeid(min).name() == str3)
        {
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_real_distribution<> dist(min.real(), max.real());
            std::complex<double> compdouble(dist(rand), dist(rand));
            return compdouble;
        }
    }

    std::complex<float> random(complex<float> min, complex<float> max)
    {
        string str2 = "class std::complex<float>";
        if (typeid(min).name() == str2)
        {
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_real_distribution<> dist(min.real(), max.real());
            std::complex<float> compfloat(dist(rand), dist(rand));
            return compfloat;
        }
    }

    template <typename T>
    T random(T min, T max)
    {
        string str1 = "float";
        string str4 = "int";
        string str5 = "double";
        if (typeid(min).name() == str1)
        {
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_real_distribution<> dist(min, max);
            float num = dist(rand);
            return num;
        }

        else if (typeid(min).name() == str4)
        {
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_int_distribution<> dist(min, max);
            int num = dist(rand);
            return num;
        }

        else if (typeid(min).name() == str5)
        {
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_real_distribution<> dist(min, max);
            double num = dist(rand);
            return num;
        }
    }

};

template <typename T>
T operator* (const Vector<complex<T>>& v1, const Vector<complex<T>>& v2)
{
    if (v1._size != v2._size) {
        throw std::invalid_argument("Вектора должны быть одинаковой размерности для умножения");
    }
    T result = 0;
    for (size_t i = 0; i < v1._size; ++i) {
        result += conj(v1[i]) * v2[i];
       
    }
    return result;
}

int main()
{

    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    try {
        Vector<int> a(2, 1);
        Vector<int> b(2, 1);
        Vector<int> c(3, 1);
        complex<double> val1(3.5, 4.2);
        complex<double> val2(3.8, 4.8);
        complex<double> val3(3.5, 4.2);
        complex<double> val4(3.8, 4.8);
        Vector<complex<double>> com1(2, val1);
        Vector<complex<double>> com2(2, val3);
        bool ert = (com1 == com2);
        cout << com1 << endl;
        cout << com2 << endl;
        cout << ert;
        cout << com1 * com2;
    }
    catch (const std::out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl; // Выводим сообщение об ошибке
    }
    catch (const std::invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl; // Выводим сообщение об ошибке для второго случая
    }
    return 0;
}
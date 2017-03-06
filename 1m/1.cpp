/*
 * 1_5.  Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.
 */

#include <iostream>
#include <cassert>

using namespace std;


class IntVector {
public:
    IntVector(size_t initialCapacity = 32);
    IntVector(const IntVector& other);
    ~IntVector();

    void append(int item);
    void remove(size_t index);
    void pop();

    int operator[](size_t index) const;
    int& operator[](size_t index);

    size_t getLength() const;

private:
    size_t _capacity = 0;
    size_t _length = 0;
    int* _data = nullptr;
};

IntVector::IntVector(size_t initialCapacity) :
        _capacity(initialCapacity),
        _length(0),
        _data(new int[_capacity])
{
}

IntVector::IntVector(const IntVector &other) {
    _capacity = other._capacity;
    _length = other._length;
    if (_data != nullptr) {
        delete[] _data;
    }
    _data = new int[_capacity];
    memcpy(_data, other._data, _length);
}

IntVector::~IntVector() {
    delete[] _data;
}

void IntVector::append(int item) {
    if (_length == _capacity) {
        _capacity += 32;
        _data = (int*) realloc(_data, _capacity);
    }
    _data[_length++] = item;
}

void IntVector::remove(size_t index) {
    for (size_t i = index + 1; i < _length; i++) {
        _data[i - 1] = _data[i];
    }
    _length--;
}

void IntVector::pop() {
    _length--;
}

int IntVector::operator[](size_t index) const {
    assert(index < _length);
    return _data[index];
}

int& IntVector::operator[](size_t index) {
    assert(index < _length);
    return _data[index];
}

size_t IntVector::getLength() const {
    return _length;
}


IntVector findSquares(int count) {
    IntVector result;
    int accumulator = 0;
    for (int i = 0; i < count; i++) {
        int oddNumber = 1 + i * 2;
        accumulator += oddNumber;
        result.append(accumulator);
    }
    return result;
}


int main() {
    int n;
    cin >> n;

    IntVector squares = findSquares(n);

    for (size_t i = 0; i < squares.getLength(); i++) {
        cout << squares[i] << ' ';
    }

    return 0;
}
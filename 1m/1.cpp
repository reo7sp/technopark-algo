/*
 * 1_5.  Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.
 */

#include <iostream>
#include <cassert>

using namespace std;


class IntVector {
public:
    IntVector(size_t initialCapacity = 32);
    ~IntVector();

    void append(int item);
    void remove(size_t index);

    int operator[](size_t index) const;
    int& operator[](size_t index);

    size_t getLength() const;

private:
    size_t _capacity;
    size_t _length;
    int* _data;
};

IntVector::IntVector(size_t initialCapacity) :
        _capacity(initialCapacity),
        _length(0),
        _data(new int[_capacity])
{
}

IntVector::~IntVector() {
    delete[] _data;
}

size_t IntVector::getLength() const {
    return _length;
}

int IntVector::operator[](size_t index) const {
    assert(index < _length);
    return _data[index];
}

int& IntVector::operator[](size_t index) {
    assert(index < _length);
    return _data[index];
}

void IntVector::append(int item) {
    if (_length == _capacity) {
        _data = (int*) realloc(_data, _capacity += 32);
    }
    _data[_length++] = item;
}

void IntVector::remove(size_t index) {
    for (size_t i = index + 1; i < _length; i++) {
        _data[i - 1] = _data[i];
    }
    _length--;
}


IntVector findSquares(int count) {
}


int main() {
    int n;
    cin >> n;

    return 0;
}
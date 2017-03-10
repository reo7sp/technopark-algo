/*
 * 1_*.  Найти все простые числа в диапазоне [2..n] за O(n).
 */

#include <iostream>
#include <cassert>
#include <memory.h>

using namespace std;


class IntVector {
public:
    explicit IntVector(size_t initialCapacity = 32);
    IntVector(const IntVector& other);
    ~IntVector();

    void append(int item);
    void remove(size_t index);
    void pop();

    int operator[](size_t index) const;
    int& operator[](size_t index);

    size_t getLength() const;

private:
    void _grow();

    size_t _capacity = 0;
    size_t _length = 0;
    int* _data = nullptr;
};

IntVector::IntVector(size_t initialCapacity) :
        _capacity(initialCapacity),
        _length(0),
        _data((int*) malloc(sizeof(int) * _capacity))
{
}

IntVector::IntVector(const IntVector &other) {
    _capacity = other._capacity;
    _length = other._length;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (int*) malloc(sizeof(int) * _capacity);
    memcpy(_data, other._data, sizeof(int) * _length);
}

IntVector::~IntVector() {
    free(_data);
}

void IntVector::append(int item) {
    if (_length == _capacity) {
        _grow();
    }
    _data[_length++] = item;
}

void IntVector::remove(size_t index) {
    assert(index < _length);
    for (size_t i = index + 1; i < _length; i++) {
        _data[i - 1] = _data[i];
    }
    _length--;
}

void IntVector::pop() {
    assert(_length > 0);
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

void IntVector::_grow() {
    const size_t kGrowStep = 32;
    _capacity += kGrowStep;
    _data = (int*) realloc(_data, sizeof(int) * _capacity);
}


IntVector findPrimes(size_t count) {
    size_t primesCount = 0;
    bool* crossedOut = (bool*) calloc(count + 1, sizeof(bool));
    for (size_t prime = 2; prime <= count; prime++) {
        if (crossedOut[prime]) {
            continue;
        }
        primesCount++;
        for (size_t k = 2; k * prime <= count; k++) {
            crossedOut[k * prime] = true;
        }
    }

    IntVector result(primesCount);
    for (int prime = 2; prime <= count; prime++) {
        if (!crossedOut[prime]) {
            result.append(prime);
        }
    }

    free(crossedOut);
    
    return result;
}


int main() {
    size_t n;
    cin >> n;

    IntVector primes = findPrimes(n);

    for (size_t i = 0; i < primes.getLength(); i++) {
        cout << primes[i] << ' ';
    }

    return 0;
}
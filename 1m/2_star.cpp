/*
 * В каждой задаче, где начальными данными является массив вначале вводится количество элементов, а затем и сами элементы массива.
 */

/*
 * 2_*.  Дан массив целых чисел A[0..n). Массив произвольным образом заполнен натуральными числами из диапазона [0..n - 1). Одно или несколько значений в массиве может повторяться. Необходимо найти любой повтор за O(n), памяти O(1). Исходный массив хранить можно, модифицировать нельзя. n ≤ 10000.
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


IntVector findDublicates(const IntVector& a) {
}


int main() {
    size_t n;
    cin >> n;

    IntVector input(n);
    for (size_t i = 0; i < n; i++) {
        int item;
        cin >> item;
        input.append(item);
    }

    IntVector output = findDublicates(input);
    for (size_t i = 0; i < output.getLength(); i++) {
        cout << output[i] << ' ';
    }

    return 0;
}

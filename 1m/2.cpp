/*
 * В каждой задаче, где начальными данными является массив вначале вводится количество элементов, а затем и сами элементы массива.
 */

/*
 * 2_3.  Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.
 * Указание.  Обходите массив B от конца к началу.
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


size_t countPairsThatSumsToK(const IntVector& a, const IntVector& b, int k) {
    size_t answer = 0;

    size_t indexA = 0;
    size_t indexB = b.getLength() - 1;
    while (true) {
        int exampleK = a[indexA] + b[indexB];
        if (exampleK > k) {
            if (indexB == 0) {
                break;
            }
            indexB--;
        } else if (exampleK < k) {
            if (indexA == a.getLength() - 1) {
                break;
            }
            indexA++;
        } else {
            answer++;
            if (indexB == 0) {
                break;
            }
            indexB--;
        }
    }

    return answer;
}


int main() {
    size_t n, m;
    IntVector a, b;
    int k;

    cin >> n;
    for (size_t i = 0; i < n; i++) {
        int item;
        cin >> item;
        a.append(item);
    }
    cin >> m;
    for (size_t i = 0; i < m; i++) {
        int item;
        cin >> item;
        b.append(item);
    }
    cin >> k;

    cout << countPairsThatSumsToK(a, b, k);

    return 0;
}

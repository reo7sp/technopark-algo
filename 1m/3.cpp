/*
 * 3_1.  Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
 * Формат входных данных.
 * В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.
 */

#include <iostream>
#include <cassert>
#include <memory.h>

using namespace std;


template<typename T>
class MyVector {
public:
    explicit MyVector(size_t initialCapacity = 32);
    MyVector(const MyVector& other);
    ~MyVector();

    void append(T item);
    void remove(size_t index);
    void pop();

    T operator[](size_t index) const;
    T& operator[](size_t index);

    size_t getLength() const;

private:
    void _grow();

    size_t _capacity = 0;
    size_t _length = 0;
    T* _data = nullptr;
};

template<typename T>
MyVector<T>::MyVector(size_t initialCapacity) :
        _capacity(initialCapacity),
        _length(0),
        _data((T*) malloc(sizeof(T) * _capacity))
{
}

template<typename T>
MyVector<T>::MyVector(const MyVector &other) {
    _capacity = other._capacity;
    _length = other._length;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (T*) malloc(sizeof(T) * _capacity);
    memcpy(_data, other._data, sizeof(T) * _length);
}

template<typename T>
MyVector<T>::~MyVector() {
    free(_data);
}

template<typename T>
void MyVector<T>::append(T item) {
    if (_length == _capacity) {
        _grow();
    }
    _data[_length++] = item;
}

template<typename T>
void MyVector<T>::remove(size_t index) {
    assert(index < _length);
    for (size_t i = index + 1; i < _length; i++) {
        _data[i - 1] = _data[i];
    }
    _length--;
}

template<typename T>
void MyVector<T>::pop() {
    assert(_length > 0);
    _length--;
}

template<typename T>
T MyVector<T>::operator[](size_t index) const {
    assert(index < _length);
    return _data[index];
}

template<typename T>
T& MyVector<T>::operator[](size_t index) {
    assert(index < _length);
    return _data[index];
}

template<typename T>
size_t MyVector<T>::getLength() const {
    return _length;
}

template<typename T>
void MyVector<T>::_grow() {
    _capacity *= 2;
    _data = (T*) realloc(_data, sizeof(T) * _capacity);
}


size_t findIndex(const MyVector<int>& src, int item) {
    if (src[src.getLength() - 1] < item) {
        return src.getLength();
    }
    if (src[0] >= item) {
        return 0;
    }

    size_t left = 0;
    size_t right = src.getLength() - 1;

    // find range in between 2^(ceil(log2(item))) and 2^(ceil(log2(item)) + 1)
    for (size_t i = 1; i < src.getLength(); i <<= 1) {
        if (src[i] < item) {
            left = i;
        } else {
            right = i;
            break;
        }
    }

    // find item's index using binary search in the sub range
    while (left < right) {
        size_t mid = (left + right) / 2;
        if (src[mid] < item) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

MyVector<size_t> findIndex(const MyVector<int>& src, const MyVector<int>& items) {
    MyVector<size_t> result(items.getLength());
    for (size_t i = 0; i < items.getLength(); i++) {
        result.append(findIndex(src, items[i]));
    }
    return result;
}


int main() {
    size_t n, m;
    cin >> n;
    cin >> m;

    MyVector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        int item;
        cin >> item;
        a.append(item);
    }
    MyVector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        int item;
        cin >> item;
        b.append(item);
    }

    MyVector<size_t> result = findIndex(a, b);
    for (size_t i = 0; i < result.getLength(); i++) {
        cout << result[i] << ' ';
    }

    return 0;
}

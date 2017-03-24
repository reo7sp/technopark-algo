/*
 * 7_2. Заявки на переговоры.
В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок  ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел  —  начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число  — максимальное число заявок.
 */

#include <iostream>
#include <cassert>
#include <memory.h>
#include <type_traits>

using namespace std;


typedef long Time;


class TimePiece {
public:
    TimePiece(Time start, Time end);
    TimePiece(const TimePiece& other);
    ~TimePiece();

    Time getStart() const;
    Time getEnd() const;
    Time getDuration() const;

    bool operator==(const TimePiece& other) const;
    bool operator!=(const TimePiece& other) const;

protected:
    TimePiece() {}

    Time _end = 0;
    Time _start = 0;
};

TimePiece::TimePiece(Time start, Time end) : _start(start), _end(end) {
    assert(_start <= _end);
}

TimePiece::TimePiece(const TimePiece& other) {
    _start = other._start;
    _end = other._end;
}

TimePiece::~TimePiece() {
}

Time TimePiece::getStart() const {
    return _start;
}

Time TimePiece::getEnd() const {
    return _end;
}

Time TimePiece::getDuration() const {
    return _end - _start;
}

bool TimePiece::operator==(const TimePiece& other) const {
    return _start == other._start && _end == other._end;
}

bool TimePiece::operator!=(const TimePiece& other) const {
    return !(*this == other);
}


class TimePieceComparableByEnd : public TimePiece {
public:
    TimePieceComparableByEnd(Time start, Time end) : TimePiece(start, end) {}

    bool operator<(const TimePiece& other) const;
    bool operator>(const TimePiece& other) const;
};

bool TimePieceComparableByEnd::operator<(const TimePiece& other) const {
    return getEnd() < other.getEnd();
}

bool TimePieceComparableByEnd::operator>(const TimePiece& other) const {
    return getEnd() > other.getEnd();
}


template<typename T>
class MyVector {
public:
    explicit MyVector(size_t initialCapacity = 32);
    MyVector(const MyVector& other);
    ~MyVector();

    void append(T item);
    void remove(size_t index);
    void pop();
    void sort(); // sort order is ascending

    T operator[](size_t index) const;
    T& operator[](size_t index);

    size_t getLength() const;

private:
    void _grow();
    void _qsort(size_t left, size_t right);

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
void MyVector<T>::sort() {
    if (_length > 0) {
        _qsort(0, _length - 1);
    }
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
    const size_t kGrowFactor = 2;
    _capacity *= kGrowFactor;
    _data = (T*) realloc(_data, sizeof(T) * _capacity);
}

template<typename T>
void MyVector<T>::_qsort(size_t left, size_t right) {
    T pivot = _data[(left + right) / 2];
    size_t i = left;
    size_t j = right;
    while (i <= j) {
        while (i < _length && _data[i] < pivot) {
            i++;
        }
        while (j < _length && _data[j] > pivot) {
            j--;
        }
        if (i >= _length || j >= _length) {
            break;
        }
        if (i <= j) {
            T temp = _data[i];
            _data[i] = _data[j];
            _data[j] = temp;
            i++;
            j--;
        }
    }
    if (j > _length) {
        j = 0;
    }
    if (left < j) {
        _qsort(left, j);
    }
    if (i < right) {
        _qsort(i, right);
    }
}


size_t countMaxDurations(MyVector<TimePieceComparableByEnd> container) {
    if (container.getLength() == 0) {
        return 0;
    }

    container.sort(); // sort by ends

    size_t result = 1;
    Time lastEndTime = container[0].getEnd();

    for (size_t i = 1; i < container.getLength(); i++) {
        const TimePieceComparableByEnd& item = container[i];
        if (lastEndTime <= item.getStart()) { // use next item as soon as it doesn't overlap
            result++;
            lastEndTime = item.getEnd();
        }
    }

    return result;
}

int main() {
    MyVector<TimePieceComparableByEnd> container;

    Time startTime, endTime;
    while (cin >> startTime && cin >> endTime) {
        container.append(TimePieceComparableByEnd(startTime, endTime));
    }

    cout << countMaxDurations(container);

    return 0;
}

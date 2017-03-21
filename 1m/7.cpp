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
    TimePieceComparableByEnd(const TimePieceComparableByEnd& other) : TimePiece(other._start, other._end) {}

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
    void sort();

    T operator[](size_t index) const;
    T& operator[](size_t index);

    size_t getLength() const;

private:
    void _grow();

    void _qsort(size_t left, size_t right);
    size_t _qsort_partition(size_t left, size_t right);

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
    const size_t kGrowStep = 32;
    _capacity += kGrowStep;
    _data = (T*) realloc(_data, sizeof(T) * _capacity);
}

template<typename T>
void MyVector<T>::_qsort(size_t left, size_t right) {
    if (left < right) {
        size_t middle = _qsort_partition(left, right);
        _qsort(left, middle - 1);
        _qsort(middle + 1, right);
    }
}

template<typename T>
size_t MyVector<T>::_qsort_partition(size_t left, size_t right) {
    T exampleItem = _data[(left + right) / 2];
    size_t i = left;
    size_t j = right;
    while (i < j) {
        while (_data[i] < exampleItem) {
            i++;
        }
        while (_data[j] > exampleItem) {
            j--;
        }
        if (i < j) {
            T temp = _data[i];
            _data[i] = _data[j];
            _data[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}


template<typename T>
Time findMinTime(const MyVector<T>& container) {
    static_assert(std::is_base_of<TimePiece, T>::value, "Template type must subclass of TimePiece");

    Time min = container[0].getStart();
    for (size_t i = 0; i < container.getLength(); i++) {
        if (container[i].getStart() < min) {
            min = container[i].getStart();
        }
    }
    return min;
}

template<typename T>
Time findMaxTime(const MyVector<T>& container) {
    static_assert(std::is_base_of<TimePiece, T>::value, "Template type must subclass of TimePiece");

    Time max = container[0].getEnd();
    for (size_t i = 0; i < container.getLength(); i++) {
        if (max < container[i].getEnd()) {
            max = container[i].getEnd();
        }
    }
    return max;
}

size_t countMaxDurations(MyVector<TimePieceComparableByEnd> container) {
    container.sort();

    size_t result = 0;

    Time minTime = findMinTime(container);
    Time maxTime = findMaxTime(container);
    size_t scheduleSize = (size_t) (maxTime - minTime + 1);
    bool* schedule = new bool[scheduleSize];
    memset(schedule, false, scheduleSize);

    for (size_t i = 0; i < container.getLength(); i++) {
        const TimePieceComparableByEnd& item = container[i];

        bool canSchedule = true;
        for (Time time = item.getStart(); time < item.getEnd(); time++) {
            if (schedule[minTime + time]) {
                canSchedule = false;
                break;
            }
        }
        if (canSchedule) {
            result++;
            for (Time time = item.getStart(); time < item.getEnd(); time++) {
                schedule[minTime + time] = true;
            }
        }
    }

    delete[] schedule;

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

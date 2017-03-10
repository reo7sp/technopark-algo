/*
 * Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 */

/*
 * 4_2.  Реализовать дек с динамическим зацикленным буфером.
 */

#include <iostream>
#include <cassert>
#include <memory.h>

using namespace std;


class Deque {
public:
    Deque(size_t initialCapacity = 32);
    Deque(const Deque& other);
    ~Deque();

    void pushFront(int item);
    void pushBack(int item);
    int popFront();
    int popBack();

private:
    void _grow();

    size_t _getPreviousIndex(size_t current) const;
    size_t _getNextIndex(size_t current) const;

    int* _data = nullptr;
    size_t _capacity = 0;
    size_t _headIndex = 0;
    size_t _tailIndex = 0;
};

Deque::Deque(size_t initialCapacity) :
    _capacity(initialCapacity),
    _data((int*) malloc(sizeof(int) * initialCapacity)),
    _headIndex(0),
    _tailIndex(0)
{
}

Deque::Deque(const Deque& other) {
    _capacity = other._capacity;
    _headIndex = other._headIndex;
    _tailIndex = other._tailIndex;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (int*) malloc(sizeof(int) * _capacity);
    memcpy(_data, other._data, sizeof(int) * _capacity);
}

Deque::~Deque() {
    free(_data);
}

void Deque::pushFront(int item) {
    size_t newIndex = _getPreviousIndex(_headIndex);
    if (newIndex == _tailIndex) {
        _grow();
        newIndex = _getPreviousIndex(_headIndex);
    }
    _headIndex = newIndex;
    _data[_headIndex] = item;
}

void Deque::pushBack(int item) {
    size_t newIndex = _getNextIndex(_tailIndex);
    if (newIndex == _headIndex) {
        _grow();
        newIndex = _getNextIndex(_tailIndex);
    }
    _data[_tailIndex] = item;
    _tailIndex = newIndex;
}

int Deque::popFront() {
    if (_headIndex == _tailIndex) {
        return -1;
    }
    int item = _data[_headIndex];
    _headIndex = _getNextIndex(_headIndex);
    return item;
}

int Deque::popBack() {
    if (_headIndex == _tailIndex) {
        return -1;
    }
    _tailIndex = _getPreviousIndex(_tailIndex);
    int item = _data[_tailIndex];
    return item;
}

void Deque::_grow() {
    const size_t kGrowStep = 32;
    _capacity += kGrowStep;
    _data = (int*) realloc(_data, sizeof(int) * _capacity);
    if (_tailIndex < _headIndex) {
        memmove(_data + _headIndex + kGrowStep, _data + _headIndex, sizeof(int) * (_capacity - _headIndex));
        _headIndex += kGrowStep;
    }
}

size_t Deque::_getPreviousIndex(size_t current) const {
    if (current != 0) {
        return current - 1;
    } else {
        return _capacity - 1;
    }
}

size_t Deque::_getNextIndex(size_t current) const {
    if (current + 1 != _capacity) {
        return current + 1;
    } else {
        return 0;
    }
}


bool processCommand(Deque& queue, int mode, int value) {
    switch (mode) {
        case 1:
            queue.pushFront(value);
            return true;

        case 2:
            return queue.popFront() == value;

        case 3:
            queue.pushBack(value);
            return true;

        case 4:
            return queue.popBack() == value;

        default:
            return false;
    }
}


int main() {
    Deque queue;

    size_t n;
    cin >> n;

    bool answer = true;
    for (size_t i = 0; i < n; i++) {
        int mode, value;
        cin >> mode;
        cin >> value;

        if (!processCommand(queue, mode, value)) {
            answer = false;
            break;
        }
    }
    cout << (answer ? "YES" : "NO");

    return 0;
}

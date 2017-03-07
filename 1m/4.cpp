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
 * 4_1.  Реализовать очередь с динамическим зацикленным буфером.
 */

#include <iostream>
#include <cassert>
#include <memory.h>

using namespace std;


class Queue {
public:
    Queue(size_t initialCapacity = 1);
    Queue(const Queue& other);
    ~Queue();

    void pushBack(int item);
    int popFront();

private:
    void _grow();

    size_t _getNextIndex(size_t current);

    int* _data = nullptr;
    size_t _capacity = 0;
    size_t _headIndex = 0;
    size_t _tailIndex = 0;
};

Queue::Queue(size_t initialCapacity) :
    _capacity(initialCapacity),
    _data((int*) malloc(sizeof(int) * initialCapacity)),
    _headIndex(0),
    _tailIndex(0)
{
}

Queue::Queue(const Queue& other) {
    _capacity = other._capacity;
    _headIndex = other._headIndex;
    _tailIndex = other._tailIndex;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (int*) malloc(sizeof(int) * _capacity);
    memcpy(_data, other._data, sizeof(int) * _capacity);
}

Queue::~Queue() {
    free(_data);
}

void Queue::pushBack(int item) {
    size_t nextTailIndex = _getNextIndex(_tailIndex);
    if (nextTailIndex == _headIndex) {
        _grow();
        nextTailIndex = _getNextIndex(_tailIndex);
    }
    _data[_tailIndex] = item;
    _tailIndex = nextTailIndex;
}

int Queue::popFront() {
    if (_headIndex == _tailIndex) {
        return -1;
    }
    int item = _data[_headIndex];
    _headIndex = _getNextIndex(_headIndex);
    return item;
}

void Queue::_grow() {
    const size_t kGrowStep = 32;
    _capacity += kGrowStep;
    _data = (int*) realloc(_data, sizeof(int) * _capacity);
    if (_tailIndex < _headIndex) {
        memcpy(_data + _headIndex + kGrowStep, _data + _headIndex, sizeof(int) * kGrowStep);
        _headIndex += kGrowStep;
    }
}

size_t Queue::_getNextIndex(size_t current) {
    if (current + 1 != _capacity) {
        return current + 1;
    } else {
        return 0;
    }
}


bool processCommand(Queue& queue, int mode, int value) {
    switch (mode) {
        case 2:
            return queue.popFront() == value;

        case 3:
            queue.pushBack(value);
            return true;

        default:
            return false;
    }
}


int main() {
    Queue queue;

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

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

using namespace std;


typedef unsigned int Time;


class TimePiece {
public:
    TimePiece(Time start, Time end);
    TimePiece(const TimePiece& other);
    ~TimePiece();

    Time getStart() const;
    Time getEnd() const;
    Time getDuration() const;

private:
    Time _start = 0;
    Time _end = 0;
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
    return _end - _start + 1;
}


class TimePiecesContainerNode {
public:
    TimePiecesContainerNode(TimePiece item);
    TimePiecesContainerNode(const TimePiecesContainerNode& other);
    ~TimePiecesContainerNode();

    TimePiece item = TimePiece(0, 0);
    TimePiecesContainerNode* nextNode = nullptr;
};

TimePiecesContainerNode::TimePiecesContainerNode(TimePiece item) : TimePiece(item) {
}

TimePiecesContainerNode::TimePiecesContainerNode(const TimePiecesContainerNode& other) {
    item = other.item;
    nextNode = other.nextNode;
}

TimePiecesContainerNode::~TimePiecesContainerNode() {
}


class TimePiecesContainerIterator {
public:
    TimePiecesContainerIterator(TimePiecesContainerNode* startItem);
    TimePiecesContainerIterator(const TimePiecesContainerIterator& other);
    ~TimePiecesContainerIterator();

    const TimePiece& current() const;
    void next();
    bool isDone();

private:
    TimePiecesContainerNode* _currentNode = nullptr;
};

TimePiecesContainerIterator::TimePiecesContainerIterator(TimePiecesContainerNode* startItem) : _currentNode(startItem)
{
}

TimePiecesContainerIterator::TimePiecesContainerIterator(const TimePiecesContainerIterator& other) {
    _currentNode = other._currentNode;
}

TimePiecesContainerIterator::~TimePiecesContainerIterator() {
}

const TimePiece& TimePiecesContainerIterator::current() const {
    assert(_currentNode != nullptr);
    return _currentNode->item;
}

void TimePiecesContainerIterator::next() {
    assert(_currentNode != nullptr);
    _currentNode = _currentNode->nextNode;
}

bool TimePiecesContainerIterator::isDone() {
    return _currentNode == nullptr;
}


class TimePiecesContainer {
public:
    TimePiecesContainer();
    TimePiecesContainer(const TimePiecesContainer& other);
    ~TimePiecesContainer();

    void push(TimePiece item);
    TimePiecesContainerIterator iterate() const;
    size_t getLength();

private:
    TimePiecesContainerNode* _head = nullptr;
};

TimePiecesContainer::TimePiecesContainer() {
}

TimePiecesContainer::TimePiecesContainer(const TimePiecesContainer& other) {
    _head = other._head;
}

TimePiecesContainer::~TimePiecesContainer() {
    TimePiecesContainerNode** nodes = new TimePiecesContainerNode*[getLength()];
    TimePiecesContainerNode* node = _head;
    size_t i = 0;
    while (node != nullptr) {
        nodes[i++] = node;
        node = node->nextNode;
    }
    delete[] nodes;
}

void TimePiecesContainer::push(TimePiece item) {
    TimePiecesContainerNode* newNode = new TimePiecesContainerNode(item);
    if (_head == nullptr) {
        _head = newNode;
    } else {
        TimePiecesContainerNode* node = _head;
        while (node->nextNode != nullptr) {
            if (node->nextNode->item.getEnd()) { // TODO
                break;
            }
            node = node->nextNode;
        }
        newNode->nextNode = node->nextNode;
        node->nextNode = newNode;
    }
}

TimePiecesContainerIterator TimePiecesContainer::iterate() const {
    return TimePiecesContainerIterator(_head);
}

size_t TimePiecesContainer::getLength() {
    size_t length = 0;
    TimePiecesContainerNode* node = _head;
    while (node != nullptr) {
        length++;
        node = node->nextNode;
    }
    return length;
}


size_t countMaxDurations(TimePiecesContainer container) {
    size_t result = 0;
    bool* schedule = (bool*) calloc((size_t) (container.getMaxTime() + 1), sizeof(bool));
    for (TimePiecesContainerIterator iter = container.iterate(); !iter.isDone(); iter.next()) {
        const TimePiece& item = iter.current();
        bool canSchedule = true;
        for (int i = item.getStart(); i <= item.getEnd(); i++) {
            if (schedule[i]) {
                canSchedule = false;
                break;
            }
        }
        if (canSchedule) {
            result++;
            for (int i = item.getStart(); i <= item.getEnd(); i++) {
                schedule[i] = true;
            }
        }
    }
    free(schedule);
    return result;
}


int main() {
    TimePiecesContainer container;

    Time startTime, endTime;
    while (cin >> startTime && cin >> endTime) {
        container.push(TimePiece(startTime, endTime - 1));
    }

    cout << countMaxDurations(container);

    return 0;
}

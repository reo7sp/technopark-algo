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


class TimeDuration {
public:
    TimeDuration(int start, int end);
    TimeDuration(const TimeDuration& other);
    ~TimeDuration();

    int getStart() const;
    int getEnd() const;
    int getDuration() const;

private:
    int _start = 0;
    int _end = 0;
};

TimeDuration::TimeDuration(int start, int end) :
        _start(start), _end(end)
{
    assert(_start <= _end);
}

TimeDuration::TimeDuration(const TimeDuration& other) {
    _start = other._start;
    _end = other._end;
}

TimeDuration::~TimeDuration() {
}

int TimeDuration::getStart() const {
    return _start;
}

int TimeDuration::getEnd() const {
    return _end;
}

int TimeDuration::getDuration() const {
    return _end - _start + 1;
}


class TimeDurationsContainerNode {
public:
    TimeDurationsContainerNode(TimeDuration item);
    TimeDurationsContainerNode(const TimeDurationsContainerNode& other);
    ~TimeDurationsContainerNode();

    TimeDuration item = TimeDuration(0, 0);
    TimeDurationsContainerNode* nextNode = nullptr;
};

TimeDurationsContainerNode::TimeDurationsContainerNode(TimeDuration item) :
        item(item)
{
}

TimeDurationsContainerNode::TimeDurationsContainerNode(const TimeDurationsContainerNode& other) {
    item = other.item;
    nextNode = other.nextNode;
}

TimeDurationsContainerNode::~TimeDurationsContainerNode() {
}


class TimeDurationsContainerIterator {
public:
    TimeDurationsContainerIterator(TimeDurationsContainerNode* startItem);
    TimeDurationsContainerIterator(const TimeDurationsContainerIterator& other);
    ~TimeDurationsContainerIterator();

    const TimeDuration& current() const;
    void next();
    bool isDone();

private:
    TimeDurationsContainerNode* _currentNode = nullptr;
};

TimeDurationsContainerIterator::TimeDurationsContainerIterator(TimeDurationsContainerNode* startItem) :
    _currentNode(startItem)
{
}

TimeDurationsContainerIterator::TimeDurationsContainerIterator(const TimeDurationsContainerIterator& other) {
    _currentNode = other._currentNode;
}

TimeDurationsContainerIterator::~TimeDurationsContainerIterator() {
}

const TimeDuration& TimeDurationsContainerIterator::current() const {
    assert(_currentNode != nullptr);
    return _currentNode->item;
}

void TimeDurationsContainerIterator::next() {
    assert(_currentNode != nullptr);
    _currentNode = _currentNode->nextNode;
}

bool TimeDurationsContainerIterator::isDone() {
    return _currentNode == nullptr;
}


class TimeDurationsContainer {
public:
    TimeDurationsContainer();
    TimeDurationsContainer(const TimeDurationsContainer& other);
    ~TimeDurationsContainer();

    void push(TimeDuration item);
    TimeDurationsContainerIterator iterate() const;

    size_t getLength();

    int getMinTime();
    int getMaxTime();

private:
    TimeDurationsContainerNode* _head = nullptr;
    int _minTime = 0;
    int _maxTime = 0;
};

TimeDurationsContainer::TimeDurationsContainer() {
}

TimeDurationsContainer::TimeDurationsContainer(const TimeDurationsContainer& other) {
    _head = other._head;
}

TimeDurationsContainer::~TimeDurationsContainer() {
    size_t length = getLength();
    TimeDurationsContainerNode** nodes = new TimeDurationsContainerNode*[length];
    TimeDurationsContainerNode* node = _head;
    for (size_t i = 0; i < length; i++) {
        nodes[i] = node;
        node = node->nextNode;
    }
    delete[] nodes;
}

void TimeDurationsContainer::push(TimeDuration item) {
    TimeDurationsContainerNode* newNode = new TimeDurationsContainerNode(item);

    if (_head == nullptr) {
        _head = newNode;
    } else {
        TimeDurationsContainerNode* node = _head;
        while (node->nextNode != nullptr) {
            if (node->item.getDuration() == newNode->item.getDuration() &&
                    node->nextNode->item.getDuration() != newNode->item.getDuration())
            {
                break;
            }
            node = node->nextNode;
        }
        newNode->nextNode = node->nextNode;
        node->nextNode = newNode;
    }

    if (item.getStart() < _minTime) {
        _minTime = item.getStart();
    }
    if (item.getEnd() > _maxTime) {
        _maxTime = item.getEnd();
    }
}

TimeDurationsContainerIterator TimeDurationsContainer::iterate() const {
    return TimeDurationsContainerIterator(_head);
}

size_t TimeDurationsContainer::getLength() {
    size_t length = 0;
    TimeDurationsContainerNode* node = _head;
    while (node != nullptr) {
        length++;
        node = node->nextNode;
    }
    return length;
}

int TimeDurationsContainer::getMinTime() {
    return _minTime;
}

int TimeDurationsContainer::getMaxTime() {
    return _maxTime;
}


size_t countMaxDurations(TimeDurationsContainer container) {
    size_t result = 0;
    bool* schedule = (bool*) calloc((size_t) (container.getMaxTime() + 1), sizeof(bool));
    for (TimeDurationsContainerIterator iter = container.iterate(); !iter.isDone(); iter.next()) {
        const TimeDuration& item = iter.current();
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
    TimeDurationsContainer container;

    int startTime, endTime;
    while (cin >> startTime && cin >> endTime) {
        container.push(TimeDuration(startTime, endTime - 1));
    }

    cout << countMaxDurations(container);

    return 0;
}

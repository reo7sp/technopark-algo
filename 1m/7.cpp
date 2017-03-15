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


class TimePiecesVector {
public:
    TimePiecesVector(size_t initialCapacity = 32);
    TimePiecesVector(const TimePiecesVector& other);
    ~TimePiecesVector();

    const TimePiece& operator[](size_t index) const;
    void push(TimePiece item);

    size_t getLength() const;
    Time getMinTime() const;
    Time getMaxTime() const;

private:
    void _insert(TimePiece item, size_t index);
    void _grow();

    TimePiece* _data = nullptr;
    size_t _capacity = 0;
    size_t _length = 0;
};

TimePiecesVector::TimePiecesVector(size_t initialCapacity) :
    _capacity(initialCapacity),
    _length(0),
    _data((TimePiece*) malloc(sizeof(TimePiece) * _capacity))
{
}

TimePiecesVector::TimePiecesVector(const TimePiecesVector& other) {
    _capacity = other._capacity;
    _length = other._length;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (TimePiece*) malloc(sizeof(TimePiece) * _capacity);
    memcpy(_data, other._data, sizeof(TimePiece) * _length);
}

TimePiecesVector::~TimePiecesVector() {
    free(_data);
}

const TimePiece& TimePiecesVector::operator[](size_t index) const {
    assert(index < _length);
    return _data[index];
}

void TimePiecesVector::push(TimePiece item) {
    for (size_t i = 0; i < _length; i++) {
        if (_data[i].getDuration() < item.getDuration()) {
            _insert(item, i);
            return;
        }
    }
    _insert(item, _length);
}

size_t TimePiecesVector::getLength() const {
    return _length;
}

Time TimePiecesVector::getMinTime() const {
    assert(_length != 0);
    Time min = _data[0].getStart();
    for (size_t i = 1; i < _length; i++) {
        if (_data[i] < min) {
            min = _data[i].getStart();
        }
    }
    return min;
}

Time TimePiecesVector::getMaxTime() const {
    assert(_length != 0);
    Time max = _data[0].getEnd();
    for (size_t i = 1; i < _length; i++) {
        if (max < _data[i]) {
            max = _data[i].getEnd();
        }
    }
    return max;
}

void TimePiecesVector::_insert(TimePiece item, size_t index) {
    assert(index <= _length);
    if (_length == _capacity) {
        _grow();
    }
    for (size_t i = _length; i > index; i--) {
        _data[i] = _data[i - 1];
    }
    _data[index] = item;
    _length++;
}

void TimePiecesVector::_grow() {
    const size_t kGrowStep = 32;
    _capacity += kGrowStep;
    _data = (TimePiece*) realloc(_data, sizeof(TimePiece) * _capacity);
}


size_t countMaxMeetings(TimePiecesVector timePiecesVector) {
    size_t result = 0;

    size_t scheduleTableWidth = timePiecesVector.getMaxTime();
    int* schedule = new int[scheduleTableWidth];
    memset(schedule, -1, scheduleTableWidth);

    for (size_t i = 0; i < timePiecesVector.getLength(); i++) {
        assert(i != 0);
        const TimePiece& timePiece = timePiecesVector[i];

        int* intersectedTimePieces = new int[timePiece.getDuration()];
        size_t intersectedCount = 0;

        for (int time = timePiece.getStart(); time <= timePiece.getEnd(); time++) {
            if (schedule[time] != -1) {
                intersectedTimePieces[intersectedCount++] = schedule[time];
            }
        }

        if (intersectedCount == 0) {
            for (int time = timePiece.getStart(); time <= timePiece.getEnd(); time++) {
                schedule[time] = i;
            }
            result++;
        } else {
            size_t alternateResult = 0;

            int* alternateSchedule = new int[scheduleTableWidth];
            memcpy(alternateSchedule, );

            for (size_t j = 0; j <= i; j++) {
                assert(j != 0);
                bool doSkip = false;
                for (size_t k = 0; k < intersectedCount; k++) {
                    if (intersectedTimePieces[k] == j) {
                        doSkip = true;
                        break;
                    }
                }
                if (doSkip) {
                    continue;
                }
                const TimePiece& timePiece1 = timePiecesVector[j];
                bool canSchedule = true;
                for (int time = timePiece1.getStart(); time <= timePiece1.getEnd(); time++) {
                    if (alternateSchedule[time] != -1) {
                        canSchedule = false;
                        break;
                    }
                }
                if (canSchedule) {
                    for (int time = timePiece1.getStart(); time <= timePiece1.getEnd(); time++) {
                        alternateSchedule[time] = j;
                    }
                    alternateResult++;
                }
            }

            if (alternateResult > result) {
                delete[] schedule;
                schedule = alternateSchedule;
                result = alternateResult;
            } else {
                delete[] alternateSchedule;
            }
        }
    }

    delete[] schedule;

    return result;
}


int main() {
    TimePiecesVector container;

    Time startTime, endTime;
    while (cin >> startTime && cin >> endTime) {
        container.push(TimePiece(startTime, endTime - 1));
    }

    cout << countMaxMeetings(container);

    return 0;
}

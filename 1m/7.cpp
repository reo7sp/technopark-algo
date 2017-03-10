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


class IntMap {
public:
    explicit IntMap(size_t initialCapacity = 32);
    IntMap(const IntMap& other);
    ~IntMap();

    int& operator[](size_t index);

    size_t getCapacity() const;

private:
    void _grow(size_t minNewCapacity);

    size_t _capacity = 0;
    int* _data = nullptr;
};

IntMap::IntMap(size_t initialCapacity) :
        _capacity(initialCapacity),
        _data((int*) calloc(_capacity, sizeof(int)))
{
}

IntMap::IntMap(const IntMap &other) {
    _capacity = other._capacity;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (int*) calloc(_capacity, sizeof(int));
    memcpy(_data, other._data, sizeof(int) * _capacity);
}

IntMap::~IntMap() {
    free(_data);
}

int& IntMap::operator[](size_t index) {
    if (index >= _capacity) {
        _grow(index);
    }
    return _data[index];
}

size_t IntMap::getCapacity() const {
    return _capacity;
}

void IntMap::_grow(size_t minNewCapacity) {
    const size_t kGrowStep = 32;
    size_t oldCapacity = _capacity;
    _capacity = minNewCapacity + kGrowStep;
    _data = (int*) realloc(_data, sizeof(int) * _capacity);
    memset(_data + oldCapacity, 0, _capacity - oldCapacity);
}


int main() {
    IntMap map;

    int minTime = -1, maxTime = -1;
    
    int startTime, endTime;
    while (cin >> startTime && cin >> endTime) {
        int duration = endTime - startTime + 1;
        assert(duration > 0);
        map[duration]++;
        if (minTime == -1 || startTime < minTime) {
            minTime = startTime;
        }
        if (maxTime == -1 || endTime > maxTime) {
            maxTime = endTime;
        }
    }

    int leftTime = maxTime - minTime + 1;
    int answer = 0;
    bool stop = false;
    for (size_t i = 0; !stop && i < map.getCapacity(); i++) {
        for (size_t j = 0; j < map[i]; j++) {
            leftTime -= i;
            if (leftTime >= 0) {
                answer++;
            } else {
                stop = true;
                break;
            }
        }
    }
    cout << answer;

    return 0;
}

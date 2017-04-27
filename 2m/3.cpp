/*
 * Во всех задачах данного раздела необходимо реализовать и использовать  локальную пирамидальную сортировку  (без использования дополнительной памяти). Общее время работы алгоритма O(n log n).
 */

/*
 * 3_1. Реклама.
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
 */

/*
 * Test 1:
     * in:
         5
         1 10
         10 12
         1 10
         1 10
         23 24
     * out:
         5
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


template<typename T, typename COMPARE>
class Heap {
public:
    Heap(vector<T>& vector, COMPARE compare);

    T getMax() const;

    void rebuild();
    void sort();

private:
    vector<T>& _data;
    COMPARE _compare;

    void _buildHeap();
    void _siftDown(size_t i, size_t size);

    size_t _getParentIndex(size_t i) const;
    size_t _getLeftChildIndex(size_t i) const;
    size_t _getRightChildIndex(size_t i) const;
};

template<typename T, typename COMPARE>
Heap<T, COMPARE>::Heap(vector<T>& vector, COMPARE compare) : _data(vector), _compare(compare) {
    _buildHeap();
}

template<typename T, typename COMPARE>
T Heap<T, COMPARE>::getMax() const {
    return _data[0];
}

template<typename T, typename COMPARE>
void Heap<T, COMPARE>::rebuild() {
    _buildHeap();
}

template<typename T, typename COMPARE>
void Heap<T, COMPARE>::sort() {
    size_t heapSize = _data.size();
    while (heapSize > 1) {
        swap(_data[0], _data[heapSize - 1]);
        heapSize--;
        _siftDown(0, heapSize);
    }
}

template<typename T, typename COMPARE>
void Heap<T, COMPARE>::_buildHeap() {
    for (size_t i = _data.size() / 2 - 1; ; i--) {
        _siftDown(i, _data.size());
        if (i == 0) {
            break;
        }
    }
}

template<typename T, typename COMPARE>
void Heap<T, COMPARE>::_siftDown(size_t i, size_t size) {
    size_t leftElemIndex = _getLeftChildIndex(i);
    size_t rightElemIndex = _getRightChildIndex(i);

    size_t largestElemIndex = i;
    if (leftElemIndex < size && _compare(_data[i], _data[leftElemIndex])) {
        largestElemIndex = leftElemIndex;
    }
    if (rightElemIndex < size && _compare(_data[largestElemIndex], _data[rightElemIndex])) {
        largestElemIndex = rightElemIndex;
    }

    if (largestElemIndex != i) {
        std::swap(_data[i], _data[largestElemIndex]);
        _siftDown(largestElemIndex, size);
    }
}

template<typename T, typename COMPARE>
size_t Heap<T, COMPARE>::_getParentIndex(size_t i) const {
    assert(i > 0);
    return (i - 1) / 2;
}

template<typename T, typename COMPARE>
size_t Heap<T, COMPARE>::_getRightChildIndex(size_t i) const {
    return 2 * i + 2;
}

template<typename T, typename COMPARE>
size_t Heap<T, COMPARE>::_getLeftChildIndex(size_t i) const {
    return 2 * i + 1;
}


template<typename T, typename COMPARE>
void heapSort(vector<T>& data, COMPARE compare) {
    Heap<T, COMPARE> heap(data, compare);
    heap.sort();
};


enum class TimeType {
    ENTER, EXIT
};


class PersonTime {
public:
    PersonTime(size_t personId, int time, TimeType timeType);

    size_t getPersonId() const;
    int getTime() const;
    TimeType getType() const;

private:
    size_t _personId;
    int _time;
    TimeType _timeType;
};

PersonTime::PersonTime(size_t personId, int time, TimeType timeType) : _personId(personId), _time(time), _timeType(timeType) {
}

size_t PersonTime::getPersonId() const {
    return _personId;
}

int PersonTime::getTime() const {
    return _time;
}

TimeType PersonTime::getType() const {
    return _timeType;
}


size_t countAds(vector<PersonTime>& timetable, size_t peopleCount) {
    heapSort(timetable, [](const PersonTime& left, const PersonTime& right) {
        return left.getTime() < right.getTime();
    });

    size_t lastAdId = 0;
    vector<size_t> userStartAdIds(peopleCount);
    for (size_t i = 0; i < timetable.size(); i++) {
        const PersonTime& item = timetable[i];

        switch (item.getType()) {
            case TimeType::ENTER:
                userStartAdIds[item.getPersonId()] = lastAdId;
                break;
            case TimeType::EXIT:
                while (lastAdId - userStartAdIds[item.getPersonId()] < 2) {
                    lastAdId++;
                }
                break;
        }
    }

    return lastAdId;
}


int main() {
    size_t n;
    cin >> n;

    vector<PersonTime> input;
    input.reserve(n);
    for (size_t i = 0; i < n; i++) {
        int start, end;
        cin >> start;
        cin >> end;
        input.push_back(PersonTime(i, start, TimeType::ENTER));
        input.push_back(PersonTime(i, end, TimeType::EXIT));
    }

    cout << countAds(input, n);

    return 0;
}

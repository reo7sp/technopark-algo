/*
 * Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
Формат входных данных:
На вход подается количество кубиков N.
Формат выходных данных:
Вывести число различных пирамид из N кубиков.
 */

/*
 * 6_2. Широкая пирамида.  Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
 */

#include <iostream>
#include <cassert>
#include <memory.h>

using namespace std;


class TriangleTableRow {
public:
    TriangleTableRow(size_t size, unsigned long* data);
    TriangleTableRow(const TriangleTableRow& other);
    ~TriangleTableRow();

    unsigned long operator[](size_t index) const;
    unsigned long& operator[](size_t index);

    size_t getSize() const;

private:
    size_t _size = 0;
    unsigned long* _data = nullptr;
};

TriangleTableRow::TriangleTableRow(size_t size, unsigned long* data) :
    _size(size),
    _data(data)
{
}

TriangleTableRow::TriangleTableRow(const TriangleTableRow& other) {
    _data = other._data;
}

TriangleTableRow::~TriangleTableRow() {
}

unsigned long TriangleTableRow::operator[](size_t index) const {
    assert(index != 0 && index <= _size);
    return _data[index - 1];
}

unsigned long& TriangleTableRow::operator[](size_t index) {
    assert(index != 0 && index <= _size);
    return _data[index - 1];
}

size_t TriangleTableRow::getSize() const {
    return _size;
}


// 2 dimensional square array without elements above main diagonal.
// Indexes are starting from 1, not 0.
// Tables are initialized by zeros.
class TriangleTable {
public:
    TriangleTable(size_t size);
    TriangleTable(const TriangleTable& other);
    ~TriangleTable();

    const TriangleTableRow operator[](size_t index) const;
    TriangleTableRow operator[](size_t index);

    size_t getSize() const;

private:
    size_t _getDataLocation(size_t n) const;

    size_t _size = 0;
    unsigned long* _data = nullptr;
};

TriangleTable::TriangleTable(size_t size) :
    _size(size),
    _data((unsigned long*) calloc(_getDataLocation(_size), sizeof(unsigned long)))
{
}

TriangleTable::TriangleTable(const TriangleTable& other) {
    _size = other._size;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (unsigned long*) calloc(_getDataLocation(_size), sizeof(unsigned long));
}

TriangleTable::~TriangleTable() {
    free(_data);
}

const TriangleTableRow TriangleTable::operator[](size_t index) const {
    assert(index != 0 && index <= _size);
    return TriangleTableRow(index, _data + _getDataLocation(index - 1));
}

TriangleTableRow TriangleTable::operator[](size_t index) {
    assert(index != 0 && index <= _size);
    return TriangleTableRow(index, _data + _getDataLocation(index - 1));
}

size_t TriangleTable::getSize() const {
    return _size;
}

size_t TriangleTable::_getDataLocation(size_t n) const {
    // This formula calculates sum of an arithmetic progression with step = 1.
    // Graphic representation:
    // *
    // **
    // ***
    // ****
    // ...
    return (1 + n) * n / 2;
}


unsigned long countPossiblePyramids(size_t n) {
    // One pyramid is one split of n into sum components.
    // E.g. 6 = 3 + 2 + 1
    assert(n >= 1);
    TriangleTable table(n);
    /*
     *   | max sum component →      |
     * __|__________________________|
     *   |                          |
     * n | 1                        | 1 = (1)
     * ↓ |  1                       | 2 = (2)
     *   |  11                      | 3 = (3), (2, 1)
     *   |   11                     | 4 = (4), (3, 1)
     *   |   111                    | 5 = (5), (4, 1), (3, 2)
     *   |   1111                   | 6 = (6), (5, 1), (4, 2), (3, 2, 1)
     *   |    2111                  | 7 = (7), (6, 1), (5, 2), (4, 3), (4, 2, 1)
     *   |    12111                 | 8 = (8), (7, 1), (6, 2), (5, 3), (5, 2, 1), (4, 3, 1)
     *   |    122111                | 9 = (9), (8, 1), (7, 2), (6, 3), (6, 2, 1), (5, 4), (5, 3, 1), (4, 3, 2)
     * --+--------------------------+
     *     1 3 5 7 9
     *      2 4 6 8
     */
    table[1][1] = 1;
    if (n >= 2) {
        table[2][2] = 1;
    }
    for (size_t currentNumber = 3; currentNumber <= n; currentNumber++) {
        table[currentNumber][currentNumber] = 1;
        for (size_t maxSumComponent = currentNumber - 1; maxSumComponent != 0; maxSumComponent--) {
            for (size_t i = min(maxSumComponent - 1, currentNumber - maxSumComponent); i != 0; i--) {
                table[currentNumber][maxSumComponent] += table[currentNumber - maxSumComponent][i];
            }
        }
    }
    unsigned long result = 0;
    for (size_t i = 1; i <= n; i++) {
        result += table[n][i]; // sum of the row
    }
    return result;
}


int main() {
    size_t n;
    cin >> n;

    cout << countPossiblePyramids(n);

    return 0;
}


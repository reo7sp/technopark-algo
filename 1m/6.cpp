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
    TriangleTableRow(size_t size, int* data);
    TriangleTableRow(const TriangleTableRow& other);
    ~TriangleTableRow();

    int operator[](size_t index) const;
    int& operator[](size_t index);

    size_t getSize() const;

private:
    size_t _size = 0;
    int* _data = nullptr;
};

TriangleTableRow::TriangleTableRow(size_t size, int* data) :
    _size(size),
    _data(data)
{
}

TriangleTableRow::TriangleTableRow(const TriangleTableRow& other) {
    _data = other._data;
}

TriangleTableRow::~TriangleTableRow() {
}

int TriangleTableRow::operator[](size_t index) const {
    assert(index != 0 && index <= _size);
    return _data[index - 1];
}

int& TriangleTableRow::operator[](size_t index) {
    assert(index != 0 && index <= _size);
    return _data[index - 1];
}

size_t TriangleTableRow::getSize() const {
    return _size;
}


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
    int* _data = nullptr;
};

TriangleTable::TriangleTable(size_t size) :
    _size(size),
    _data((int*) calloc(_getDataLocation(_size), sizeof(int)))
{
}

TriangleTable::TriangleTable(const TriangleTable& other) {
    _size = other._size;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (int*) calloc(_getDataLocation(_size), sizeof(int));
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
    return (1 + n) * n / 2;
}


int countPossiblePyramids(size_t n) {
    assert(n >= 1);
    TriangleTable table(n);
    table[1][1] = 1;
    if (n >= 2) {
        table[2][2] = 1;
    }
    for (size_t i = 3; i <= n; i++) {
        table[i][i] = 1;
        for (size_t j = i - 1; j != 0; j--) {
            for (size_t k = min(j - 1, i - j); k != 0; k--) {
                table[i][j] += table[i - j][k];
            }
        }
    }
    int result = 0;
    for (size_t i = 1; i <= n; i++) {
        result += table[n][i];
    }
    return result;
}


int main() {
    size_t n;
    cin >> n;

    cout << countPossiblePyramids(n);

    return 0;
}


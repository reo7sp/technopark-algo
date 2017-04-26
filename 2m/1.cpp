/*
 * Во всех вариантах данной задачи необходимо реализовать и использовать  сортировку вставками . Функция сравнения или оператор сравнения или функтор должен быть явно определен и передаваться в функцию сортировки.
 */

/*
 * 1_1. Ящики.
На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0. Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий). Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям. Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
 */

/*
 * Test 1:
     * in:
         3
         2 3 5
         1 1 1
         10 4 10
     * out:
         1 0 2
 * Test 2:
     * in:
         2
         5 2 1
         2 3 7
     * out:
         0 1
 */

#include <vector>
#include <iostream>

using namespace std;


class Box {
public:
    Box(int sizeX, int sizeY, int sizeZ);

    int getSizeX() const;
    int getSizeY() const;
    int getSizeZ() const;

private:
    int _sizeX, _sizeY, _sizeZ;
};

Box::Box(int sizeX, int sizeY, int sizeZ) : _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ) {}

int Box::getSizeX() const {
    return _sizeX;
}

int Box::getSizeY() const {
    return _sizeY;
}

int Box::getSizeZ() const {
    return _sizeZ;
}


class BoxWithId : public Box {
public:
    BoxWithId(size_t id, int sizeX, int sizeY, int sizeZ);

    size_t getId() const;

private:
    size_t _id;
};

BoxWithId::BoxWithId(size_t id, int sizeX, int sizeY, int sizeZ) : _id(id), Box(sizeX, sizeY, sizeZ) {}

size_t BoxWithId::getId() const {
    return _id;
}


template<typename T>
class BoxIsLessComparer {
public:
    bool operator()(const T& left, const T& right) const;
};

template<typename T>
bool BoxIsLessComparer<T>::operator()(const T& left, const T& right) const {
    int lx = left.getSizeX();
    int ly = left.getSizeY();
    int lz = left.getSizeZ();
    int rx = right.getSizeX();
    int ry = right.getSizeY();
    int rz = right.getSizeZ();
    return (lx < rx && ly < ry && lz < rz) ||
           (lx < ry && ly < rz && lz < rx) ||
           (lx < rz && ly < rx && lz < ry) ||
           (lx < rx && ly < rz && lz < ry) ||
           (lx < rz && ly < ry && lz < rx) ||
           (lx < ry && ly < rx && lz < rz);
};


template<typename T, typename COMPARER>
void insertSort(vector<T>& array, const COMPARER& compare) {
    for (size_t i = 1; i < array.size(); i++)  {
        T tmp = array[i];
        size_t j = i;
        for (; j >= 1 && compare(tmp, array[j - 1]); j--) {
            array[j] = array[j - 1];
        }
        array[j] = tmp;
    }
};


int main() {
    vector<BoxWithId> boxes;
    BoxIsLessComparer<BoxWithId> boxCompare;

    size_t n;
    cin >> n;
    boxes.reserve(n);

    for (size_t i = 0; i < n; i++) {
        int x, y, z;
        cin >> x;
        cin >> y;
        cin >> z;
        boxes.push_back(BoxWithId(i, x, y, z));
    }

    insertSort(boxes, boxCompare);

    for (size_t i = 0; i < n; i++) {
        cout << boxes[i].getId() << ' ';
    }

    return 0;
}

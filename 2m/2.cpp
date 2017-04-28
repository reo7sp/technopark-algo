/*
 * Решение всех задач данного раздела предполагает использование кучи.
 */

/*
 * 2_4. Скользящий максимум.
Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n log n), память O(k).
Формат входных данных.  Вначале вводится n - количество элементов массива. Затем вводится n строк со значением каждого элемента. Затем вводится k - размер окна.
Формат выходных данных.  Разделенные пробелом значения максимумов для каждого положения окна.
 */

/*
 * Test 1:
     * in:
         3
         1 2 3
         2
     * out:
         2 3
 * Test 2:
     * in:
         9
         0 7 3 8 4 5 10 4 6
         4
     * out:
         8 8 8 10 10 10
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


template<typename T>
class Heap {
public:
    Heap(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end);

    T getMax() const;

private:
    vector<T> _data;

    void _buildHeap();
    void _siftDown(size_t i);

    inline size_t _getParentIndex(size_t i) const;
    inline size_t _getLeftChildIndex(size_t i) const;
    inline size_t _getRightChildIndex(size_t i) const;
};

template<typename T>
Heap<T>::Heap(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end) : _data(begin, end) {
    _buildHeap();
}

template<typename T>
T Heap<T>::getMax() const {
    return _data[0];
}

template<typename T>
void Heap<T>::_buildHeap() {
    for (size_t i = _data.size() / 2 - 1; ; i--) {
        _siftDown(i);
        if (i == 0) {
            break;
        }
    }
}

template<typename T>
void Heap<T>::_siftDown(size_t i) {
    size_t rootIndex = i;
    while (_getLeftChildIndex(rootIndex) <= _data.size()) {
        int childIndex = _getLeftChildIndex(rootIndex);
        if (childIndex + 1 <= _data.size() && _data[childIndex] < _data[childIndex + 1]) {
            ++childIndex;
        }
        if (_data[rootIndex] < _data[childIndex]) {
            swap(_data[rootIndex], _data[childIndex]);
            rootIndex = childIndex;
        } else {
            return;
        }
    }
}

template<typename T>
inline size_t Heap<T>::_getParentIndex(size_t i) const {
    assert(i > 0);
    return (i - 1) / 2;
}

template<typename T>
inline size_t Heap<T>::_getRightChildIndex(size_t i) const {
    return 2 * i + 2;
}

template<typename T>
inline size_t Heap<T>::_getLeftChildIndex(size_t i) const {
    return 2 * i + 1;
}


template<typename T>
vector<T> findMaxInWindows(const vector<T>& array, size_t windowSize) {
    assert(windowSize >= 1);
    vector<T> result;
    size_t resultSize = array.size() - windowSize + 1;
    result.reserve(resultSize);
    for (size_t i = 0; i < resultSize; i++) {
        Heap<T> heap(array.begin() + i, array.begin() + i + windowSize);
        result.push_back(heap.getMax());
    }
    return result;
}


int main() {
    size_t n;
    cin >> n;

    vector<int> input;
    input.reserve(n);
    for (size_t i = 0; i < n; i++) {
        int elem;
        cin >> elem;
        input.push_back(elem);
    }

    size_t k;
    cin >> k;

    vector<int> output = findMaxInWindows(input, k);

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << ' ';
    }

    return 0;
}
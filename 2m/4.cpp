/*
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
● Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
● Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
● Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
● Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
● Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше
опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
● В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 */

/*
 * 4_1.  Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */

/*
 * Test 1:
     * in:
         10 4
         1 2 3 4 5 6 7 8 9 10
     * out:
         5
 * Test 2:
     * in:
         10 0
         3 6 5 7 2 9 8 10 4 1
     * out:
         1
 * Test 3:
     * in:
         10 9
         0 0 0 0 0 0 0 0 0 1
     * out:
         1
 */

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

namespace findOrderStatisticUtils {
    /**
     * Медиана из первого, последнего и серединного.
     * @param startIndex inclusive
     * @param endIndex exclusive
     */
    template<typename T>
    inline size_t getPivot(const vector<T>& array, size_t startIndex, size_t endIndex) {
        endIndex--;
        size_t middleIndex = (startIndex + endIndex) / 2;
        // перебираем по кругу
        if (array[endIndex] <= array[startIndex] && array[startIndex] <= array[middleIndex]) {
            return startIndex;
        } else if (array[startIndex] <= array[middleIndex] && array[middleIndex] <= array[endIndex]) {
            return middleIndex;
        } else {
            return endIndex;
        }
    }


    /**
     * @param startIndex inclusive
     * @param endIndex exclusive
     */
    template<typename T>
    size_t partition(vector<T>& array, size_t startIndex, size_t endIndex) {
        size_t pivotIndex = getPivot(array, startIndex, endIndex);

        endIndex--; // right is inclusive now

        T pivot = array[pivotIndex];
        swap(array[pivotIndex], array[endIndex]); // pivot must not interfere in comparisons
        endIndex--;

        size_t i = startIndex;
        size_t j = endIndex;
        while (i <= j) {
            while (i <= endIndex && array[i] < pivot) {
                i++;
            }
            while (j >= startIndex && array[j] > pivot) {
                j--;
            }
            if (i >= array.size() || j >= array.size()) { // overflow check
                break;
            }
            if (i <= j) {
                swap(array[i], array[j]);
                i++;
                j--;
            }
        }

        endIndex++;
        swap(array[i], array[endIndex]); // revert pivot

        return i;
    }
};


template<typename T>
T findOrderStatistic(vector<T>& array, size_t k) {
    size_t pivotIndex;
    size_t startIndex = 0;
    size_t endIndex = array.size();
    while (startIndex < endIndex) {
        pivotIndex = findOrderStatisticUtils::partition(array, startIndex, endIndex);
        if (pivotIndex == k) {
            break;
        } else if (pivotIndex < k) {
            startIndex = pivotIndex + 1;
        } else {
            endIndex = pivotIndex;
        }
    }
    return array[pivotIndex];
}


int main() {
    size_t n;
    cin >> n;

    size_t k;
    cin >> k;

    vector<int> input;
    input.reserve(n);
    for (size_t i = 0; i < n; i++) {
        int it;
        cin >> it;
        input.push_back(it);
    }

    cout << findOrderStatistic(input, k);

    return 0;
}
/*
 * 6_1. MSD для строк.
Дан массив строк. Количество строк не больше 100000. Отсортировать массив методом поразрядной сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
 */

/*
 * Test 1:
     * in:
         ab
         a
         aaa
         aa
     * out:
         a
         aa
         aaa
         ab
 */

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


namespace _msdSortInternal {
    vector<size_t>
    countingSort(vector<string>& array, size_t startIndex, size_t endIndex, size_t alphabetSize, size_t sortIndex) {
        if (endIndex <= startIndex) {
            return vector<size_t> {};
        }
        const size_t n = endIndex - startIndex;
        vector<size_t> counts(alphabetSize + 1);
        for (size_t i = 0; i < n; ++i) {
            char c;
            if (sortIndex < array[startIndex + i].size()) {
                c = array[startIndex + i][sortIndex];
            } else {
                c = '\0';
            }
            counts[c]++;
        }
        size_t countsSum = 0;
        for (size_t i = 0; i < alphabetSize + 1; i++) {
            size_t countsForItem = counts[i];
            counts[i] = countsSum;
            countsSum += countsForItem;
        }
        vector<string> result(n);
        for (size_t i = 0; i < n; ++i) {
            result[counts[array[startIndex + i][sortIndex]]++] = array[startIndex + i];
        }
        for (size_t i = 0; i < n; i++) {
            array[startIndex + i] = result[i];
        }
        return counts;
    }

    void msdSort(vector<string>& array, size_t startIndex, size_t endIndex, size_t alphabetSize, size_t sortIndex) {
        if (endIndex <= startIndex || sortIndex < array[startIndex].size()) {
            return;
        }
        auto c = _msdSortInternal::countingSort(array, startIndex, endIndex, alphabetSize, 0);
        if (c.empty()) return;
        for (int i = 0; i < alphabetSize + 1; ++i) {
            _msdSortInternal::msdSort(array, startIndex + c[i], startIndex + c[i + 1] - c[i], alphabetSize, sortIndex + 1);
        }
    }
}

void msdSort(vector<string>& array, size_t alphabetSize) {
    _msdSortInternal::countingSort(array, 0, array.size(), alphabetSize, 0);
    _msdSortInternal::msdSort(array, 0, array.size(), alphabetSize, 1);
}


int main() {
    vector<string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }

    msdSort(input, 256);

    for (auto& it : input) {
        cout << it << endl;
    }

    return 0;
}
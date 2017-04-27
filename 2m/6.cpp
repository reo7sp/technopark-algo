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
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


namespace _msdSortInternal {
    void countingSort(string* array, size_t n, size_t alphabetSize, size_t sortIndex, size_t* groupStartsOut) {
        size_t* counts = (size_t*) malloc(sizeof(size_t) * (alphabetSize + 1));
        memset(counts, 0, sizeof(size_t) * (alphabetSize + 1));
        for (size_t i = 0; i < n; i++) {
            char ch = sortIndex < array[i].size() ? array[i][sortIndex] : '\0';
            counts[ch]++;
        }

        size_t countsSum = 0;
        for (size_t i = 0; i < alphabetSize + 1; i++) {
            size_t countsForItem = counts[i];
            counts[i] = countsSum;
            countsSum += countsForItem;
        }
        memcpy(groupStartsOut, counts, sizeof(size_t) * (alphabetSize + 1));

        string* result = (string*) malloc(sizeof(string) * n);
        for (size_t i = 0; i < n; i++) {
            char ch = sortIndex < array[i].size() ? array[i][sortIndex] : '\0';
            result[counts[ch]++] = array[i];
        }
        memcpy(array, result, sizeof(string) * n);

        free(counts);
        free(result);
    }

    void msdSort(string* array, size_t n, size_t alphabetSize, size_t sortIndex) {
        if (array[0].size() <= sortIndex || n < 2) {
            return;
        }
        size_t* groupStarts = new size_t[alphabetSize + 1];
        countingSort(array, n, alphabetSize, sortIndex, groupStarts);
        for (size_t i = 0; i < alphabetSize; i++) {
            assert(groupStarts[i + 1] >= groupStarts[i]);
            msdSort(array + groupStarts[i], groupStarts[i + 1] - groupStarts[i], alphabetSize, sortIndex + 1);
        }
        delete[] groupStarts;
    }
}

void msdSort(vector<string>& array, size_t alphabetSize) {
    _msdSortInternal::msdSort(array.data(), array.size(), alphabetSize, 0);
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
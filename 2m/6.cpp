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
    vector<string> countingSort(const vector<string>& array, size_t startIndex, size_t endIndex, size_t alphabetSize, size_t sortIndex) {
        if (endIndex <= startIndex) {
            return vector<string>();
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
        return result;
    }

    vector<string> msdSort(const vector<string>& array, size_t startIndex, size_t endIndex, size_t alphabetSize, size_t sortIndex) {
        if (endIndex <= startIndex) {
            return vector<string>();
        }

        vector<string> result;
        result.reserve(endIndex - startIndex);

        char currentChar = array[startIndex][sortIndex - 1];
        size_t currentCharStartIndex = startIndex;
        for (size_t i = startIndex; i <= endIndex; i++) {
            if (i == endIndex || array[i][sortIndex - 1] != currentChar) {
                vector<string> notYetSortedArray = countingSort(array, currentCharStartIndex, i, alphabetSize, sortIndex);

                size_t longerItemsStartIndex = notYetSortedArray.size();
                for (size_t i = 0; i < notYetSortedArray.size(); i++) {
                    if (sortIndex < notYetSortedArray[i].size()) {
                        longerItemsStartIndex = i;
                        break;
                    }
                }

                vector<string> sortedLongerItems = msdSort(notYetSortedArray, longerItemsStartIndex, notYetSortedArray.size(), alphabetSize, sortIndex + 1);

                for (size_t i = 0; i < longerItemsStartIndex; i++) {
                    result.push_back(notYetSortedArray[i]);
                }
                for (size_t i = 0; i < sortedLongerItems.size(); i++) {
                    result.push_back(sortedLongerItems[i]);
                }

                if (i < endIndex) {
                    currentChar = array[i][sortIndex - 1];
                    currentCharStartIndex = i;
                }
            }
        }

        return result;
    }
}

vector<string> msdSort(const vector<string>& array, size_t alphabetSize) {
    vector<string> sortedArray = _msdSortInternal::countingSort(array, 0, array.size(), alphabetSize, 0);
    return _msdSortInternal::msdSort(sortedArray, 0, sortedArray.size(), alphabetSize, 1);
}


int main() {
    vector<string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }

    vector<string> output = msdSort(input, 256);

    for (auto& it : output) {
        cout << it << endl;
    }

    return 0;
}
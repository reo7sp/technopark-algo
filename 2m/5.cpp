/*
 * 5_2. Сортировка почти упорядоченной последовательности.
Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 */

/*
 * Test 1:
     * in:
         10 4
         0 4 3 2 1 8 7 6 5 9
     * out:
         0 1 2 3 4 5 6 7 8 9
 */

#include <vector>
#include <iostream>

using namespace std;


template<typename T>
vector<T> merge(typename vector<T>::const_iterator begin1, typename vector<T>::const_iterator end1, typename vector<T>::const_iterator begin2, typename vector<T>::const_iterator end2) {
    vector<T> result;
    result.reserve((end1 - begin1) + (end2 - begin2));
    while (begin1 != end1 && begin2 != end2) {
        if (*begin1 <= *begin2) {
            result.push_back(*begin1);
            begin1++;
        } else {
            result.push_back(*begin2);
            begin2++;
        }
    }
    while (begin1 != end1) {
        result.push_back(*begin1);
        begin1++;
    }
    while (begin2 != end2) {
        result.push_back(*begin2);
        begin2++;
    }
    return result;
}

template<typename T>
vector<T> mergeSort(typename vector<T>::const_iterator begin, typename vector<T>::const_iterator end) {
    if (end - begin == 1) {
        return vector<T> { *begin };
    }
    typename vector<T>::const_iterator middle = begin + (end - begin) / 2;
    vector<T> v1 = mergeSort<T>(begin, middle);
    vector<T> v2 = mergeSort<T>(middle, end);
    return merge<T>(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
}

template<typename T>
vector<T> mergeSort(const vector<T>& array) {
    return mergeSort<T>(array.cbegin(), array.cend());
}

template<typename T>
vector<T> sortSemisortedSequence(vector<T> array, size_t k) {
    for (size_t i = 0; i < array.size(); i += k) {
        typename vector<T>::const_iterator begin = array.cbegin() + i;
        typename vector<T>::const_iterator end = begin + 2 * k;
        if (array.cend() < end) {
            end = array.cend();
        }
        typename vector<T>::const_iterator middle = begin + (end - begin) / 2;
        vector<T> v1 = mergeSort<T>(begin, middle);
        vector<T> v2 = mergeSort<T>(middle, end);
        vector<T> sorted = merge<T>(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
        for (size_t j = 0; j < 2 * k && i + j < array.size(); j++) {
            array[i + j] = sorted[j];
        }
    }
    return array;
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

    vector<int> output = sortSemisortedSequence(input, k);

    for (size_t i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }

    return 0;
}
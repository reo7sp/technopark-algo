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


vector<int> sortSemisortedSequence(const vector<int>& input, size_t k) {
//    mergeSort()
    return vector<int>();
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
/*
 * Решение всех задач данного раздела предполагает использование стека. Способ реализации стека может быть любым (список/динамический массив).
 */

/*
 * 5_2. Стековые анаграммы.
 * Пара слов называется стековой анаграммой, если одно слово можно получить из другого, проведя последовательность стековых операций с его буквами (взять очередную букву исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова).
Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе. Все буквы в слове различные.
Длина анаграммы ≤ 10000.
Формат входных данных.  Пара слов, являющихся анаграммой.
Формат выходных данных.   YES , если последовательность стековых операций существует и  NO  в противном случае.
 */

#include <iostream>
#include <string>

using namespace std;


bool isStackAnagram(const string& src, const string& dst) {
    if (src.length() != dst.length()) {
        return false;
    }
    for (size_t srcIndex = 0; srcIndex < src.length(); srcIndex++) {
        bool doContinueSearch = true;

        size_t dstIndex;
        for (dstIndex = srcIndex; doContinueSearch && dstIndex < dst.length(); dstIndex++) {
            if (src[srcIndex] == dst[dstIndex]) {
                doContinueSearch = false;

                size_t distance = dstIndex - srcIndex + 1;
                for (size_t k = 1; k < distance; k++) {
                    if (src[srcIndex + k] != dst[dstIndex - k]) {
                        doContinueSearch = true;
                        break;
                    }
                }
            }
        }

        if (doContinueSearch) {
            return false;
        } else {
            srcIndex = dstIndex;
        }
    }
    return true;
}

int main() {
    string src, dst;
    cin >> src;
    cin >> dst;

    cout << (isStackAnagram(src, dst) ? "YES" : "NO");

    return 0;
}

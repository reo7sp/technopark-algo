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
#include <cassert>
#include <memory.h>

using namespace std;


class CharStack {
public:
    explicit CharStack(size_t initialCapacity = 32);
    CharStack(const CharStack& other);
    ~CharStack();

    void push(char item);
    char pop();
    char seek() const;

    bool isEmpty();

private:
    void _grow();

    size_t _capacity = 0;
    size_t _length = 0;
    char* _data = nullptr;
};

CharStack::CharStack(size_t initialCapacity) :
        _capacity(initialCapacity),
        _length(0),
        _data((char*) malloc(sizeof(char) * _capacity))
{
}

CharStack::CharStack(const CharStack& other) {
    _capacity = other._capacity;
    _length = other._length;
    if (_data != nullptr) {
        free(_data);
    }
    _data = (char*) malloc(sizeof(char) * _capacity);
    memcpy(_data, other._data, sizeof(char) * _length);
}

CharStack::~CharStack() {
    free(_data);
}

void CharStack::push(char item) {
    if (_length == _capacity) {
        _grow();
    }
    _data[_length++] = item;
}

char CharStack::pop() {
    assert(_length != 0);
    return _data[--_length];
}

char CharStack::seek() const {
    assert(_length != 0);
    return _data[_length - 1];
}

void CharStack::_grow() {
    const size_t kGrowFactor = 2;
    _capacity *= kGrowFactor;
    _data = (char*) realloc(_data, sizeof(char) * _capacity);
}

bool CharStack::isEmpty() {
    return _length == 0;
}


bool isStackAnagram(const char* src, const char* dst) {
    CharStack stack;
    size_t dstIndex = 0;
    for (size_t srcIndex = 0; src[srcIndex] != '\0'; srcIndex++) {
        // emulating stack anagram creation
        stack.push(src[srcIndex]);
        while (!stack.isEmpty() && dst[dstIndex] == stack.seek()) {
            stack.pop();
            dstIndex++;
        }
    }
    return stack.isEmpty();
}


int main() {
    char* src = new char[10000];
    cin >> src;

    char* dst = new char[10000];
    cin >> dst;

    cout << (isStackAnagram(src, dst) ? "YES" : "NO");

    delete[] src;
    delete[] dst;

    return 0;
}

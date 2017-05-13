/*
 * Задача 1. Хеш-таблица (6 баллов)
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
 */

/*
 * 1_1.  Для разрешения коллизий используйте квадратичное пробирование. i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */

/*
 * Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции – один из трех символов:
+ означает добавление данной строки в множество;
- означает удаление строки из множества;
? означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
 */

/*
 * Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.
 */

/*
stdin:
    + hello
    + bye
    ? bye
    + bye
    - bye
    ? bye
    ? hello
stdout:
    OK
    OK
    OK
    FAIL
    OK
    FAIL
    OK
 */


#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


class HashSet {
public:
    explicit HashSet(float maxLoadFactor = 3.0f / 4);

    bool add(const string& item);
    bool remove(const string& item);
    bool has(const string& item) const;

private:
    static const size_t _initialCapacity = 8;

    struct Item {
        string value;
        bool hasValue = false;
    };

    float _getLoadFactor() const;
    bool _needRehash() const;
    size_t _hash(const string& item) const;
    size_t _hash(const string& item, size_t m) const;
    size_t _nextHash(size_t previousHash, size_t index) const;

    void _rehash();

    vector<Item> _data;
    float _maxLoadFactor = 0;
    size_t _itemCount = 0;
};

HashSet::HashSet(float maxLoadFactor) : _maxLoadFactor(maxLoadFactor) {
    assert(0 < _maxLoadFactor && _maxLoadFactor <= 1);
    _data.resize(_initialCapacity);
}

bool HashSet::add(const string& item) {
    if (_needRehash()) {
        _rehash();
    }

    bool isAdded = false;
    size_t addPosition = 0;

    size_t index = _hash(item);
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[index].hasValue) {
            if (_data[index].value == item) {
                return false;
            }
        } else {
            if (!isAdded) {
                isAdded = true;
                addPosition = index;
            }
        }
        index = _nextHash(index, i + 1);
    }

    if (isAdded) {
        _data[addPosition].value = item;
        _data[addPosition].hasValue = true;
        _itemCount++;
        return true;
    } else {
        return false;
    }
}

bool HashSet::remove(const string& item) {
    size_t index = _hash(item);
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[index].hasValue && _data[index].value == item) {
            _data[index].hasValue = false;
            _itemCount--;
            return true;
        }
        index = _nextHash(index, i + 1);
    }
    return false;
}

bool HashSet::has(const string& item) const {
    size_t index = _hash(item);
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[index].hasValue && _data[index].value == item) {
            return true;
        }
        index = _nextHash(index, i + 1);
    }
    return false;
}

float HashSet::_getLoadFactor() const {
    return (float) _itemCount / _data.size();
}

bool HashSet::_needRehash() const {
    return _getLoadFactor() >= _maxLoadFactor;
}

size_t HashSet::_hash(const string& item) const {
    return _hash(item, _data.size());
}

size_t HashSet::_hash(const string& item, size_t m) const {
    static const size_t a = 41;
    size_t hash = 0;
    for (char ch : item) {
        hash = (hash * a + ch) % m;
    }
    return hash;
}

size_t HashSet::_nextHash(size_t previousHash, size_t index) const {
    return (previousHash + index) % _data.size();
}

void HashSet::_rehash() {
    vector<Item> newData;
    newData.resize(_data.size() * 2);
    for (const Item& item : _data) {
        if (item.hasValue) {
            newData[_hash(item.value, newData.size())] = item;
        }
    }
    _data = newData;
}


int main() {
    HashSet set;

    string operation, item;
    while (cin >> operation && cin >> item) {
        bool success = false;
        switch (operation[0]) {
            case '+':
                success = set.add(item);
                break;
            case '-':
                success = set.remove(item);
                break;
            case '?':
                success = set.has(item);
                break;
        }
        cout << (success ? "OK" : "FAIL") << endl;
    }

    return 0;
}
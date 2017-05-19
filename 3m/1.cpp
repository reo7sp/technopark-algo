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
    explicit HashSet(float maxLoadFactor = 3.0f / 4, size_t capacity = 8);

    bool add(const string& item);
    bool remove(const string& item);
    bool has(const string& item) const;

private:
    struct Entry {
        string value;
        bool empty = true;
        bool deleted = false;
    };

    float _getLoadFactor() const;
    bool _needRehash() const;
    size_t _hash(const string& item) const;
    size_t _hash(const string& item, size_t m) const;
    size_t _nextHash(size_t previousHash, size_t index) const;
    size_t _nextHash(size_t previousHash, size_t index, size_t m) const;

    void _rehash();

    vector<Entry> _data;
    float _maxLoadFactor = 0;
    size_t _itemCount = 0;
};

HashSet::HashSet(float maxLoadFactor, size_t capacity) : _maxLoadFactor(maxLoadFactor) {
    assert(0 < _maxLoadFactor && _maxLoadFactor <= 1);
    _data.resize(capacity);
}

bool HashSet::add(const string& item) {
    if (_needRehash()) {
        _rehash();
    }

    size_t index = _hash(item);
    size_t hashNo = 0;
    while (true) {
        if (_data[index].empty) {
            _data[index].value = item;
            _data[index].empty = false;
            _itemCount++;
            return true;
        } else if (_data[index].deleted) {
            // skip
        } else {
            if (_data[index].value == item) {
                return false;
            }
        }
        index = _nextHash(index, ++hashNo);
    }
}

bool HashSet::remove(const string& item) {
    size_t index = _hash(item);
    size_t hashNo = 0;
    while (true) {
        if (_data[index].empty) {
            return false;
        } else if (_data[index].deleted) {
            // skip
        } else {
            if (_data[index].value == item) {
                _data[index].deleted = true;
                return true;
            }
        }
        index = _nextHash(index, ++hashNo);
    }
}

bool HashSet::has(const string& item) const {
    size_t index = _hash(item);
    size_t hashNo = 0;
    while (true) {
        if (_data[index].empty) {
            return false;
        } else if (_data[index].deleted) {
            // skip
        } else {
            if (_data[index].value == item) {
                return true;
            }
        }
        index = _nextHash(index, ++hashNo);
    }
}

float HashSet::_getLoadFactor() const {
    return (float) _itemCount / _data.size();
}

bool HashSet::_needRehash() const {
    return _maxLoadFactor * _data.size() <= _itemCount;
}

size_t HashSet::_hash(const string& item) const {
    return _hash(item, _data.size());
}

size_t HashSet::_hash(const string& item, size_t m) const {
    static const size_t a = 3;
    size_t hash = 0;
    for (char ch : item) {
        hash += ch;
        hash *= a;
    }
    return hash % m;
}

size_t HashSet::_nextHash(size_t previousHash, size_t index) const {
    return _nextHash(previousHash, index, _data.size());
}

size_t HashSet::_nextHash(size_t previousHash, size_t index, size_t m) const {
    return (previousHash + index + 1) % m;
}

void HashSet::_rehash() {
    HashSet newSet(_maxLoadFactor, _data.size() * 2);
    for (const Entry& entry : _data) {
        if (!entry.empty && !entry.deleted) {
            newSet.add(entry.value);
        }
    }
    _itemCount = newSet._itemCount;
    _data = move(newSet._data);
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
            default:
                break;
        }
        cout << (success ? "OK" : "FAIL") << endl;
    }

    return 0;
}
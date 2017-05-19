/*
 * Задача 2. Порядок обхода (3 балла)
Дано число N < 106    и последовательность целых чисел из [-231 ..231 ] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
 */

/*
 * 2_1. Выведите элементы в порядке in-order (слева направо).
 */

/*
in:
    3
    2 1 3
out:
    1 2 3
 */

/*
in:
    3
    1 2 3
out:
    1 2 3
 */

/*
in:
    3
    3 1 2
out:
    1 2 3
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;


template<typename T>
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);

    void add(T item);
    vector<T> makeInOrderTraverse() const;

private:
    struct Entry {
        explicit Entry(T value) : value(value) {}

        T value;
        Entry* left = nullptr;
        Entry* right = nullptr;
    };

    vector<Entry*> _makeInOrderEntryTraverse() const;

    Entry* root = nullptr;
};

template<typename T>
BinaryTree<T>::BinaryTree() {
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    vector<Entry*> inOrderEntryTraverse = _makeInOrderEntryTraverse();
    for (Entry* entry : inOrderEntryTraverse) {
        delete entry;
    }
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) : root(other.root) {
}

template<typename T>
void BinaryTree<T>::add(T item) {
    if (root == nullptr) {
        root = new Entry(item);
    } else {
        Entry* currentEntry = root;
        while (true) {
            if (currentEntry->value <= item) {
                if (currentEntry->right == nullptr) {
                    currentEntry->right = new Entry(item);
                    break;
                } else {
                    currentEntry = currentEntry->right;
                }
            } else {
                if (currentEntry->left == nullptr) {
                    currentEntry->left = new Entry(item);
                    break;
                } else {
                    currentEntry = currentEntry->left;
                }
            }
        }
    }
}

template<typename T>
vector<T> BinaryTree<T>::makeInOrderTraverse() const {
    vector<T> result;

    vector<Entry*> inOrderEntryTraverse = _makeInOrderEntryTraverse();
    result.reserve(inOrderEntryTraverse.size());
    for (Entry* entry : inOrderEntryTraverse) {
        result.push_back(entry->value);
    }

    return result;
}

template<typename T>
vector<typename BinaryTree<T>::Entry*> BinaryTree<T>::_makeInOrderEntryTraverse() const {
    vector<Entry*> result;

    Entry* currentEntry = root;
    stack<Entry*> s;
    while (!s.empty() || currentEntry != nullptr) {
        if (currentEntry != nullptr) {
            s.push(currentEntry);
            currentEntry = currentEntry->left;
        } else {
            currentEntry = s.top();
            s.pop();
            result.push_back(currentEntry);
            currentEntry = currentEntry->right;
        }
    }

    return result;
}


int main() {
    size_t n;
    cin >> n;

    BinaryTree<int> tree;
    for (size_t i = 0; i < n; i++) {
        int t;
        cin >> t;
        tree.add(t);
    }

    vector<int> result = tree.makeInOrderTraverse();
    for (int it : result) {
        cout << it << ' ';
    }

    return 0;
}
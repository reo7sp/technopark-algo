/*
 * Задача 3. Декартово дерево (4 балла)
Дано число N < 10^6    и последовательность пар целых чисел из [-2^31 ..2^31 ] длиной N. Построить декартово дерево из N узлов, характеризующихся парами чисел {X i,  Y i}  . Каждая пара чисел {X i,  Y i}  определяет ключ X i  и приоритет Y i  в декартовом дереве. Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
● При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
Построить также наивное дерево поиска по ключам X i  методом из задачи 2.
 */

/*
 * 3_1.  Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.
 */

/*
in:
    10
    5 11
    18 8
    25 7
    50 12
    30 30
    15 15
    20 10
    22 5
    40 20
    45 9
out:
    2
 */

/*
in:
    10
    38 19
    37 5
    47 15
    35 0
    12 3
    0 42
    31 37
    21 45
    30 26
    41 6
out:
    2
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


template<typename T>
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);

    void add(T item);
    size_t getHeight() const;

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

template<typename T>
size_t BinaryTree<T>::getHeight() const {
    if (root == nullptr) {
        return 0;
    }

    size_t maxHeight = 1;
    queue<pair<Entry*, size_t>> q;

    q.push(make_pair(root, 1));

    while (!q.empty()) {
        pair<Entry*, size_t> t = q.front();
        Entry* currentEntry = t.first;
        size_t currentHeight = t.second;
        q.pop();
        if (maxHeight < currentHeight) {
            maxHeight = currentHeight;
        }
        if (currentEntry->left != nullptr) {
            q.push(make_pair(currentEntry->left, currentHeight + 1));
        }
        if (currentEntry->right != nullptr) {
            q.push(make_pair(currentEntry->right, currentHeight + 1));
        }
    }

    return maxHeight;
}


template<typename T, typename K>
class Treap {
public:
    Treap();
    ~Treap();
    Treap(const Treap& other);

    void add(T value, K priority);
    size_t getHeight() const;

private:
    struct Entry {
        explicit Entry(T value, K priority) : value(value), priority(priority) {}

        T value;
        K priority;
        Entry* left = nullptr;
        Entry* right = nullptr;
    };

    pair<Entry*, Entry*> _split(Entry* tree, T value);
    Entry* _merge(Entry* leftTree, Entry* rightTree);
    vector<Entry*> _makeInOrderEntryTraverse() const;

    Entry* root = nullptr;
};

template<typename T, typename K>
Treap<T, K>::Treap() {
}

template<typename T, typename K>
Treap<T, K>::~Treap() {
    vector<Entry*> inOrderEntryTraverse = _makeInOrderEntryTraverse();
    for (Entry* entry : inOrderEntryTraverse) {
        delete entry;
    }
}

template<typename T, typename K>
Treap<T, K>::Treap(const Treap& other) : root(other.root) {
}

template<typename T, typename K>
void Treap<T, K>::add(T value, K priority) {
    if (root == nullptr) {
        root = new Entry(value, priority);
    } else {
        Entry* currentEntryParent = nullptr;
        bool currentEntryIsLeft = false;
        Entry* currentEntry = root;
        while (true) {
            if (currentEntry == nullptr) {
                break;
            }
            if (currentEntry->priority < priority) {
                break;
            }
            if (currentEntry->value <= value) {
                currentEntryParent = currentEntry;
                currentEntryIsLeft = false;
                currentEntry = currentEntry->right;
            } else {
                currentEntryParent = currentEntry;
                currentEntryIsLeft = true;
                currentEntry = currentEntry->left;
            }
        }

        Entry* newEntry = new Entry(value, priority);
        auto splits = _split(currentEntry, value);
        newEntry->left = splits.first;
        newEntry->right = splits.second;

        if (currentEntryParent) {
            if (currentEntryIsLeft) {
                currentEntryParent->left = newEntry;
            } else {
                currentEntryParent->right = newEntry;
            }
        } else {
            root = newEntry;
        }
    }
}

template<typename T, typename K>
pair<typename Treap<T, K>::Entry*, typename Treap<T, K>::Entry*> Treap<T, K>::_split(typename Treap<T, K>::Entry* tree, T value) {
    if (tree == nullptr) {
        return make_pair(nullptr, nullptr);
    } else {
        if (tree->value <= value) {
            auto splits = _split(tree->right, value);
            tree->right = splits.first;
            return make_pair(tree, splits.second);
        } else {
            auto splits = _split(tree->left, value);
            tree->left = splits.second;
            return make_pair(splits.first, tree);
        }
    }
}

template<typename T, typename K>
typename Treap<T, K>::Entry* Treap<T, K>::_merge(typename Treap<T, K>::Entry* leftTree, typename Treap<T, K>::Entry* rightTree) {
    if (leftTree == nullptr || rightTree == nullptr) {
        return leftTree == nullptr ? rightTree : leftTree;
    } else {
        if (leftTree->priority > rightTree->priority) {
            leftTree->right = _merge(leftTree->right, rightTree);
            return leftTree;
        } else {
            rightTree->left = _merge(leftTree, rightTree->left);
            return rightTree;
        }
    }
}

template<typename T, typename K>
vector<typename Treap<T, K>::Entry*> Treap<T, K>::_makeInOrderEntryTraverse() const {
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

template<typename T, typename K>
size_t Treap<T, K>::getHeight() const {
    if (root == nullptr) {
        return 0;
    }

    size_t maxHeight = 1;
    queue<pair<Entry*, size_t>> q;

    q.push(make_pair(root, 1));

    while (!q.empty()) {
        pair<Entry*, size_t> t = q.front();
        Entry* currentEntry = t.first;
        size_t currentHeight = t.second;
        q.pop();
        if (maxHeight < currentHeight) {
            maxHeight = currentHeight;
        }
        if (currentEntry->left != nullptr) {
            q.push(make_pair(currentEntry->left, currentHeight + 1));
        }
        if (currentEntry->right != nullptr) {
            q.push(make_pair(currentEntry->right, currentHeight + 1));
        }
    }

    return maxHeight;
}


int main() {
    size_t n;
    cin >> n;

    BinaryTree<int> tree;
    Treap<int, int> treap;
    for (size_t i = 0; i < n; i++) {
        int x, y;
        cin >> x;
        cin >> y;
        treap.add(x, y);
        tree.add(x);
    }

    int heightDiff = (int) tree.getHeight() - (int) treap.getHeight();
    cout << heightDiff << endl;

    return 0;
}

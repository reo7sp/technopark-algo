/*
 * Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
Формат входных данных:
На вход подается количество кубиков N.
Формат выходных данных:
Вывести число различных пирамид из N кубиков.
 */

/*
 * 6_2. Широкая пирамида.  Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
 */

#include <iostream>
#include <cassert>

using namespace std;


int countPossiblePiramyds(int n, int minCubesOnLevel = 0) {
    assert(n >= 1);
    assert(minCubesOnLevel >= 0);
    if (n < minCubesOnLevel) {
        return 0;
    }
    if (n == minCubesOnLevel) {
        return 1;
    }
    int result = 0;
    for (int i = minCubesOnLevel + 1; i <= n; i++) {
        result += countPossiblePiramyds(n - minCubesOnLevel, i);
    }
    return result;
}


int main() {
    int n;
    cin >> n;

    cout << countPossiblePiramyds(n);

    return 0;
}


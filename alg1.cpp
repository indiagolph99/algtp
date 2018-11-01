/* Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
Необходимо найти первую пару индексов i0 и j0, , такую что
A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
Время работы - O(n). n ≤ 100000.
*/

#include <iostream>
#include <assert.h>

struct Pair {
    size_t first;
    size_t second;
};

struct Pair max_search(int* a, int* b, int size) {
    struct Pair pair = {0, 0};
    int a_res = 0;
    int a_ans = 0;
    int b_ans = 0;
    int max = 0;
    max = a[0] + b[0];
    for (int i = 0; i < size; i++) {
        if (a[i] > a[a_res]) {
            a_res = i;
        }

        if (a[a_res] + b[i] > max) {
            max = a[a_res] + b[i];
            pair.first = a_res;
            pair.second = i;
        }
    }
    return pair;
}

int main() {
    int n = 0;
    int *a = nullptr;
    int *b = nullptr;
    struct Pair pair = {};
    std::cin >> n;
    a = new int[n];
    b = new int[n];
    assert((a != NULL) && (b != NULL));

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    pair = max_search(a, b, n);
    std::cout << pair.first << ' ' << pair.second << '\n';
    delete[] a;
    delete[] b;

    return 0;
}

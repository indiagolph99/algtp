// Дан массив неотрицательных целых 64-разрядных чисел.
// Количество чисел не больше
// 1000000. Отсортировать массив методом MSD по битам (бинарный QuickSort).

#include <iostream>
#include "assert.h"
#include <algorithm>

void partition(unsigned long long int *arr, int left, int right, int b) {
     int i = left;
     if (right <= left || b < 0) {
		return;
    }

     for (int j = left; j <= right; j++)
     {
         if (!(arr[j] & ((unsigned long long int)1 << b)))
         {
             std::swap(arr[i], arr[j]);
             i++;
         }
     }
     partition(arr, left, i - 1, b - 1);
     partition(arr, i, right, b - 1);
}

int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0);
    unsigned long long int arr[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    partition(arr, 0, n - 1, 63);  // unsigned long long size = 64 bits

    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i]  << " ";
    }
    std::cout << '\n';
}
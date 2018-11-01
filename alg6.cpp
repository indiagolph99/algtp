// Даны неотрицательные целые числа n, k и массив целых чисел из диапазона
// [0..109] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы
// стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
// Напишите нерекурсивный алгоритм.
// Дополнительная память: none.
// Cреднее время работы: O(n).


#include <iostream>
#include <assert.h>
#include <algorithm> // for std::swap

int med (int* arr, int left, int mid, int right)
{
    if (arr[left] > arr[mid]) {
        if (arr[right] > arr[left])
        return left;
        return (arr[mid] > arr[right]) ? mid : right;
    }

    if (arr[right] > arr[mid])
    return mid;
    return (arr[left] > arr[right]) ? left : right;
}

int partition(int *arr, int left, int right) {
     int pivot = med(arr, left, (left + right) / 2, right);
     std::swap(arr[pivot], arr[right]);
     int x = arr[right], i = left;
     for (int j = left; j <= right - 1; j++)
     {
         if (arr[j] <= x)
         {
             std::swap(arr[i], arr[j]);
             i++;
         }
     }
     std::swap(arr[i], arr[right]);
     return i;
}

int k_statistic(int* arr, int k, int size) {
    int left = 0, right = size;
    while (true) {
        if (left == right) {
            return arr[left];
        }

        int mid = partition(arr, left, right);

        if (mid == k) {
            return arr[mid];
        }
        else if (k < mid) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
}


int main() {
    int n = 0;
    int k = 0;

    std::cin >> n;
    std::cin >> k;
    assert(n > 0 && k >= 0 && k < n);
    int arr[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << k_statistic(arr, k, n - 1) << '\n';

}

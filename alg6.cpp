// Даны неотрицательные целые числа n, k и массив целых чисел из диапазона
// [0..109] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы
// стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
// Напишите нерекурсивный алгоритм.
// Дополнительная память: none.
// Cреднее время работы: O(n).


#include <iostream>
#include <cassert>
#include <algorithm> // for std::swap

template <typename T> size_t med (T* arr, size_t left, size_t mid, size_t right)
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

template <typename T> size_t partition(T *arr, size_t left, size_t right) {
     size_t pivot = med(arr, left, (left + right) / 2, right);
     std::swap(arr[pivot], arr[right]);
     T x = arr[right];
     size_t i = left;
     for (size_t j = left; j <= right - 1; j++)
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

template <typename T> size_t k_statistic(T* arr, size_t k, size_t size) {
    size_t left = 0, right = size;
    while (true) {
        if (left == right) {
            return arr[left];
        }

        size_t mid = partition(arr, left, right);

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
    size_t n = 0;
    size_t k = 0;

    std::cin >> n;
    std::cin >> k;
    assert(n > 0 && k >= 0 && k < n);
    int arr[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << k_statistic(arr, k, n - 1) << '\n';

}

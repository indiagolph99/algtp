// Дан массив неотрицательных целых 64-разрядных чисел.
// Количество чисел не больше
// 1000000. Отсортировать массив методом MSD по битам (бинарный QuickSort).

#include <iostream>
#include <cassert>
#include <algorithm>
void binary_sort(uint64_t *arr,
                 size_t left, size_t right, size_t b) {
  size_t i = left;
  if (right <= left || b < 0) {
    return;
  }

  for (size_t j = left; j <= right; j++) {
    if (!(arr[j] & static_cast<int64_t>(1) << b)) {
      std::swap(arr[i], arr[j]);
      i++;
    }
  }
  binary_sort(arr, left, i - 1, b - 1);
  binary_sort(arr, i, right, b - 1);
}

int main() {
  size_t n = 0;
  std::cin >> n;
  assert(n > 0);
  auto *arr = new uint64_t[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  binary_sort(arr, 0, n - 1, 63);  // unsigned long long size = 64 bits

  for (size_t i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  std::cout << '\n';
}

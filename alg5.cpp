#include <iostream>

int min (int a, int b) {
    return a < b ? a : b;
}

bool compare(std::pair<int, bool> a, std::pair<int, bool> b) {
    return a.first > b.first;
}

template <typename T, typename Compare>
void merge(T* arr, int left, int mid, int right, Compare cmp) {
    int it1 = 0, it2 = 0;
    T* res = new T[right - left];

    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (cmp(arr[left + it1], arr[mid + it2])) {
            res[it1 + it2] = arr[mid + it2];
            it2++;
        }
        else {
            res[it1 + it2] = arr[left + it1];
            it1++;
        }
    }

    while (left + it1 < mid) {
        res[it1 + it2] = arr[left + it1];
        it1++;
    }

    while (mid + it2 < right) {
        res[it1 + it2] = arr[mid + it2];
        it2++;
    }

    for (int i = 0; i < it1 + it2; i++) {
        arr[left + i] = res[i];
    }
}

template <typename T, typename Compare>
void mergeSort(T* arr, int left, int right, Compare cmp) {
    int n = right - left;
    for (int i = 1; i <= n; i *= 2) {
        for (int j = 0; j < n - i; j += 2 * i) {
            merge(arr, left + j, left + j + i, min(left + j + 2 * i, right), cmp);
        }
    }
}

int lenSegment(std::pair<int, bool>* arr, int n) {
    int res = 0;
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (count == 1) {
            res += arr[i].first - arr[i - 1].first;
        }
        arr[i].second ? count++ : count--;
    }
    return res;
}

int main() {
    int n;
    std::cin >> n;

    std::pair<int, bool>* arr = new std::pair<int, bool>[n * 2];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i * 2].first >> arr[i * 2 + 1].first;
        arr[i * 2].second = true;
        arr[i * 2 + 1].second = false;
    }
    mergeSort(arr, 0, n * 2, compare);

    std::cout << lenSegment(arr, n * 2);
    return 0;
}
#include <iostream>
#include <cassert>
#include <functional>

#define BUFFSIZE 64

template <typename T>
class Heap {
public:
    Heap(
            std::function<bool(T, T)> cmp = [](T a, T b){return a < b;}) : _size(0), _buffSize(BUFFSIZE), cmp(cmp) {
        arr = new T[_buffSize];
    }

    Heap(long size,
         std::function<bool(T, T)> cmp = [](T a, T b){return a < b;}
    ) : _size(0), _buffSize(size), cmp(cmp) {
        arr = new T[_buffSize];
    }

    ~Heap() {
        delete[] arr;
    }

    long size() const;
    bool empty() const;

    void siftDown(const long i);
    void siftUp(const long i);
    void buildHeap(T* newArr, const long newSize);
    void add(const T elem);

    T seeMax() const;
    T extractMax();

private:
    void expand();

    T* arr;
    long _size;
    long _buffSize;
    std::function<bool(T, T)> cmp;
};

template <typename T>
long Heap<T>::size() const {
    return _size;
}

template <typename T>
bool Heap<T>::empty() const {
    return _size ? false : true;
}

template <typename T>
void Heap<T>::siftDown(long i) {
    bool key = true;
    while (key) {
        long left = i * 2 + 1;
        long right = i * 2 + 2;
        long largest = i;
        if (left < _size && cmp(arr[left], arr[largest])) {
            largest = left;
        }
        if (right < _size && cmp(arr[right], arr[largest])) {
            largest = right;
        }
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            i = largest;
        } else {
            key = false;
        }
    }
}

template <typename T>
void Heap<T>::siftUp(const long i) {
    long index = i;
    while (index > 0) {
        long parent = (index - 1) / 2;
        if (!cmp(arr[index], arr[parent])) {
            return;
        }
        std::swap(arr[index], arr[parent]);
        index = parent;
    }
}

template <typename T>
void Heap<T>::buildHeap(T* newArr, const long newSize) {
    if (arr != nullptr) {
        delete [] arr;
        _buffSize = newSize * 2;
        _size = newSize;
        arr = new T[_buffSize];
        for (long i = 0; i < _size; i++) {
            arr[i] = newArr[i];
        }
    }
    for (long i = _size / 2 - 1; i >= 0; i--) {
        siftDown(i);
    }
}

template <typename T>
void Heap<T>::expand() {
    T* tmp = new T[_buffSize * 2];
    for (long i = 0; i < _buffSize; i++) {
        tmp[i] = arr[i];
    }
    _buffSize *= 2;
    delete [] arr;
    arr = tmp;
}

template <typename T>
void Heap<T>::add(const T elem) {
    if (_size == _buffSize) {
        expand();
    }
    arr[_size] = elem;
    _size++;
    siftUp(_size - 1);
}

template <typename T>
T Heap<T>::seeMax() const {
    assert(!empty());
    return arr[0];
}

template <typename T>
T Heap<T>::extractMax() {
    assert(!empty());
    T result = arr[0];
    arr[0] = arr[_size - 1];
    _size--;
    if (!empty()) {
        siftDown(0);
    }
    return result;
}

void updateWindow(Heap<std::pair<int, int>>& window, long i, long k, std::pair<int, int> elem) {
    while (!window.empty() && (window.seeMax().second <= (i - k))) { // добавляю новый элемент и убираю максимума, которые не попадают в окно
        window.extractMax();
    }
    window.add(elem);
}

int main() {
    long n = 0, k = 0;
    std::cin >> n;
    std::pair<int, int>* arr = new std::pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i].first;
        arr[i].second = i;
    }
    std::cin >> k;
    Heap<std::pair<int, int>> window(
            [](std::pair<int, int> a, std::pair<int, int> b) {
                return a.first > b.first;
            });
    window.buildHeap(arr, k);
    std::cout << window.seeMax().first << " ";
    for (long i = k; i < n; i++) {
        updateWindow(window, i, k, arr[i]);
        std::cout << window.seeMax().first << " ";
    }
    return 0;
}
/*Дан массив целых чисел A[0..n), n не превосходит 100 000.
Так же задан размер некотрого окна (последовательно расположенных элементов
массива)
в этом массиве k, k<=n. Требуется для каждого положения окна (от 0 и до n-k) выв
ести значение максимума в окне. Скорость работы O(n log n), память O(n).
*/
#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

template <class T>
class Heap {
    T *buf;
    size_t curr_size;
    size_t heap_size;

 public:
    Heap(): curr_size(0), heap_size(8) { buf = new T[8]; }
    explicit Heap(const T size) {
        curr_size = 0; heap_size = size; buf = new T[size];
    }
    ~Heap() { delete[] buf; }

    void sift_down(T* array, size_t index) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t j = index;
        if (left < curr_size && array[buf[left]] > array[buf[index]]) {
            j = left;
        }  // instead of values, indexes of max are stored
        if (right < curr_size && array[buf[right]] > array[buf[j]]) {
            j = right;
        }
        if (j != index) {
            std::swap(buf[index], buf[j]);
            sift_down(array, j);
        }
    }

    void sift_up(T* array, size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (array[buf[index]] <= array[buf[parent]]) {
                return;
            }
            std::swap(buf[index], buf[parent]);
            index = parent;
        }
    }

    void append(T* array, T elem) {
        curr_size++;
        buf[curr_size - 1] = elem;
        sift_up(array, curr_size - 1);
    }

    T extract_max(T* array) {
        assert(curr_size != 0);
        T max = buf[0];
        buf[0] = buf[curr_size - 1];
        curr_size--;
        if (curr_size != 0) {
            sift_down(array, 0);
        }
        return max;
    }

    T top() {
        return buf[0];
    }
};

template<typename T> T* get_max(int input_size, int window_size, T* array) {
    Heap<T> H(input_size);

    for (size_t i = 0; i < window_size; i++) {
        H.append(array, i);  // instead of values, indexes of are stored
    }

    T * result = new T[input_size - window_size + 1];
    int result_size = 0;
    result[0] = array[H.top()];

    for (size_t i = 1; i <= input_size - window_size; i++) {
        H.append(array, i + window_size - 1);
        while (H.top() < i) {       // remove all maxes outside the window
            H.extract_max(array);
        }
        result[i] = array[H.top()];
    }

    return result;
}

int main() {
    int input_size = 0;
    int window_size = 0;
    int* result = nullptr;
    int* array = nullptr;
    std::cin >> input_size;
    assert(input_size > 0);
    array = new int[input_size];
    for (size_t i = 0; i < input_size; i++) {
        std::cin >> array[i];
    }
    std::cin >> window_size;
    assert(window_size <= input_size && window_size != 0);

    result = get_max(input_size, window_size, array);

    for (size_t i = 0; i <= input_size - window_size; i++) {
        std::cout << result[i] << ' ';
    }
    std::cout << '\n';
    delete[] result;
    delete[] array;
    return 0;
}

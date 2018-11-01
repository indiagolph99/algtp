/* Реализовать очередь с динамическим зацикленным буфером.

Обрабатывать команды push back и pop front.
*/
#include <iostream>
#include <assert.h>
#include <string.h>

template <class T>
class Queue {
    T *buf;
    size_t buf_len;
    size_t curr_len;
    size_t tail;
    size_t head;
    size_t buf_cap;
    size_t curr_cap;
public:
    Queue(): buf_len(0), curr_len(0), tail(0), head(0), buf_cap(8), curr_cap(8) {buf = new T[8];}

    ~Queue() { delete[] buf;}

    void extend_buf() {
        T* new_buf = new T[buf_cap * 2];
        for (int i = 0; i < buf_cap; i++) {
            new_buf[i] = buf[i];
        }
        buf_cap *= 2;
        delete[] buf;
        buf = new_buf;
    };
    void push(const T& elem) {
        bool bufrealloc = false;
        bool ringrealloc = false;
        if (curr_cap != buf_cap) {
            bufrealloc = (tail == 0);
            ringrealloc = false;
        } else if (curr_cap == curr_len) {
            bufrealloc = true;
            ringrealloc = (tail == 0);
        } else {
            bufrealloc = false;
            ringrealloc = false;
        }

        if (bufrealloc) {
            tail = buf_cap;
            extend_buf(); // double buffer capacity in that func and update len info
            if (ringrealloc) {
                curr_cap = buf_cap;
            }
        }

        buf[tail] = elem;
        buf_len++;
        if (tail < curr_cap) {
            curr_len++;
        }
        tail = (tail + 1) % buf_cap;
    };

    T pop() {
        if (buf_len == 0) {
            return -1;
        }
        T elem = buf[head];
        buf[head] = -1;
        buf_len--;
        curr_len--;
        if (curr_len == 0 && buf_len != 0) {
            head = curr_cap;
            curr_len = buf_len;
            curr_cap = buf_cap;
        } else {
            head = (head + 1) % curr_cap;
        }
        return elem;
    };
};



int main() {
    int n = 0;
    int action = 0;
    int value = 0;
    std::string answer = "YES";
    std::cin >> n;
    assert(n != 0);
    Queue<int> Q;
    for (int i = 0; i < n; i++) {
        std::cin >> action >> value;
        switch (action) {
        case 2:
            if (Q.pop() != value) { answer = "NO";}
            break;
        case 3:
            Q.push(value);
            break;
        }
    }
    std::cout << answer << '\n';

    return 0;
}

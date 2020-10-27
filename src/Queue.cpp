#ifndef QUEUE_CPP
#define QUEUE_PP
#include "D_Array.cpp"
#include <cmath>

class Queue {
public:
    Queue(): buffer(nullptr), buffer_size(0), head(0), tail(0), size(0) {}

    ~Queue() = default;

    Queue(const Queue &other) = delete;

    Queue &operator=(const Queue &other) = delete;

    void push(const int elem) {
        if (size == buffer_size) {
            increase_buffer();
        }
        tail = (tail + 1) % buffer_size;
        buffer[tail] = elem;
        ++size;
    }

    int pop(const int elem) {
        if (size == 0) {
            return -1;
        }
        int result = buffer[head];
        head = (head + 1) % buffer_size;
        --size;
        return result;
    }

    void increase_buffer() {
        int *temp = buffer;
        if (buffer_size == 0) {
            buffer = new int [1];
        } else {
            buffer = new int [buffer_size * 2];
        }

        for (int i = 0; i < buffer_size; ++i) {
            buffer[i] = temp[head++ % buffer_size];
        }
        head = 0;
        tail = buffer_size - 1;

        if (buffer_size == 0) {
            buffer_size = 1;
        } else {
            buffer_size *= 2;
        }
        delete [] temp;
    }

    bool is_empty() const {
        return head == tail;
    }
private:
    int *buffer;
    int buffer_size;
    int head;
    int tail;
    int size;
};

#endif
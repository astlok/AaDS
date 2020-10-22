#ifndef QUEUE_CPP
#define QUEUE_PP
#include "D_Array.cpp"
#include <cmath>

class Queue {
public:
    Queue(): data(), free_cell(-1), head(0), tail(0) {}

    ~Queue() = default;

    Queue(const Queue &other) = delete;

    Queue &operator=(const Queue &other) = delete;

    void push(const int elem) {
        if (head == tail + 1) {
            data.move(head, tail);
            tail = data.size() - 1;
            head = 0;
            free_cell = -1;
        }
        if (free_cell != -1) {
            data[free_cell] = elem;
            tail = free_cell;
            if (data[free_cell + 1] == -1) {
                free_cell++;
            }
        } else {
            data.add(elem);
            tail = data.size();
        }
    }

    int pop(const int elem) {
        if (data.is_empty() || data[head] != elem) {
            return -1;
        }
        int result = data[head];
        data[head++] = -1;
        if (free_cell == -1 || free_cell > (head - 1)) {
            free_cell = head - 1;
        }
        if (head == tail || (head >= tail && data[tail] == -1)) {
            head = tail = free_cell = 0;
        }
        return result;
    }

private:
    D_Array data;
    int free_cell;
    int head;
    int tail;
};

#endif
#ifndef D_ARRAY_CPP
#define D_ARRAY_CPP
#include <cassert>

class D_Array {
public:
    D_Array(): buffer(nullptr), real_size(0), buffer_size(0) {}

    ~D_Array() {
        delete [] buffer;
    };

    D_Array(const D_Array &other) = delete;

    D_Array &operator=(const D_Array &other) = delete;

    int size() const {
        return real_size;
    }

    int operator[](int index) const {
        assert(index >= 0 && index < real_size && buffer != nullptr);
        return buffer[index];
    }

    int &operator[] (int index) {
        assert(index >= 0 && index < real_size && buffer != nullptr);
        return buffer[index];
    }

    void add(int data) {
        if (real_size == buffer_size) {
            increase_buffer();
        }
        buffer[real_size++] = data;
    }

    void increase_buffer() {
        int *temp = buffer;
        if (buffer_size == 0) {
            buffer = new int [1];
        } else {
            buffer = new int [buffer_size * 2];
        }
        for (int i = 0; i < buffer_size; ++i) {
            buffer[i] = temp[i];
        }
        if (buffer_size == 0) {
            buffer_size = 1;
        } else {
            buffer_size *= 2;
        }
        delete [] temp;
    }

    bool is_empty() const {
        return real_size == 0;
    }

    void move(int head, int tail) {
        D_Array temp;
        for (int i = 0; i < head; ++i) {
            temp.add((*this)[i]);
        }
        for (int i = 0; i < real_size - head; ++i) {
            (*this).buffer[i] = (*this).buffer[i + head];
        }
        for (int i = 0; i < temp.size(); ++i) {
            (*this).buffer[i + real_size - head] = temp[i];
        }
        increase_buffer();
    }
private:
    int *buffer;
    int real_size;
    int buffer_size;
};
#endif

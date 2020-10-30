#ifndef D_ARRAY_CPP
#define D_ARRAY_CPP
#include <cassert>

template<class T>
class D_Array {
public:
    D_Array(): buffer(nullptr), real_size(0), buffer_size(0) {}

    explicit D_Array(int size):  real_size(size), buffer_size(0) {
        buffer_size = size;
        buffer = new T [buffer_size];
    }

    ~D_Array() {
        delete [] buffer;
    };

    D_Array(const D_Array &other) = delete;

    D_Array &operator=(const D_Array &other) = delete;

    int size() const {
        return real_size;
    }
    int buff_size() const {
        return buffer_size;
    };

    T operator[](int index) const {
        assert(index >= 0 && index < real_size && buffer != nullptr);
        return buffer[index];
    }

    T &operator[] (int index) {
        assert(index >= 0 && index < real_size && buffer != nullptr);
        return buffer[index];
    }

    void add(T data) {
        if (real_size == buffer_size) {
            increase_buffer();
        }
        buffer[real_size++] = data;
    }

    void increase_buffer() {
        T *temp = buffer;
        if (buffer_size == 0) {
            buffer = new T [1];
        } else {
            buffer = new T [buffer_size * 2];
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

    void swap(int first, int second) {
        T temp = buffer[first];
        buffer[first] = buffer[second];
        buffer[second] = temp;
    }

    void pop() {
        real_size--;
    }

private:
    T *buffer;
    int real_size;
    int buffer_size;
};
#endif

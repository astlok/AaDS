#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define MAX_ALPHA 0.75

enum state_t {
    EMPTY,
    DELETE,
    NOT_EMPTY
};

struct Elem {
    std::string key;
    state_t state;

    Elem &operator=(const Elem &rhs) = default;
};

size_t hash_str(const std::string &str) {
    size_t hash = 0;
    size_t a = 59;
    for (char ch: str) {
        hash = hash * a + ch;
    }
    return hash;
}

class HashTable {

public:
    HashTable() : buckets_count(8), items_count(0), elems(buckets_count) {
        for (auto elem: elems) {
            elem.state = EMPTY;
        }
    }

    bool insert(const std::string &str) {
        if (has(str)) {
            return false;
        }

        if (get_alpha() >= MAX_ALPHA) {
            rehashed();
        }

        size_t ind = hash_str(str) % buckets_count;
        size_t prev_ind = 0;
        for (size_t i = 0; i < buckets_count; ++i) {
            if (elems[ind].state == EMPTY || elems[ind].state == DELETE) {
                elems[ind] = {str, NOT_EMPTY};
                ++items_count;
                return true;
            }
            prev_ind = ind;
            ind = (prev_ind + i + 1) % buckets_count;
        }
        return false;
    }

    bool erase(const std::string& str) {
        if (!has(str)) {
            return false;
        }

        size_t ind = hash_str(str) % buckets_count;
        size_t prev_ind = 0;
        for (size_t i = 0; i < buckets_count; ++i) {
            if (elems[ind].state == EMPTY) {
                return false;
            }
            if (elems[ind].key == str) {
                elems[ind].state = DELETE;
                elems[ind].key = "";
                --items_count;
                return true;
            }
            prev_ind = ind;
            ind = (prev_ind + i + 1) % buckets_count;
        }
        return false;
    }

    bool has(const std::string &str) {
        size_t ind = hash_str(str) % buckets_count;
        size_t prev_ind = 0;
        for (size_t i = 0; i < buckets_count; ++i) {
            if (elems[ind].state == EMPTY) {
                return false;
            }
            if (elems[ind].key == str) {
                return true;
            }
            prev_ind = ind;
            ind = (prev_ind + i + 1) % buckets_count;
        }
        return false;
    }

private:
    double get_alpha() const {
        return double(items_count) / double(buckets_count);
    }

    void rehashed() {
        size_t new_buckets_count = buckets_count * 2;
        std::vector<Elem> new_elems(new_buckets_count);
        for (const auto& elem: elems) {
            size_t ind = hash_str(elem.key) % new_buckets_count;
            size_t prev_ind = 0;
            for (size_t i = 0; i < new_buckets_count; ++i) {
                if (new_elems[ind].state == EMPTY) {
                    break;
                }
                prev_ind = ind;
                ind = (prev_ind + i + 1) % new_buckets_count;
            }
            new_elems[ind] = elem;
        }
        elems = new_elems;
        buckets_count = new_buckets_count;
    }

    size_t buckets_count;
    size_t items_count;

    std::vector<Elem> elems;

};

void run(std::istream &is, std::ostream &os) {
    std::string key = "";
    char operation = '\0';

    HashTable htable;
    while (is >> operation >> key) {
        bool res = false;
        switch (operation) {
            case '+':
                res = htable.insert(key);
                break;
            case '-':
                res = htable.erase(key);
                break;
            case '?':
                res = htable.has(key);
                break;
            default:
                res = false;
        }
        if (res) {
            os << "OK" << std::endl;
        } else {
            os << "FAIL" << std::endl;
        }
    }
}

int main() {
    run(std::cin, std::cout);
    return 0;
}

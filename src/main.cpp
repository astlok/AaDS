// 4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая,
// то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
// Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
// а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность –
// все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
// а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.

#include <iostream>
#include <memory>
#include <sstream>
#include <cassert>

template <typename T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) const {
        if (l < r)
            return -1;
        if (l == r)
            return 0;
        return 1;
    }
};

template<typename T>
struct Node {
    Node(const T &key): key(key), left(nullptr), right(nullptr), height(1), nodes_count(1) {}

    T key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    size_t height;
    size_t nodes_count;
};

template<typename T, class Comparator=DefaultComparator<T>>
class AVLTree{
public:
    explicit AVLTree(Comparator comp = Comparator()): root(nullptr), comp(comp) {}

    size_t add(const T &key) {
        size_t position = 0;
        root = add_aux(root, key, position);
        return position;
    }

    bool has(const T &key) {
        std::shared_ptr<Node<T>> tmp = root;
        int res = comp(tmp->key, key);
        while (tmp != nullptr) {
            if (res == 0) {
                return true;
            } else if (res == -1) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }
        return false;
    }

    void del(const int number) {
        std::shared_ptr<Node<T>> node = get_node_by_number(root, number);
        if (node == nullptr) {
            return;
        }
        root = del_aux(root, node->key);
    }
private:
    std::shared_ptr<Node<T>> add_aux(std::shared_ptr<Node<T>> node, const T &key, size_t &position) {
        if (node == nullptr) {
            return std::make_shared<Node<T>>(key);
        }
        int res = comp(node->key, key);
        if (res == -1) {
            node->right = add_aux(node->right, key, position);
        } else {
            position += get_nodes_count(node->right) + 1;
            node->left = add_aux(node->left, key, position);
        }
        return balance(node);
    }

    std::shared_ptr<Node<T>> get_node_by_number(std::shared_ptr<Node<T>> node, int number) {
        if (number >= node->nodes_count) {
            return nullptr;
        }

        while (node) {
            int right_num = node->right ? node->right->nodes_count : 0;
            if (number == right_num) {
                return node;
            } else if (number > right_num){
                node = node->left;
                number = number - right_num - 1;
                continue;
            } else {
                node = node->right;
                continue;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Node<T>> del_aux(std::shared_ptr<Node<T>> node, const T &key) {
        if (node == nullptr) {
            return nullptr;
        }
        int res = comp(node->key, key);
        if (res == -1) {
            node->right = del_aux(node->right, key);
        } else if (res == 1) {
            node->left = del_aux(node->left, key);
        } else {
            std::shared_ptr<Node<T>> left = node->left;
            std::shared_ptr<Node<T>> right = node->right;

            if (right == nullptr) {
                return left;
            }

            std::shared_ptr<Node<T>> min = find_min(right);
            min->right = remove_min(right);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }

    size_t get_height(std::shared_ptr<Node<T>> node) {
        return node ? node->height : 0;
    }

    size_t get_nodes_count(std::shared_ptr<Node<T>> node) {
        return node ? node->nodes_count : 0;
    }

    void fix_height(std::shared_ptr<Node<T>> node) {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
    }

    void fix_node_count(std::shared_ptr<Node<T>> node) {
        node->nodes_count = get_nodes_count(node->left) + get_nodes_count(node->right) + 1;
    }

    int get_balance(std::shared_ptr<Node<T>> node) {
        return get_height(node->right) - get_height(node->left);
    }

    std::shared_ptr<Node<T>> balance(std::shared_ptr<Node<T>> node) {
        fix_height(node);
        fix_node_count(node);
        switch (get_balance(node)) {
            case 2: {
                if (get_balance(node->right) < 0)
                    node->right = rotate_right(node->right);
                return rotate_left(node);
            }
            case -2: {
                if (get_balance(node->left) > 0)
                    node->left = rotate_left(node->left);
                return rotate_right(node);
            }
            default:
                return node;
        }
    }
    std::shared_ptr<Node<T>> find_min(std::shared_ptr<Node<T>> node) {
        while(node->left) {
            node = node->left;
        }
        return node;
    }
    std::shared_ptr<Node<T>> remove_min(std::shared_ptr<Node<T>> node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = remove_min(node->left);
        return balance(node);
    }

    std::shared_ptr<Node<T>> rotate_left(std::shared_ptr<Node<T>> node) {
        std::shared_ptr<Node<T>> tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fix_height(node);
        fix_height(tmp);

        fix_node_count(node);
        fix_node_count(tmp);

        return tmp;
    }

    std::shared_ptr<Node<T>> rotate_right(std::shared_ptr<Node<T>> node) {
        std::shared_ptr<Node<T>> tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fix_height(node);
        fix_height(tmp);

        fix_node_count(node);
        fix_node_count(tmp);

        return tmp;
    }

    std::shared_ptr<Node<T>> root;
    Comparator comp;
};
void run(std::istream &is, std::ostream &os) {
    AVLTree<int> avlTree;

    int op;
    int key = 0;
    int n = 0;
    is >> n;
    for (int i = 0; i < n; ++i) {
        is >> op >> key;
        switch (op) {
            case 1: {
                os << avlTree.add(key) << std::endl;
                break;
            }
            case 2: {
                avlTree.del(key);
                break;
            }
        }
    }
}

void test1() {
    std::stringstream input;
    std::stringstream output;
    input << "5" << std::endl;
    input << "1 " << "100" << std::endl;
    input << "1 " << "200" << std::endl;
    input << "1 " << "50" << std::endl;
    input << "2 " << "1" << std::endl;
    input << "1 " << "150" << std::endl;
    run(input, output);
    assert(output.str() == "0\n0\n2\n1\n");
}

void test2() {
    std::stringstream input;
    std::stringstream output;
    input << "10" << std::endl;
    input << "1 " << "100" << std::endl;
    input << "2 " << "0" << std::endl;
    input << "1 " << "10" << std::endl;
    input << "1 " << "12" << std::endl;
    input << "1 " << "9" << std::endl;
    input << "1 " << "3" << std::endl;
    input << "2 " << "1" << std::endl;
    input << "1 " << "8" << std::endl;
    input << "2 " << "1" << std::endl;
    input << "1 " << "11" << std::endl;
    run(input, output);
    assert(output.str() == "0\n0\n0\n2\n3\n2\n1\n");
}

void test3() {
    std::stringstream input;
    std::stringstream output;
    input << "32" << std::endl;
    for (int i = 0; i < 20; ++i) {
        input << "1 " << i << std::endl;
    }
    for (int i = 0; i < 10; ++i) {
        input << "2 " << 0 << std::endl;
    }

    input << "1 " << "12" << std::endl;
    input << "1 " << "11" << std::endl;
    run(input, output);
    assert(output.str() == "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n1\n");
}

void test4() {
    std::stringstream input;
    std::stringstream output;
    input << "24" << std::endl;
    input << "1 " << "12" << std::endl;
    input << "1 " << "11" << std::endl;
    input << "1 " << "10" << std::endl;
    input << "1 " << "3" << std::endl;
    input << "1 " << "8" << std::endl;
    input << "1 " << "5" << std::endl;
    input << "1 " << "15" << std::endl;
    input << "1 " << "28" << std::endl;
    input << "1 " << "1" << std::endl;
    input << "1 " << "19" << std::endl;
    input << "1 " << "13" << std::endl;
    input << "1 " << "2" << std::endl;
    input << "1 " << "22" << std::endl;
    input << "1 " << "6" << std::endl;
    input << "2 " << "6" << std::endl;
    input << "1 " << "11" << std::endl;
    input << "2 " << "6" << std::endl;
    input << "2 " << "3" << std::endl;
    input << "2 " << "8" << std::endl;
    input << "1 " << "16" << std::endl;
    input << "1 " << "7" << std::endl;
    input << "1 " << "4" << std::endl;
    input << "1 " << "0" << std::endl;
    input << "1 " << "29" << std::endl;

    run(input, output);
    assert(output.str() == "0\n1\n2\n3\n3\n4\n0\n0\n8\n1\n3\n10\n1\n9\n6\n3\n8\n10\n14\n0\n");
}

int main() {
    run(std::cin, std::cout);
    test1();
    test2();
    test3();
    test4();
}

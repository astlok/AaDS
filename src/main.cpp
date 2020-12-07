//Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
//Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
//Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
//Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
//При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево
//по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева
//сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
//
//Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
//3_2. Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного
//дерева поиска. Вывести их разницу. Разница может быть отрицательна.

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <queue>

template<class T>
struct BTreeNode {
    BTreeNode(int value): left(nullptr), right(nullptr), value(value), last_node(true) {}
    BTreeNode *left;
    BTreeNode *right;

    bool last_node;

    T value;
};

template<class T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        if (l <= r)
            return false;
        return true;
    }
};

template<class T, class Comparator=DefaultComparator<T>>
class BinaryTree {
public:
    explicit BinaryTree(Comparator comp = Comparator()): root(nullptr), comp(comp) {}

    void add(T value) {
        if (root == nullptr) {
            root = new BTreeNode<T>(value);
            return;
        }
        BTreeNode<T> **cur_node = &root;
        while (true) {
            int comp_res = comp((*cur_node)->value, value);
            if (comp_res) {
                if ((*cur_node)->last_node || (*cur_node)->left == nullptr) {
                    (*cur_node)->left = new BTreeNode<T>(value);
                    (*cur_node)->last_node = false;
                    break;
                } else {
                    cur_node = &((*cur_node)->left);
                }
            } else {
                if ((*cur_node)->last_node || (*cur_node)->right == nullptr) {
                    (*cur_node)->right = new BTreeNode<T>(value);
                    (*cur_node)->last_node = false;
                    break;
                } else {
                    cur_node = &((*cur_node)->right);
                }
            }
        }
    }

    void print_tree() {
        std::shared_ptr<std::stack<BTreeNode<T>*>> s = get_post_order_stack();
        while (!s->empty()) {
            std::cout << s->top()->value << " ";
            s->pop();
        }
    }

    int max_tree_width() {
        int max_width = 0;
        std::queue<BTreeNode<T>*> layer;
        layer.push(root);

        while (!layer.empty()) {
            if (layer.size() > max_width) {
                max_width = layer.size();
            }

            size_t size = layer.size();
            for (size_t i = 0; i < size; ++i) {
                BTreeNode<T> *temp = layer.front();
                layer.pop();
                if (temp->left != nullptr) {
                    layer.push(temp->left);
                }
                if (temp->right != nullptr) {
                    layer.push(temp->right);
                }
            }
        }
        return max_width;
    }

    ~BinaryTree() {
        std::shared_ptr<std::stack<BTreeNode<T>*>> s = get_post_order_stack();
        while (!s->empty()) {
            delete s->top();
            s->pop();
        }
    }

private:
    std::shared_ptr<std::stack<BTreeNode<T>*>> get_post_order_stack() {
        std::stack<BTreeNode<T>*> s1;
        std::stack<BTreeNode<T>*> s2;
        s1.push(root);
        while(true) {
            BTreeNode<T> *out = s1.top();
            s1.pop();
            if (out->left) {
                s1.push(out->left);
            }
            if (out->right) {
                s1.push(out->right);
            }
            s2.push(out);
            if (s1.empty()){
                break;
            }
        }
        return std::make_shared<std::stack<BTreeNode<T>*>>(s2);
    }

    BTreeNode<T> *root;
    Comparator comp;
};

template<class T>
struct TreapNode {
    explicit TreapNode (T key, T priority): key(key), priority(priority), left(nullptr), right(nullptr)
    {}
    T key;
    T priority;
    std::shared_ptr<TreapNode<T>> left;
    std::shared_ptr<TreapNode<T>> right;
};

template<class T>
class TreapTree {
public:
    TreapTree(): root(nullptr) {}

    void add(T key, T priority) {
        if (root == nullptr) {
            root = std::make_shared<TreapNode<T>>(TreapNode<T>(key, priority));
            return;
        }
        std::shared_ptr<TreapNode<T>> cur_node = root;
        std::shared_ptr<TreapNode<T>> parent = nullptr;
        while (cur_node->priority >= priority) {
            if (cur_node->key > key) {
                if (cur_node->left == nullptr) {
                    cur_node->left = std::make_shared<TreapNode<T>>(key, priority);
                    return;
                }
                parent = cur_node;
                cur_node = cur_node->left;
            } else {
                if (cur_node->right == nullptr) {
                    cur_node->right = std::make_shared<TreapNode<T>>(key, priority);
                    return;
                }
                parent = cur_node;
                cur_node = cur_node->right;
            }
        }

        std::shared_ptr<TreapNode<T>> tree_left;
        std::shared_ptr<TreapNode<T>> tree_right;

        split(cur_node, key, tree_left, tree_right);

        cur_node = std::make_shared<TreapNode<T>>(key, priority);

        cur_node->left = tree_left;
        cur_node->right = tree_right;

        if (parent == nullptr) {
            root = cur_node;
            return;
        }

        if (parent->key > key) {
            parent->left = cur_node;
        } else {
            parent->right = cur_node;
        }
    }

    int max_tree_width() {
        int max_width = 0;
        std::queue<std::shared_ptr<TreapNode<T>>> layer;
        layer.push(root);

        while (!layer.empty()) {
            if (layer.size() > max_width) {
                max_width = layer.size();
            }

            size_t size = layer.size();
            for (size_t i = 0; i < size; ++i) {
                std::shared_ptr<TreapNode<T>> temp = layer.front();
                layer.pop();
                if (temp->left != nullptr) {
                    layer.push(temp->left);
                }
                if (temp->right != nullptr) {
                    layer.push(temp->right);
                }
            }
        }
        return max_width;
    }
private:

    void split(std::shared_ptr<TreapNode<T>> cur_node,
               T key,
               std::shared_ptr<TreapNode<T>> &left,
               std::shared_ptr<TreapNode<T>> &right) {
        if (cur_node == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (cur_node->key <= key) {
            split(cur_node->right, key, cur_node->right, right);
            left = cur_node;
        } else {
            split(cur_node->left, key, left, cur_node->left );
            right = cur_node;
        }
    }

    std::shared_ptr<TreapNode<T>> merge(std::shared_ptr<TreapNode<T>> left,
               std::shared_ptr<TreapNode<T>> right) {
        if (left == 0 || right == 0) {
            return left == 0 ? right : left;
        }
        if (left->priority > right->priority ) {
            left->right = merge(left->right, right);
            return left;
        } else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    std::shared_ptr<TreapNode<T>> root;
};

int main() {
    int n;
    std::cin >> n;
    TreapTree<int> treap_tree;
    BinaryTree<int> binary_tree;
    for (int i = 0; i < n; ++i) {
        int key, value;
        std::cin >> key >> value;
        treap_tree.add(key, value);
        binary_tree.add(key);
    }
    std::cout << treap_tree.max_tree_width() - binary_tree.max_tree_width();
    return 0;
}
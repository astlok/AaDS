#include <iostream>
#include <memory>
#include <vector>
#include <stack>

template<class T>
struct Node {
    Node(int value): left(nullptr), right(nullptr), value(value), last_node(true) {}
    Node *left;
    Node *right;

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
            root = new Node<T>(value);
            return;
        }
        Node<T> **cur_node = &root;
        while (true) {
            int comp_res = comp((*cur_node)->value, value);
            if (comp_res) {
                if ((*cur_node)->last_node || (*cur_node)->left == nullptr) {
                    (*cur_node)->left = new Node<T>(value);
                    (*cur_node)->last_node = false;
                    break;
                } else {
                    cur_node = &((*cur_node)->left);
                }
            } else {
                if ((*cur_node)->last_node || (*cur_node)->right == nullptr) {
                    (*cur_node)->right = new Node<T>(value);
                    (*cur_node)->last_node = false;
                    break;
                } else {
                    cur_node = &((*cur_node)->right);
                }
            }
        }
    }

    void print_tree() {
        std::shared_ptr<std::stack<Node<T>*>> s = get_post_order_stack();
        while (!s->empty()) {
            std::cout << s->top()->value << " ";
            s->pop();
        }
    }


    ~BinaryTree() {
        std::shared_ptr<std::stack<Node<T>*>> s = get_post_order_stack();
        while (!s->empty()) {
            delete s->top();
            s->pop();
        }
    }

private:
    std::shared_ptr<std::stack<Node<T>*>> get_post_order_stack() {
        std::stack<Node<T>*> s1;
        std::stack<Node<T>*> s2;
        s1.push(root);
        while(true) {
            Node<T> *out = s1.top();
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
        return std::make_shared<std::stack<Node<T>*>>(s2);
    }

    Node<T> *root;
    Comparator comp;
};


int main() {
    int n;
    std::cin >> n;
    BinaryTree<int> tree;
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        tree.add(temp);
    }
    tree.print_tree();
    return 0;
}
#include <iostream>
#include "Queue.cpp"

//void TEST() {
//    D_Array array;
//    int expect_array[] = {0, 1, 2, 3, 4};
//    for (int i = 0; i < 5; ++i) {
//        array.add(i);
//    }
//    for (int i = 0; i < 5; ++i) {
//        assert(array[i] == expect_array[i]);
//    }
//}
void test2() {
    Queue queue;
    queue.push(2);
    assert(queue.pop(2) == 2);
}
void test3() {
    Queue queue;
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    assert(queue.pop(2) == 2);
    queue.push(4);
    assert(queue.pop(3) == 3);
    queue.push(5);
    assert(queue.pop(4) == 4);
}
void test4() {
    Queue queue;
    for (int i = 0; i < 10000; ++i) {
        queue.push(i);
    }
    for (int i = 0; i < 10000; ++i) {
        assert(queue.pop(i) == i);
    }
}
void test5() {
    Queue queue;
    for (int i = 0; i < 10000; ++i) {
        queue.push(i);
    }
    for (int i = 0; i < 5000; ++i) {
        assert(queue.pop(i) == i);
    }
    for (int i = 5000; i < 10000; ++i) {
        queue.push(i);
    }
    for (int i = 5000; i < 10000; ++i) {
        assert(queue.pop(i) == i);
    }
}
void test6() {
    Queue queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    assert(queue.pop(1) == 1);
    queue.push(6);
    queue.push(7);
    assert(queue.pop(2) == 2);
    assert(queue.pop(3) == 3);
    assert(queue.pop(4) == 4);
    assert(queue.pop(5) == 5);
    assert(queue.pop(6) == 6);
    assert(queue.pop(7) == 7);
    queue.push(22);
    assert(queue.pop(22) == 22);
    queue.push(12);
    assert(queue.pop(12) == 12);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    assert(queue.pop(1) == 1);
    queue.push(6);
    queue.push(7);
    assert(queue.pop(2) == 2);
    assert(queue.pop(3) == 3);
    assert(queue.pop(4) == 4);
    assert(queue.pop(5) == 5);
    assert(queue.pop(6) == 6);
    assert(queue.pop(7) == 7);
    for (int i = 0; i < 100; ++i) {
        queue.push(i);
    }
    for (int i = 0; i < 100; ++i) {
        assert(queue.pop(i) == i);
    }
    for (int i = 0; i < 1000; ++i) {
        queue.push(228);
        assert(queue.pop(228) == 228);
    }
}
void test8() {
    Queue queue;
    for (int i = 0; i < 100; ++i) {
        queue.push(i);
    }
    for (int i = 0; i < 100; ++i) {
        assert(queue.pop(i) == i);
    }
    for (int i = 50; i < 100; ++i) {
        queue.push(i);
    }
    for (int i = 50; i < 100; ++i) {
        assert(queue.pop(i) == i);
    }

}
void test7() {
    Queue queue;
    assert(queue.pop(2) == -1);
    queue.push(10);
    assert(queue.pop(10) == 10);
}
void test9() {
    Queue queue;
    for (int i = 0; i < 10; ++i) {
        queue.push(i);
    }
    assert(queue.pop(0) == 0);
    queue.push(228);
    queue.push(322);
    for (int i = 1; i < 10; ++i) {
        assert(queue.pop(i) == i);
    }
    assert(queue.pop(228) == 228);
    assert(queue.pop(322) == 322);
    for (int i = 0; i < 9; ++i) {
        queue.push(i);
    }
    assert(queue.pop(0) == 0);
    for (int i = 9; i < 20; ++i) {
        queue.push(i);
    }
    for (int i = 1; i < 20; ++i) {
        assert(queue.pop(i) == i);
    }
}

void test10() {
    Queue queue;
    queue.push(119);
    assert(queue.pop(119) == 119);
    queue.push(93);
    queue.push(135);
    queue.push(27);
    queue.push(99);
    assert(queue.pop(93) == 93);
    assert(queue.pop(135) == 135);
    assert(queue.pop(27) == 27);
    queue.push(69);
    assert(queue.pop(99) == 99);
    assert(queue.pop(69) == 69);
    queue.push(123);
    queue.push(5);
}
int main() {
    test2();
    test3();
    test4();
    test5();
    test6();
    test8();
    test7();
    test9();
    test10();
//    int n = 0;
//    std::cin >> n;
//    int operate = 0;
//    int elem = 0;
//    Queue queue;
//    bool done = true;
//    for (int i = 0; i < n; ++i){
//        std::cin >> operate >> elem;
//        switch(operate) {
//            case 2:
//                if (queue.pop(elem) != elem) {
//                    std::cout << "NO" << std::endl;
//                    done = false;
//                }
//                break;
//            case 3:
//                queue.push(elem);
//        }
//    }
//    if (done) {
//        std::cout << "YES" << std::endl;
//    }
    return 0;
}


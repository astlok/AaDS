//Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
//[ 1  2  3  4 ]
//[ 5  6  7  8 ]
//[ 9  10 11 12]
//[ 13 14 15 0 ]
//где 0 задает пустую ячейку.
//Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.

#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>

static const int LINE_SIZE = 4;
static const int FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using FieldArray = std::array<int, FIELD_SIZE>;

static const FieldArray EMPTY_FIELD = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0

};

static const FieldArray GOAL_FIELD = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0

};
enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NODIR
};

class FieldState {
public:
    FieldState() : dist_from_begin(0) {
        init(EMPTY_FIELD);
    }

    FieldState(const FieldArray& arr) : dist_from_begin(0) {
        init(arr);
        dir = NODIR;
    }

    FieldState(const FieldState&) = default;
    FieldState& operator= (const FieldState&) = default;
    ~FieldState() = default;

    bool operator< (const FieldState& r) const {
        return arr_state < r.arr_state;
    }

    bool operator== (const FieldState& r) const {
        return arr_state == r.arr_state;
    }

    std::vector<FieldState> GetNextVertices() const {
        std::vector<FieldState> res;

        if (zero_pos >= LINE_SIZE) { // up
            FieldState state(*this);
            state.moveUp();
            state.dir = DOWN;
            res.push_back(state);
        }
        if (zero_pos < FIELD_SIZE - LINE_SIZE) { // down
            FieldState state(*this);
            state.moveDown();
            state.dir = UP;
            res.push_back(state);
        }
        if (zero_pos % LINE_SIZE != 0) { // left
            FieldState state(*this);
            state.moveLeft();
            state.dir = RIGHT;
            res.push_back(state);
        }
        if ((zero_pos + 1) % LINE_SIZE != 0) { // right
            FieldState state(*this);
            state.moveRight();
            state.dir = LEFT;
            res.push_back(state);
        }
        return res;
    }

    bool sol_exists() {
        int k = zero_pos / LINE_SIZE + 1;
        int n = 0;

        for (int i = 0; i < arr_state.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (arr_state[i] == 0 || arr_state[j] == 0) {
                    continue;
                }
                if (arr_state[j] > arr_state[i]) {
                    ++n;
                }
            }
        }
        if ((n + k) % 2 == 0) {
            return true;
        } else {
            return false;
        }
    }

    std::string print() const {
        switch (dir) {
            case UP:
                return "U";
            case DOWN:
                return "D";
            case LEFT:
                return "L";
            case RIGHT:
                return "R";
            case NODIR:
                return "";
        }
    }

    int manhetten_way() {
        int sum = 0;
        int k = 3;
        for (int i = 0; i < FIELD_SIZE; ++i) {
            if (arr_state[i] == 0) {
                sum += (abs((i % LINE_SIZE) - 3) + abs((i / LINE_SIZE) - 3));
            } else {
                sum += (abs((i % LINE_SIZE) - ((arr_state[i] - 1) % LINE_SIZE)) + abs((i / LINE_SIZE)- ((arr_state[i] - 1) / LINE_SIZE)));
            }
        }
        return  k * sum;
    }

    int dist_from_begin;
    int deep;
    direction dir;
private:
    void moveUp() {
        int new_zero_pos = zero_pos - LINE_SIZE;
        std::swap(arr_state[zero_pos], arr_state[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void moveDown() {
        int new_zero_pos = zero_pos + LINE_SIZE;
        std::swap(arr_state[zero_pos], arr_state[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void moveLeft() {
        int new_zero_pos = zero_pos - 1;
        std::swap(arr_state[zero_pos], arr_state[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void moveRight() {
        int new_zero_pos = zero_pos + 1;
        std::swap(arr_state[zero_pos], arr_state[new_zero_pos]);
        zero_pos = new_zero_pos;
    }

    void init(const FieldArray& arr) {
        for (int i = 0; i < arr.size(); ++i) {
            arr_state[i] = arr[i];
            if (arr[i] == 0) {
                zero_pos = i;
            }
        }
    }

    FieldArray arr_state;
    int zero_pos;

};

void AStar(FieldState& start) {
    if (!start.sol_exists()) {
        std::cout << -1 << std::endl;
        return;
    }
    auto comp = [](const FieldState &l, const FieldState &r){ return l.deep <= r.deep; };
    std::set<FieldState, decltype(comp)> q(comp);
    std::map<FieldState, FieldState> used;

    const FieldState goal_state(GOAL_FIELD);
    const FieldState empty_state(EMPTY_FIELD);

    start.dist_from_begin = 0;
    start.deep = start.manhetten_way();
    q.insert(start);
    used.insert(std::make_pair(start, empty_state));
    FieldState cur_state(EMPTY_FIELD);
    while(!q.empty()) {
        cur_state = *q.begin();
        q.erase(q.begin());

        if (cur_state == goal_state) {
            break;
        }

        for (FieldState child : cur_state.GetNextVertices()) {
            if (used.find(child) == used.end()) {
                child.dist_from_begin = cur_state.dist_from_begin + 1;
                child.deep = child.manhetten_way() + cur_state.dist_from_begin + 1;
                q.insert(child);
                used.insert(std::make_pair(child, cur_state));
            }
        }
    }

    std::string result;
        int steps_count = 0;
        while (!(cur_state == empty_state)) {
            result += cur_state.print();
            cur_state = used.find(cur_state)->second;
            steps_count++;
        }
        std::reverse(result.begin(), result.end());
        std::cout << --steps_count << std::endl << result << std::endl;
}

int main() {
    FieldArray arr;
    for (int i = 0; i < FIELD_SIZE; ++i) {
        std::cin >> arr[i];
    }
    FieldState start(arr);
    AStar(start);
    return 0;
}

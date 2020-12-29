#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <map>

static const int LINE_SIZE = 4;
static const int FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using FieldArray = std::array<uint8_t, FIELD_SIZE>;

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

class FieldState {
public:
    FieldState() {
        init(EMPTY_FIELD);
    }

    FieldState(const FieldArray& arr) {
        init(arr);
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
            res.push_back(state);
        }
        if (zero_pos < FIELD_SIZE - LINE_SIZE) { // down
            FieldState state(*this);
            state.moveDown();
            res.push_back(state);
        }
        if (zero_pos % LINE_SIZE != 0) { // left
            FieldState state(*this);
            state.moveLeft();
            res.push_back(state);
        }
        if ((zero_pos + 1) % LINE_SIZE != 0) { // right
            FieldState state(*this);
            state.moveRight();
            res.push_back(state);
        }
        return res;
    }

    void print() const {
        for (int i = 0; i < arr_state.size(); ++i) {
            std::cout << (int)arr_state[i] << " ";
            if ((i + 1) % LINE_SIZE == 0) { // right
                std::cout << std::endl;
            }
        }
    }


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


void bfs(const FieldState& start) {
    std::queue<FieldState> q;
    std::map<FieldState, FieldState> used;

    const FieldState goal_state(GOAL_FIELD);
    const FieldState empty_state(EMPTY_FIELD);

    q.push(start);
    used.insert(std::make_pair(start, empty_state));
    FieldState cur_state(EMPTY_FIELD);
    while(!q.empty()) {
        cur_state = q.front();
        q.pop();
        size_t s = used.size();

        if (cur_state == goal_state) {
            break;
        }

        for (FieldState child : cur_state.GetNextVertices()) {
            if (used.find(child) == used.end()) {
                used.insert(std::make_pair(child, cur_state));
                q.push(child);
            }
        }
    }

    if (cur_state == goal_state) {
        int steps_count = 0;
        while (!(cur_state == empty_state)) {
            cur_state.print();
            std::cout << "-----------" << std::endl;
            cur_state = used.find(cur_state)->second;
            steps_count++;
        }
        std::cout << steps_count << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    std::cout << "used count: " << used.size() << std::endl;
}


int main() {
    FieldState start({
                             5, 1, 3, 4,
                             9, 2, 6, 8,
                             13, 10 ,7, 11,
                             14, 15, 0, 12
                     });
    bfs(start);
    return 0;
}

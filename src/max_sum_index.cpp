#include "max_sum_index.h"

std::vector<int> max_sum_index(std::vector<int> &a, std::vector<int> &b, int n) {
    int max = b[0];
    int k = 0;
    for (int i = 0; i < n; i++) {
       if (b[i] > max) {
          max = b[i];
          k = i;
       }
    }
    int max_sum = max + a[0];
    int l = 0;
    for (int i = 0; i <= k; i++) {
        if (max + a[i] >= max_sum) {
            max_sum = max + a[i];
            l = i;
        }
    }
    return {l, k};
}

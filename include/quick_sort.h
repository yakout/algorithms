//
// Created by Ahmed Yakout on 3/11/17.
//

#ifndef ALGORITHMS_QUICK_SORT_H__
#define ALGORITHMS_QUICK_SORT_H__

#include <istream>
#include <vector>

namespace algo {
    using namespace std;

    class quick_sort {
    private:
        int partitioning(vector<int> &A, int p, int r) {
            int pivot = A[r];
            int i = p - 1;
            for (int j = p; j <= r - 1; ++j) {
                if (A[j] <= pivot) {
                    i++;
                    swap(A[j], A[i]);
                }
            }
            swap(A[i + 1], A[r]);
            return i + 1;
        }
    public:
        quick_sort(){};
        ~quick_sort(){};
        void sort(vector<int> &array, int p, int r) {
            if (p < r) {
                int q = partitioning(array, p, r);
                sort(array, q + 1, r);
                sort(array, p, q - 1);
            }
            return;
        }
    };
}

#endif //ALGORITHMS_QUICK_SORT_H__

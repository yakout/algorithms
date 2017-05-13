//
// Created by Ahmed Yakout on 3/11/17.
//

#ifndef ALGORITHMS_SELECTION_SORT_H__
#define ALGORITHMS_SELECTION_SORT_H__

namespace algo {
    template <typename Comparable>
    static void selection_sort(vector<Comparable> &range) {
        int min_index;
        for (int i = 0; i < range.size(); ++i) {
            min_index = i;

            for (int j = i + 1; j < range.size(); ++j) {
                if (range[j] < range[min_index]) {
                    min_index = j;
                }
            }

            if (min_index != i) {
                swap(range[min_index], range[i]);
            }
        }
    }
}
#endif //ALGORITHMS_SELECTION_SORT_H

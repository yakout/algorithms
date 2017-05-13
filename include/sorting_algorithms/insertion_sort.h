//
// Created by Ahmed Yakout on 3/11/17.
//

#ifndef ALGORITHMS_INSERTION_SORT_H__
#define ALGORITHMS_INSERTION_SORT_H__

namespace algo {
    /**
     * running time is O(n^2)
     * @tparam Comparable
     * @param range
     */
    template <typename Comparable>
    static void insertion_sort(vector<Comparable> &range) {
        int j;
        for (int i = 1; i < range.size(); i++) {
            Comparable current_item = range[i];
            j = i - 1;
            while (j >= 0 && range[j] > current_item) {
                range[j + 1] = range[j];
                j--;
            }
            range[j + 1] = current_item;
        }
    }
}

#endif //ALGORITHMS_INSERTION_SORT_H__

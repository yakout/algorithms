//
// Created by Ahmed Yakout on 3/18/17.
//

#ifndef ALGORITHMS_DECTIONARY_H__
#define ALGORITHMS_DECTIONARY_H__

#include <string>
#include "avl_tree.h"

namespace algo {

    template <class Comparable>
    class dictionary {
    private:
        AVL<std::string> _dictionary;

    public:
        dictionary() {};
        ~dictionary() {};
        void load(std::string path);
        int size();
        bool insert(std::string word);
        bool lookup(std::string word);
        bool remove(std::string word);
    };

    void dictionary::load(std::string path) {

    }

    bool dictionary::insert(std::string word) {
        return false;
    }

    bool dictionary::lookup(std::string word) {
        return false;
    }

    bool dictionary::remove(std::string word) {
        return false;
    }

    int dictionary::size() {
        return 0;
    }
}

#endif //ALGORITHMS_DECTIONARY_H__

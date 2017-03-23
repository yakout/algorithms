//
// Created by Ahmed Yakout on 3/18/17.
//

#ifndef ALGORITHMS_DECTIONARY_H__
#define ALGORITHMS_DECTIONARY_H__

#include <string>
#include "avl_tree.h"
#include "binary_tree_ascii.h"

namespace algo {

    class dictionary {
    private:
        AVL<std::string> _dictionary;
        long long int dict_size;

    public:
        dictionary(): dict_size(0), _dictionary() {};
        ~dictionary() {};
        void load(std::string path);
        long long int size();
        bool insert(std::string word);
        bool lookup(std::string word);
        bool remove(std::string word);
        void print_statistics();
    };



    /**  F U N C T I O N S   D E F I N T I O N S   **/

    void dictionary::load(std::string path) {
        using namespace std;
        ifstream infile(path);
        if (!infile.is_open()) {
            cout << "Failed to open" << endl;
            return;
        }
        cout << "Opened OK" << endl;
        string line;
        while (getline(infile, line)) {
            if (!line.empty()) {
                insert(line);
            }
        }
//        _dictionary.load_file(path);
    }

    bool dictionary::insert(std::string word) {
        dict_size++;
        return _dictionary.insert_key(word);
    }

    bool dictionary::lookup(std::string word) {
        return _dictionary.lookup(word);
    }

    bool dictionary::remove(std::string word) {
        dict_size--;
        return _dictionary.delete_key(word);
    }

    long long int dictionary::size() {
        return dict_size;
    }

    void dictionary::print_statistics() {
//        print_ascii_node(_dictionary.get_tree());
        printf("size of dictionary = %lld\n", dict_size);
        printf("max key value = %s\n", _dictionary.maximum(_dictionary.get_tree())->value.c_str());
        printf("min key value = %s\n", _dictionary.minimum(_dictionary.get_tree())->value.c_str());
        printf("height of tree = %d\n", _dictionary.height());
        printf("root value = %s\n", _dictionary.get_tree()->value.c_str());
    }
}

#endif //ALGORITHMS_DECTIONARY_H__

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
        dictionary(): _dictionary(), dict_size(0) {};
        ~dictionary() {};
        void load(std::string path);
        long long int size();
        bool insert(std::string word);
        int height();
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
        bool return_value = _dictionary.insert_key(word);
        if (return_value) {
            dict_size++;
        }
        return return_value;
    }

    bool dictionary::lookup(std::string word) {
        return _dictionary.lookup(word);
    }

    bool dictionary::remove(std::string word) {
        bool return_value = _dictionary.delete_key(word);
        if (return_value) {
            dict_size--;
        } else {
            cout << "cant find key: " << word << endl;
            cout << lookup(word) << endl;
            return false;
        }
        return return_value;
    }

    long long int dictionary::size() {
        return dict_size;
    }

    int dictionary::height() {
        return _dictionary.height();
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

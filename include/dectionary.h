//
// Created by Ahmed Yakout on 3/18/17.
//

#ifndef ALGORITHMS_DECTIONARY_H__
#define ALGORITHMS_DECTIONARY_H__

#include <string>

namespace algo {

    template <class Comparable>
    class dictionary {
    public:
        dictionary() {};
        ~dictionary() {};

        void load(std::string path);
    };
}

#endif //ALGORITHMS_DECTIONARY_H__

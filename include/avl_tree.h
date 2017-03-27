//
// Created by Ahmed Yakout on 3/17/17.
//

#ifndef ALGORITHMS_AVL_H__
#define ALGORITHMS_AVL_H__

#include <iostream>
#include <stack>
#include <fstream>
#include <iomanip>

namespace algo {

    template<typename T>
    class AVL {
    public:
        AVL(): root(nullptr){};
        ~AVL() {};

        // node struct
        struct Node {
            Node *left, *right;
            T value;
            int height;
            // Any new node will have it's right and left children points to null.
            Node(const T &x) : left(nullptr), right(nullptr), value(x), height(0) {};

            /**
             * Updates the height of the current node.
             */
            void update_height() {
                // The height of null node is -1.
                height = max(left == nullptr ? -1 : left->height,
                             right == nullptr ? -1 : right->height) + 1;
            }
        };

        class key_not_found: public std::exception {
            public:
                virtual const char * what() const throw() {
                            return "key does not exist";
                }
        };


        /**
         * load keys from file with the given path.
         */
         void load_file(std::string path);

        /**
         * finds node with the given key.
         * @param key : the key of the node.
         * @return Node * : returns a pointer to the node that have the given key.
         */
        Node *find_node(const T *key);

        /**
         * Regular BST insertion.
         * @param key : node key.
         * @return bool : true in success, false in failur.
         */
        bool insert_key(T key);

        /**
         * AVL insertion using recursion.
         * @param key
         * @return Node*
         */
        Node *insert_key(Node *node, T key);

        /**
         * delete the node with the given key in avl tree.
         * @param key
         * @return bool : true in success, false in failur.
         */
        bool delete_key(T key);

        /**
         * delete the node with the given key in the given subtree.
         * @param node
         * @param key
         * @return
         */
        Node * delete_key(Node *node, T key);

        /**
         * Search for a node with the given key in the AVL tree and returns true if found
         * or false if not found.
         * @param key
         * @return bool : true if found.
         */
        bool lookup(T key);

        /**
         * Utility function to search for a node with the given key in the given subtree
         * and returns true if found or false if not found.
         * @param key
         * @return bool : true if found.
         */
        bool lookup(Node *node, T key);

        /**
         * returns the successor (the next bigger key) of the given node.
         * @param node
         * @return
         */
        Node* successor(const Node *node);

        /**
         * returns the predecessor (the previous smaller key) of the given node.
         * @param Node*
         * @return Node*
         */
        Node* predecessor(const Node *node);

        

        
        // B A L A N C I N G     M E T H O D S //  

        /**
         * This case is when the node is a left child and it's parent is also left child,
         * and we need to right rotate the grand parent node.
         * 
         *        T1, T2, T3 and T4 are subtrees.
         *
         *           z                                      y 
         *          / \                                   /   \
         *         y   T4      left_left(z)              x      z
         *        / \          - - - - - - - - ->      /  \    /  \ 
         *       x   T3                               T1  T2  T3  T4
         *      / \
         *    T1   T2
         * 
         * We call this a single rotation.
         * @param Node* a subtree, in the example above it will be z.
         * @return Node* the new root of the given subtree.
         */
        Node* left_left(Node *node);

        /**
         * It's the symetric case for the left_left case (a node is a right
         * child and it's parent is also right child).
         * Here we will need to do a left rotation.
         *
         *        T1, T2, T3 and T4 are subtrees.
         *
         *            z                               y
         *          /  \                            /   \ 
         *          T1   y     right_right(z)       z      x
         *             /  \   - - - - - - - ->    / \    / \
         *            T2   x                     T1  T2 T3  T4
         *                / \
         *               T3  T4
         *
         * We call this a single rotation.
         * @param Node* a subtree, in the example above it will be z.
         * @return Node* the new root of the given subtree.
         */
        Node* right_right(Node *node);

        /**
         * This case is when the node is a right child and it's parent is a left child.
         *
         *        T1, T2, T3 and T4 are subtrees.
         *
         *        z                                    x
         *       / \                                 /   \ 
         *      y   T4   left_right(z)             y      z
         *     / \      - - - - - - - - ->        / \    / \
         *   T1   x                             T1  T2  T3  T4
         *       / \                        
         *     T2   T3
         *
         * This is called "double rotation" also "two rotations",
         * rotate left the left-right node ('x' in this example) then rotate
         * right the node it self ('z' in this example).
         *
         * @param Node* a subtree, in the example above it will be z.
         * @return Node* the new root of the given subtree.
         */
        Node* left_right(Node *node);

        /**
         * The symetric case for the left_right case (the node is a left child
         * and it's parent is a right child).
         * 
         *           z                                x
         *          / \                             /  \ 
         *        T1   y   right_left(z)          z      y
         *            / \  - - - - - - - - ->    / \    / \
         *           x   T4                    T1  T2  T3  T4
         *          / \
         *        T2   T3
         *
         * This is called "double rotation" also "two rotations",
         * rotate right the right-left node ('x' in this example) then rotate
         * left the node it self ('z' in this example).
         *
         * @param Node* a subtree, in the example above it will be z.
         * @return Node* the new root of the given subtree.
         */
        Node* right_left(Node *node);

        /**
         * finds node with minimum value in node subtree.
         * @param node
         * @return
         */
        Node* minimum(Node *node);

        /**
         * finds node with maximum value in node subtree.
         * @param node
         * @return
         */
        Node* maximum(Node *node);

        /**
         * return the height of the AVL tree.
         * @return
         */
        inline int height() {
            return root->height;
        }

        /**
         * return the height of the node.
         * @return
         */
        inline int height(Node *node) {
            if (node == nullptr) {
                return -1;
            }
            return node->height;
        }

        /**
         * return the balance of the node.
         */
        inline int get_balance(Node *node) {
            if (node == nullptr) {
                return 0;
            }
            return height(node->left) - height(node->right);
        }

        /**
         * print the tree nodes using in-order traversal.
         */
        void to_string() {
           inorder(root);
//            inorder();
//            preorder(root);
        }

        /**
         * @return Node* The avl root node.
         */
        Node* get_tree() {
            return root;
        }

    private:
        Node *root;
        /**
         * inorder traverse using recursion.
         * @param node
         */
        void inorder(Node *node);
        /**
         * inorder traverse without recursion.
         * @param node
         */
        void inorder();
        /**
         * preorder traverse without recursion.
         * @param node
         */
        void preorder(Node *node);

    };



    /**  F U N C T I O N S   D E F I N T I O N S   **/

    template<typename T>
    bool AVL<T>::insert_key(T key) {
        try {
            root = insert_key(root, key);
        } catch (std::bad_alloc) {
            // We better give up to this exception and let the program terminate ;)
            return false;
        }
        return true;
    }

    template<typename T>
    typename AVL<T>::Node* AVL<T>::insert_key(AVL<T>::Node *node, T key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->value) {
            node->left = insert_key(node->left, key);
        } else {
            node->right = insert_key(node->right, key);
        }

        node->update_height();
        int balance = get_balance(node);

        if (balance == 2) {
            if (get_balance(node->left) >= 0) {
                return left_left(node);
            } else {
                return left_right(node);
            }
        } else if (balance == -2) {
            if (get_balance(node->right) <= 0) {
                return right_right(node);
            } else {
                return right_left(node);
            }
        }
        return node;
    }



    template<typename T>
    bool AVL<T>::delete_key(T key) {
        try {
            root = delete_key(root, key);
        } catch (const key_not_found& e) {
            cout <<  e.what() << endl;
            return false;
        }
        if (root != nullptr) {
            // avl tree is not empty
            root->update_height();
        }
        return true;
    }


    template<typename T>
    typename AVL<T>::Node *AVL<T>::delete_key(Node *node, T key) {
        if (node == nullptr) {
            // key not found
            throw AVL<T>::key_not_found();
        }
        if (key < node->value) {
            node->left = delete_key(node->left, key);
        } else if (key > node->value) {
            node->right = delete_key(node->right, key);
        } else {
            // node is found.
            if (node->left == nullptr && node->right == nullptr) {
                // deleting the node
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                delete node;
                return node->right;
            } else if (node->right == nullptr) {
                delete node;
                return node->left;
            } else {
                Node *successor_node = successor(node);
                if (node->right->left == nullptr) {
                    node->right->left = node->left;
                    node->right = nullptr;
                    delete node;
                    successor_node->update_height();
                    return successor_node;
                }
                node->right->left = successor_node->right;
                successor_node->right = node->right;
                successor_node->left = node->left;
                delete node;
                successor_node->update_height();
                return successor_node;
            }
        }
        node->update_height();
        int balance = get_balance(node);

        if (balance == 2) {
            if (get_balance(node->left) >= 0) {
                return left_left(node);
            } else {
                return left_right(node);
            }
        } else if (balance == -2) {
            // take care from the equal sign
            if (get_balance(node->right) <= 0) {
                return right_right(node);
            } else {
                return right_left(node);
            }
        }
        return node;
    }

    template<typename T>
    bool AVL<T>::lookup(T key) {
        bool temp = lookup(root, key);
        if (temp) cout << "found the key: " << key << endl;
        else cout << "no such key\n";
        return temp;
    }

    template<typename T>
    bool AVL<T>::lookup(AVL<T>::Node *node, T key) {
        if (node == nullptr) {
            // not found
            return false;
        }
        if (key < node->value) {
            return lookup(node->left, key);
        } else if (key > node->value) {
            return lookup(node->right, key);
        } else {
            // found.
            return true;
        }
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::successor(const AVL<T>::Node *node) {
        if (node->right != nullptr) {
            return minimum(node->right);
        }
        stack<Node> s;
        Node *temp = root;
        // put the path to the node in a stack.
        while(temp != nullptr) {
            s.push(*temp);
            if (node->value < temp->value) {
                s.push(*temp->left);
            } else if (node->value > temp->value){
                s.push(*temp->right);
            }
        }
        if (s.size() == 1) {
            // there is no successor for this node; the node is the greatest key.
            return nullptr;
        }
        temp = &s.top();
        s.pop();
        Node *parent = &s.top();
        s.pop();
        while (parent != nullptr && temp == parent->right) {
            temp = parent;
            parent = &s.top();
            s.pop();
        }
        return parent;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::predecessor(const AVL<T>::Node *node) {
        // todo: implement predecessor
        return nullptr;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::left_left(AVL<T>::Node *node) {
//        cout << "left_left node = " << node->value << endl;
        Node *new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        new_root->right->update_height();
        new_root->update_height();
        return new_root;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::right_right(AVL<T>::Node *node) {
//        cout << "right_right node = " << node->value << endl;
        Node *new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        new_root->left->update_height();
        new_root->update_height();
        return new_root;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::left_right(AVL<T>::Node *node) {
//        cout << "left_right node = " << node->value << endl;
        Node *new_root = node->left->right;
        node->left->right = new_root->left;
        new_root->left = node->left;
        node->left = new_root->right;
        new_root->right = node;
        new_root->right->update_height();
        new_root->left->update_height();
        new_root->update_height();
        return new_root;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::right_left(AVL<T>::Node *node) {
//        cout << "right_left node = " << node->value << endl;
        Node *new_root = node->right->left;
        node->right->left = new_root->right;
        new_root->right = node->right;
        node->right = new_root->left;
        new_root->left = node;
        new_root->right->update_height();
        new_root->left->update_height();
        new_root->update_height();
        return new_root;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::minimum(AVL<T>::Node *node) {
        Node *iter = node;
        while (iter->left != nullptr) {
            iter = iter->left;
        }
        return iter;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::maximum(AVL<T>::Node *node) {
        Node *iter = node;
        while (iter->right != nullptr) {
            iter = iter->right;
        }
        return iter;
    }

    template<typename T>
    void AVL<T>::inorder(Node *node) {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << "key = " << node->value << " || height = " << node->height << std::endl;
            inorder(node->right);
        }
        return;
    }

    template<typename T>
    void AVL<T>::preorder(AVL<T>::Node *node) {
        if (node != nullptr) {
            std::cout << "key = " << node->value << " || height = " << node->height << std::endl;
            preorder(node->left);
            preorder(node->right);
        }
    }

    template<typename T>
    void AVL<T>::inorder() {
        stack<Node> s;
        Node *iter = root;
        while(iter != nullptr || !s.empty()) {
            while(iter != nullptr) {
                s.push(*iter);
                iter = iter->left;
            }
            iter = &s.top();
            s.pop();
            cout << iter->value << endl;
            iter = iter->right;
        }
    }

    template<typename T>
    void AVL<T>::load_file(std::string path) {
        std::ifstream infile(path);
        if (!infile.is_open()) {
            cout <<" Failed to open" << endl;
            return;
        }
        cout <<"Opened OK" << endl;
        string line;
        int a;
        while (infile >> a) {
            insert_key(a);
        }
//        while (getline(infile, line)) {
////            cout << line << endl;
//            if (!line.empty())
//            insert_key(line);
//        }
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::find_node(const T *key) {
        Node *temp = root;
        while(temp != nullptr) { ;
            if (key < temp->value) {
                temp = temp->left;
            } else if (key > temp->value){
                temp = temp->right;
            } else {
                return temp;
            }
        }
        // key not found
        return nullptr;
    }

}


#endif //ALGORITHMS_AVL_H__

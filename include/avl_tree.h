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
        struct Node {
            Node *left, *right;
            T value;
            int height;
            Node(const T &x) : left(nullptr), right(nullptr), value(x), height(0) {};

            /**
             * updates the balance factor (height) of the current node.
             */
            void update_height() {
                height = max(left == nullptr ? -1 : left->height,
                             right == nullptr ? -1 : right->height) + 1;
            }
        };


        /**
         * load keys from file.
         */
         void load_file(std::string path);

        /**
         * finds node with some key.
         * @param key
         * @return
         */
        Node *find_node(const T *key);

        /**
         * BST insertion.
         * @param key
         * @return
         */
        bool insert_key(T key);

        /**
         * AVL insertion using recursion.
         * @param key
         * @return
         */
        Node * insert_key(Node *node, T key);

        /**
         * delete the node with the given key in avl tree.
         * @param key
         * @return
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
         * search for a node with the given key in the AVL tree and returns true if found
         * or false if not found.
         * @param key
         * @return
         */
        bool lookup(T key);

        /**
         * utility function to search for a node with the given key in the given subtree
         * and returns true if found or false if not found.
         * @param key
         * @return
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
         * @param node
         * @return
         */
        Node* predecessor(const Node *node);

        // rebalancing methods
        /**
         * i.e single right rotation.
         * @param node
         * @return
         */
        Node* left_left(Node *node);
        /**
         * i.e single left rotation.
         * @param node
         * @return
         */
        Node* right_right(Node *node);
        /**
         * i.e double rotation.
         * rotate left the left-right children then rotate
         * right the node.
         * @param node
         * @return
         */
        Node* left_right(Node *node);
        /**
         * * i.e double rotation.
         * rotate right the right-left children then rotate
         * left the node.
         * @param node
         * @return
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
//            inorder(root);
//            inorder();
//            preorder(root);
        }

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
//        Node *new_node = new Node(key);
//        Node *current_node = root;
//        if (current_node == nullptr) {
//            root = new_node;
//            return new_node;
//        }
//        while(true) {
//            if (key > current_node->value) {
//                if (current_node->right != nullptr) {
//                    current_node = current_node->right;
//                } else {
//                    current_node->right = new_node;
//                    break;
//                }
//            } else {
//                if (current_node->left != nullptr) {
//                    current_node = current_node->left;
//                } else {
//                    current_node->left = new_node;
//                    break;
//                }
//            }
//        }
//        return new_node;

        root = insert_key(root, key);
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

//        // AVL tree is empty
//        if (node == nullptr) {
//            root = new Node(key);
//            return true;
//        }
//        if (key < node->value) {
//            if (node->left == nullptr) {
//                node->left = new Node(key);
//            } else {
//                insert_key(node->left, key);
//            }
//        } else if (key > node->value) {
//            if (node->right == nullptr) {
//                node->right = new Node(key);
//            } else {
//                insert_key(node->right, key);
//            }
//        } else {
//            // duplicates keys are invalid in AVL.
//            return false;
//        }
//
//        node->update_height();
//        int balance = get_balance(node);
//
//        if (balance == 2) {
//
//        }

//        if (get_balance(node->left) == 2) {
//            if (get_balance(node->left->left) > 0) {
//                node->left = left_left(node->left);
//            } else {
//                node->left = left_right(node->left);
//            }
//        } else if (get_balance(node->left) == -2) {
//            if (get_balance(node->left->right) < 0) {
//                node->left = right_right(node->left);
//            } else {
//                node->left = right_left(node->left);
//            }
//        } else if (get_balance(node->right) == 2) {
//            if (get_balance(node->right->left) > 0) {
//                node->right = left_left(node->right);
//            } else {
//                node->right = left_right(node->right);
//            }
//        } else if (get_balance(node->right) == -2) {
//            if (get_balance(node->right->right) < 0) {
//                node->right = right_right(node->right);
//            } else {
//                node->right = right_left(node->right);
//            }
//        }
//        return true;
    }


    template<typename T>
    bool AVL<T>::delete_key(T key) {
        root = delete_key(root, key);
        root->update_height();
        return true;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::delete_key(Node *node, T key) {
        if (node == nullptr) {
            cout << "key not found";
            return nullptr;
        }
        if (key < node->value) {
            node->left = delete_key(node->left, key);
        } else if (key > node->value) {
            node->right = delete_key(node->right, key);
        } else {
            // node is found.
            if (node->left == nullptr && node->right == nullptr) {
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
        return lookup(root, key);
    }

    template<typename T>
    bool AVL<T>::lookup(AVL<T>::Node *node, T key) {
        if (node == nullptr) {
            // not found
            return false;
        }
        if (key < node->value) {
            return lookup(node->left, key);
        } else if (key < node->value) {
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

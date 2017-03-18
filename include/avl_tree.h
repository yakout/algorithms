//
// Created by Ahmed Yakout on 3/17/17.
//

#ifndef ALGORITHMS_AVL_H__
#define ALGORITHMS_AVL_H__

#include <iostream>
#include <stack>
#include <fstream>

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
            Node(const T &x) : left(nullptr), right(nullptr), value(x), height(0) {}

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
         *
         * @param key
         * @return
         */
        bool delete_key(T key);
        /**
         *
         * @param key
         * @return
         */
        bool search(T key);
        /**
         *
         * @param node
         * @return
         */
        Node* successor(const Node *node);
        /**
         *
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
            pre_order(root);
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
        void pre_order(Node *node);
    };


    /**  C O D E    I M P L E M E N T A T I O N     **/

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
            if (get_balance(node->left) > 0) {
                return left_left(node);
            } else {
                return left_right(node);
            }
        } else if (balance == -2) {
            if (get_balance(node->right) < 0) {
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
        Node *current_node = root;
        while(current_node != nullptr) {
            if (current_node->value == key) {
                if (current_node->right == nullptr
                    && current_node->left == nullptr) {
                    delete current_node;
                }
                if (current_node->right == nullptr) {
                    Node *temp = current_node->left;
                    current_node->left = current_node->left->left;
                    delete temp;
                } else {
                    //todo
                }
            }

        }
        // key not found
        return false;
    }

    template<typename T>
    bool AVL<T>::search(T key) {
        return false;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::successor(const AVL<T>::Node *node) {
        if (node->right != nullptr) {
            Node *temp = node->right;
            //todo use minimum
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            return temp;
        }
        return nullptr;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::predecessor(const AVL<T>::Node *node) {
        return nullptr;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::left_left(AVL<T>::Node *node) {
        cout << "left_left node = " << node->value << endl;
        Node *new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        new_root->right->update_height();
        new_root->update_height();
        return new_root;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::right_right(AVL<T>::Node *node) {
        cout << "right_right node = " << node->value << endl;
        Node *new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        new_root->left->update_height();
        new_root->update_height();
        return new_root;
    }

    template<typename T>
    typename AVL<T>::Node *AVL<T>::left_right(AVL<T>::Node *node) {
        cout << "left_right node = " << node->value << endl;
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
        cout << "right_left node = " << node->value << endl;
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
    void AVL<T>::pre_order(AVL<T>::Node *node) {
        if (node != nullptr) {
            std::cout << "key = " << node->value << " || height = " << node->height << std::endl;
            pre_order(node->left);
            pre_order(node->right);
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
        } else {
            cout <<"Opened OK" << endl;
        }
        string line;
        int a;
        while (infile >> a) {
            insert_key(a);
        }
//        while (getline(infile, line)) {
//            cout << line << endl;
//            insert_key(line);
//        }
    }
}


#endif //ALGORITHMS_AVL_H__

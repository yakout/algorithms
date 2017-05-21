//
// Created by Ahmed Yakout on 3/21/17.
//

#ifndef ALGORITHMS_BINARY_TREE_ASCII_H_
#define ALGORITHMS_BINARY_TREE_ASCII_H_


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "data_structures/avl_tree.h"
#include <stdio.h>



//                  ********** source  ************
//
//             http://stackoverflow.com/a/801794/5299155
//


using namespace algo;
#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between left and right nodes
int gap = 7;

//used for printing next node in the same level,
//this is the x coordinate of the next char printed
int print_next;

AVL<int>::Node* make_empty(AVL<int>::Node*t) {
    if (t != nullptr) {
        make_empty(t->left);
        make_empty(t->right);
        free(t);
    }

    return nullptr;
}

//printing AVL<int>::Nodein ascii

typedef struct asciinode_struct asciinode;

struct asciinode_struct {
    asciinode * left, * right;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
};


int MIN (int X, int Y) {
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y) {
    return ((X) > (Y)) ? (X) : (Y);
}

asciinode * build_ascii_node_recursive(AVL<int>::Node*t) {
    asciinode * node;

    if (t == nullptr) return nullptr;

    node = (asciinode *) malloc(sizeof(asciinode));
    node->left = build_ascii_node_recursive(t->left);
    node->right = build_ascii_node_recursive(t->right);

    if (node->left != nullptr) {
        node->left->parent_dir = -1;
    }

    if (node->right != nullptr) {
        node->right->parent_dir = 1;
    }

    sprintf(node->label, "%d(%d)", t->value, t->height);
    node->lablen = strlen(node->label);

    return node;
}


//Copy the AVL<int>::Node into the ascii node structre
asciinode * build_ascii_node(AVL<int>::Node*t) {
    asciinode *node;
    if (t == nullptr) return nullptr;
    node = build_ascii_node_recursive(t);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given AVL::Node
void free_ascii_node(asciinode *node) {
    if (node == nullptr) return;
    free_ascii_node(node->left);
    free_ascii_node(node->right);
    free(node);
}

//The following function fills in the lprofile array for the given AVL::Node.
//It assumes that the center of the label of the root of this AVL::Node
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this AVL::Node.
void compute_lprofile(asciinode *node, int x, int y) {
    int i, isleft;
    if (node == nullptr) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
    if (node->left != nullptr)
    {
        for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
        {
            lprofile[y+i] = MIN(lprofile[y+i], x-i);
        }
    }
    compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
    compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y) {
    int i, notleft;
    if (node == nullptr) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
    if (node->right != nullptr) {
        for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) {
            rprofile[y+i] = MAX(rprofile[y+i], x+i);
        }
    }
    compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
    compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

//This function fills in the edge_length and
//height fields of the specified AVL::Node
void compute_edge_lengths(asciinode *node) {
    int h, hmin, i, delta;
    if (node == nullptr) return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == nullptr && node->left == nullptr) {
        node->edge_length = 0;
    } else {
        if (node->left != nullptr) {
            for (i=0; i<node->left->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        } else {
            hmin = 0;
        }
        if (node->right != nullptr) {
            for (i=0; i<node->right->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        } else {
            hmin = 0;
        }
        delta = 4;
        for (i=0; i<hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->left != nullptr && node->left->height == 1) ||
             (node->right != nullptr && node->right->height == 1))&&delta>4) {
            delta--;
        }

        node->edge_length = ((delta+1)/2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->left != nullptr) {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != nullptr) {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//This function prints the given level of the given AVL::Node, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level) {
    int i, isleft;
    if (node == nullptr) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    } else if (node->edge_length >= level) {
        if (node->left != nullptr) {
            for (i=0; i<(x-print_next-(level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != nullptr) {
            for (i=0; i<(x-print_next+(level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
        print_level(node->left,
                    x-node->edge_length-1,
                    level-node->edge_length-1);
        print_level(node->right,
                    x+node->edge_length+1,
                    level-node->edge_length-1);
    }
}

//prints ascii AVL<int>::Nodefor given AVL<int>::Nodestructure
void print_ascii_node(AVL<int>::Node*t) {
    cout << endl;
    asciinode *proot;
    int xmin, i;
    if (t == nullptr) return;
    proot = build_ascii_node(t);
    compute_edge_lengths(proot);
    for (i=0; i<proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(This node is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    cout << endl;
    free_ascii_node(proot);
}



#endif // ALGORITHMS_BINARY_TREE_ASCII_H__

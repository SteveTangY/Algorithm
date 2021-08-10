/*
    This is AVL tree pratice, create in 2019.10.27
*/
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <unistd.h>
#include <iostream>
#include <vector>

template <typename T>
class AVL
{
public:
    AVL() : size(0) {}
    AVL(std::vector<T> initializer_array);
    ~AVL() {}
    bool insert(const T& data);
    bool del_node(const T& data);
    T& find(const T& data) const;
private:
    struct avl_tree {
        T data;
        avl_tree* parent = nullptr;
        avl_tree* left_child = nullptr;
        avl_tree* right_child = nullptr;
    };
    int size;
};

#endif  /*  */
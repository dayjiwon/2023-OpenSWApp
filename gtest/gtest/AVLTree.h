#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

enum UNBALANCE_CASE {
    BALANCE = 0,
    LEFT_LEFT = 1,
    RIGHT_RIGHT = 2,
    LEFT_RIGHT = 3,
    RIGHT_LEFT = 4
};

struct Node {
public:
    Node(int key);
    ~Node();

    int get_key();
    int get_height();
    Node* get_left_child();
    Node* get_right_child();

    void set_key(int key);
    void set_height(int height);
    void set_left_child(Node* left_child);
    void set_right_child(Node* right_child);

private:
    int key_;
    int height_;
    Node* left_child_;
    Node* right_child_;
};

class AVLTree {
public:
    AVLTree();
    int get_size();
    Node* get_root();

    void IncreaseSize();
    void DecreaseSize();
    void set_root(Node* root);

    //void Empty();
    //void Size();
    void Minimum(int x);
    void Maximum(int x);
    void Find(int x);
    void Insert(int x);
    void Rank(int x);
    void Erase(int x);

    //�׽�Ʈ�� ���� ����. Ʈ���� ��������� true, �ƴϸ� false�� ��ȯ�Ѵ�.
    bool Empty() { return size_ == 0; }
    int Size() { return size_; }

private:
    Node* GetNode(int key);
    int GetDepth(Node* node);
    int GetHeight(Node* node);
    int IsUnbalance(Node* node);
    int CalculateBalanceFactor(Node* node);
    int CalculateHeight(Node* node);
    int GetRank(Node* node, int x);

    Node* Insert(Node* node, int key);
    Node* DeleteNode(Node* node, int key);
    Node* MinValueNode(Node* node);
    Node* Restruct(Node* node);
    Node* RightRotate(Node* node);
    Node* LeftRotate(Node* node);

    Node* root_;
    int size_;
};

#endif // AVL_TREE_H
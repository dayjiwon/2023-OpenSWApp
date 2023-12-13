#include "pch.h"
#include "../gtest/AVLTree.cpp"

// Node ������ �׽�Ʈ
TEST(NodeTest, Constructor) {
    Node node(10);

    EXPECT_EQ(node.get_key(), 10);
    EXPECT_EQ(node.get_height(), 0);
    EXPECT_EQ(node.get_sub_size(), 1);
    EXPECT_EQ(node.get_left_child(), nullptr);
    EXPECT_EQ(node.get_right_child(), nullptr);
}


// AVLTree ������ �׽�Ʈ
TEST(AVLTreeTest, Constructor) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.Size(), 0);
    EXPECT_EQ(avlTree.get_root(), nullptr);
}


// Empty �׽�Ʈ
TEST(AVLTreeTest, Empty) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.Empty(), true);

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Empty(), false);

    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Empty(), true);
}


// Size �׽�Ʈ
TEST(AVLTreeTest, Size) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.Size(), 0);

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 1);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);

    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Size(), 1);

    avlTree.Erase(20);
    EXPECT_EQ(avlTree.Size(), 0);
}
 

// AVLTree�� ��� �������� ���� �׽�Ʈ
TEST(AVLTreeTest, Insert_ascending) {
    AVLTree avlTree;

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);

    avlTree.Insert(30);
    EXPECT_EQ(avlTree.Size(), 3);


    EXPECT_EQ(avlTree.get_root()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);
}


// AVLTree�� ��� �������� ���� �׽�Ʈ
TEST(AVLTreeTest, Insert_descending) {
    AVLTree avlTree;

    avlTree.Insert(30);
    EXPECT_EQ(avlTree.Size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 30);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 20);

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 3);


    EXPECT_EQ(avlTree.get_root()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);
}


// �������� ����2
TEST(AVLTreeTest, Insert_ascending2) {
    AVLTree avlTree;

    for (int i = 1; i <= 5; ++i) {
        avlTree.Insert(i);
    }

    EXPECT_EQ(avlTree.Size(), 5);

    EXPECT_EQ(avlTree.get_root()->get_key(), 2);

    Node* leftChild = avlTree.get_root()->get_left_child();
    EXPECT_NE(leftChild, nullptr);
    EXPECT_EQ(leftChild->get_key(), 1);


    Node* rightChild = avlTree.get_root()->get_right_child();
    EXPECT_NE(rightChild, nullptr);
    EXPECT_EQ(rightChild->get_key(), 4);


    EXPECT_EQ(rightChild->get_left_child()->get_key(), 3);
    EXPECT_EQ(rightChild->get_right_child()->get_key(), 5);
}


// �������� ����2
TEST(AVLTreeTest, Insert_descending2) {
    AVLTree avlTree;

    for (int i = 5; i >= 1; i--) {
        avlTree.Insert(i);
    }

    EXPECT_EQ(avlTree.Size(), 5);

    EXPECT_EQ(avlTree.get_root()->get_key(), 4);

    Node* leftChild = avlTree.get_root()->get_left_child();
    EXPECT_NE(leftChild, nullptr);
    EXPECT_EQ(leftChild->get_key(), 2);


    Node* rightChild = avlTree.get_root()->get_right_child();
    EXPECT_NE(rightChild, nullptr);
    EXPECT_EQ(rightChild->get_key(), 5);


    EXPECT_EQ(leftChild->get_left_child()->get_key(), 1);
    EXPECT_EQ(leftChild->get_right_child()->get_key(), 3);
}


// Find �׽�Ʈ. Restruct�� ���⼭ Ȯ�� ����
TEST(AVLTreeTest, Find) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);

    EXPECT_EQ(avlTree.Find(5), 2);
    EXPECT_EQ(avlTree.Find(7), 1);
    EXPECT_EQ(avlTree.Find(8), 0);
    EXPECT_EQ(avlTree.Find(9), 3);
    EXPECT_EQ(avlTree.Find(45), 2);
    EXPECT_EQ(avlTree.Find(58), 3);
    EXPECT_EQ(avlTree.Find(63), 1);
    EXPECT_EQ(avlTree.Find(77), 2);
    EXPECT_EQ(avlTree.Find(89), 3);

    EXPECT_EQ(avlTree.Find(15), -1);  // ��� 15�� �������� �����Ƿ� -1 ��ȯ
}


// Restruct �׽�Ʈ
TEST(AVLTreeTest, restruct) {
    // Single Rotation, RR Rotation �׽�Ʈ
    AVLTree avlTree;
    avlTree.Insert(20);
    avlTree.Insert(25);
    avlTree.Insert(30);

    EXPECT_EQ(avlTree.Find(25), 0);
    EXPECT_EQ(avlTree.Find(20), 1);
    EXPECT_EQ(avlTree.Find(30), 1);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);


    // Single Rotation, LL Rotation �׽�Ʈ
    AVLTree avlTree2;
    avlTree2.Insert(30);
    avlTree2.Insert(25);
    avlTree2.Insert(20);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);


    // Double Rotation, LR Rotation �׽�Ʈ
    AVLTree avlTree3;
    avlTree3.Insert(30);
    avlTree3.Insert(20);
    avlTree3.Insert(25);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);


    // Double Rotation, RL Rotation �׽�Ʈ
    avlTree2.Insert(20);
    avlTree2.Insert(30);
    avlTree2.Insert(25);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);
}


// Minimum �׽�Ʈ
TEST(AVLTreeTest, Minimum) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);

    KeyDepthPair result = avlTree.Minimum(63);
    EXPECT_EQ(result.key, 9);
    EXPECT_EQ(result.depth, 3);

    result = avlTree.Minimum(8);
    EXPECT_EQ(result.key, 5);
    EXPECT_EQ(result.depth, 2);
}


// Maximum �׽�Ʈ 
TEST(AVLTreeTest, Maximum) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);


    KeyDepthPair result = avlTree.Maximum(63);
    EXPECT_EQ(result.key, 89);
    EXPECT_EQ(result.depth, 3);

    result = avlTree.Maximum(45);
    EXPECT_EQ(result.key, 58);
    EXPECT_EQ(result.depth, 3);
}


// Rank �׽�Ʈ
TEST(AVLTreeTest, Rank) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);


    DepthRankPair result = avlTree.Rank(8);
    EXPECT_EQ(result.depth, 0);
    EXPECT_EQ(result.rank, 3);


    result = avlTree.Rank(45);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 5);


    result = avlTree.Rank(9);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 4);


    result = avlTree.Rank(77);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 8);


    result = avlTree.Rank(58);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 6);


    result = avlTree.Rank(89);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 9);


    result = avlTree.Rank(101);
    EXPECT_EQ(result.depth, 0);
    EXPECT_EQ(result.rank, 0);
}


// Rank �׽�Ʈ2
TEST(AVLTreeTest, Rank2) {
    AVLTree avlTree;
    avlTree.Insert(8);
    avlTree.Insert(3);
    avlTree.Insert(11);
    avlTree.Insert(2);
    avlTree.Insert(6);
    avlTree.Insert(9);
    avlTree.Insert(13);
    avlTree.Insert(1);
    avlTree.Insert(5);
    avlTree.Insert(7);
    avlTree.Insert(10);
    avlTree.Insert(12);
    avlTree.Insert(4);


    DepthRankPair result = avlTree.Rank(1);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 1);

    result = avlTree.Rank(2);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 2);

    result = avlTree.Rank(3);
    EXPECT_EQ(result.depth, 1);
    EXPECT_EQ(result.rank, 3);

    result = avlTree.Rank(4);
    EXPECT_EQ(result.depth, 4);
    EXPECT_EQ(result.rank, 4);

    result = avlTree.Rank(5);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 5);

    result = avlTree.Rank(6);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 6);

    result = avlTree.Rank(7);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 7);

    result = avlTree.Rank(8);
    EXPECT_EQ(result.depth, 0);
    EXPECT_EQ(result.rank, 8);

    result = avlTree.Rank(9);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 9);

    result = avlTree.Rank(10);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 10);

    result = avlTree.Rank(11);
    EXPECT_EQ(result.depth, 1);
    EXPECT_EQ(result.rank, 11);

    result = avlTree.Rank(12);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 12);

    result = avlTree.Rank(13);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 13);

    EXPECT_EQ(avlTree.Size(), 13);
}


// Erase �׽�Ʈ
TEST(AVLTreeTest, SimpleErase) {
    AVLTree avlTree;

    avlTree.Insert(10);
    avlTree.Insert(5);
    avlTree.Insert(20);

    EXPECT_EQ(avlTree.Size(), 3);

    avlTree.Erase(10);

    EXPECT_EQ(avlTree.Size(), 2);

    EXPECT_EQ(avlTree.Find(10), -1);

    EXPECT_EQ(avlTree.Find(5), 1);
    EXPECT_EQ(avlTree.Find(20), 0);
}


// Erase �׽�Ʈ3
TEST(AVLTreeTest, Erase2) {
    AVLTree avlTree;
    avlTree.Insert(10);
    avlTree.Insert(20);
    avlTree.Insert(5);
    avlTree.Insert(15);
    avlTree.Insert(25);
    avlTree.Insert(3);
    avlTree.Insert(7);
    avlTree.Insert(13);
    avlTree.Insert(17);
    avlTree.Insert(1);

    EXPECT_EQ(avlTree.Size(), 10);

    avlTree.Erase(25); // �ڽ� ���� ��� ���� �� Restruct

    EXPECT_EQ(avlTree.Find(15), 1);
    EXPECT_EQ(avlTree.Find(13), 2);
    EXPECT_EQ(avlTree.Find(20), 2);
    EXPECT_EQ(avlTree.Find(17), 3);

    avlTree.Erase(17); // �ڽ� ���� ��� ���� �� Restruct X

    EXPECT_EQ(avlTree.Find(15), 1);
    EXPECT_EQ(avlTree.Find(13), 2);
    EXPECT_EQ(avlTree.Find(20), 2);

    avlTree.Erase(15); // �ڽ� �� ���� ��� �����ڸ� ���� ����

    EXPECT_EQ(avlTree.Find(13), 2);
    EXPECT_EQ(avlTree.Find(20), 1);

    avlTree.Erase(3); // �ڽ� �ϳ��� ��� ����

    EXPECT_EQ(avlTree.Size(), 6);

    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    Node* leftChild = avlTree.get_root()->get_left_child();
    Node* rightChild = avlTree.get_root()->get_right_child();

    EXPECT_EQ(leftChild->get_key(), 5);
    EXPECT_EQ(leftChild->get_left_child()->get_key(), 1);
    EXPECT_EQ(leftChild->get_right_child()->get_key(), 7);
    
    EXPECT_EQ(rightChild->get_key(), 20);
    EXPECT_EQ(rightChild->get_left_child()->get_key(), 13);

    KeyDepthPair minresult = avlTree.Minimum(10);
    EXPECT_EQ(minresult.key, 1);
    EXPECT_EQ(minresult.depth, 2);

    KeyDepthPair maxresult = avlTree.Maximum(5);
    EXPECT_EQ(maxresult.key, 7);
    EXPECT_EQ(maxresult.depth, 2);

    DepthRankPair result = avlTree.Rank(13);
    EXPECT_EQ(result.rank, 5);
    EXPECT_EQ(result.depth, 2);
}
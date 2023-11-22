#include "pch.h"
#include "../gtest/AVLTree.cpp"

// Node Ŭ������ ������ �׽�Ʈ
TEST(NodeTest, Constructor) {
    Node node(10);

    EXPECT_EQ(node.get_key(), 10);
    EXPECT_EQ(node.get_height(), 1);
    EXPECT_EQ(node.get_left_child(), nullptr);
    EXPECT_EQ(node.get_right_child(), nullptr);
}

// AVLTree Ŭ������ ������ �׽�Ʈ
TEST(AVLTreeTest, Constructor) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.get_size(), 0);
    EXPECT_EQ(avlTree.get_root(), nullptr);
}

// AVLTree�� ��� ���� �׽�Ʈ
TEST(AVLTreeTest, Insert) {
    AVLTree avlTree;

    // ù ��° ����
    avlTree.Insert(10);
    EXPECT_EQ(avlTree.get_size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    // �� ��° ����
    avlTree.Insert(20);
    EXPECT_EQ(avlTree.get_size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);

    // �� ��° ����
    avlTree.Insert(30);
    EXPECT_EQ(avlTree.get_size(), 3);
    // �� �������� AVL Ʈ���� ������ �������ؾ� ��
    // ����Ǵ� ����: 20�� ��Ʈ, 10�� 30�� �ڽ�
    EXPECT_EQ(avlTree.get_root()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);
}

// AVLTree�� Empty �޼ҵ� �׽�Ʈ
TEST(AVLTreeTest, Empty) {
    AVLTree avlTree;

    // Ʈ���� ����ִ� ���
    EXPECT_EQ(avlTree.Empty(), true);

    // Ʈ���� ��� ����
    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Empty(), false);

    // Ʈ������ ��� ����
    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Empty(), true);
}

// AVLTree�� Size �޼ҵ� �׽�Ʈ
TEST(AVLTreeTest, Size) {
    AVLTree avlTree;

    // �ʱ� Ʈ�� ũ�� Ȯ��
    EXPECT_EQ(avlTree.Size(), 0);

    // Ʈ���� ��� ���� �� ũ�� Ȯ��
    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 1);

    // �� �ٸ� ��� ���� �� ũ�� Ȯ��

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);

    // ��� ���� �� ũ�� Ȯ��
    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Size(), 1);

    // ������ ��� ���� �� ũ�� Ȯ��
    avlTree.Erase(20);
    EXPECT_EQ(avlTree.Size(), 0);
}
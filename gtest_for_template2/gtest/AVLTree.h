/*
The MIT License

Copyright (c) <2023> <Minsub Kim, Jiwon Park, Jeonghui Han>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
using namespace std;

//balance�ϴٸ� 0(=false), unbalance�ϴٸ� 1~4(=true)
enum UNBALANCE_CASE {
    BALANCE = 0,
    LEFT_LEFT = 1,
    RIGHT_RIGHT = 2,
    LEFT_RIGHT = 3,
    RIGHT_LEFT = 4
};



template <typename T>
struct Node {
public:
    //�����ڿ� �Ҹ���
    Node(T key) : key_(key), height_(0), sub_size_(1) { left_child_ = right_child_ = NULL; }
    ~Node() {}

    //������
    T get_key() { return key_; }
    int get_height() { return height_; }
    int get_sub_size() { return sub_size_; }
    Node* get_left_child() { return left_child_; }
    Node* get_right_child() { return right_child_; }

    //������
    void set_key(T key) { key_ = key; }
    void set_height(int height) { height_ = height; }
    void set_left_child(Node* left_child) { left_child_ = left_child; }
    void set_right_child(Node* right_child) { right_child_ = right_child; }
    void set_sub_size(int sub_size) { sub_size_ = sub_size; }

private:
    T key_;
    int height_; //insert/erase�� O(log n)�� �����ϱ� ���� �߰��� ��� ����
    int sub_size_; //rank�� O(log n)�� �����ϱ� ���� �߰��� ��� ����
    Node* left_child_;
    Node* right_child_;
};

template <typename T>
class Set{
public:
    virtual ~Set() {}

    virtual bool Empty() = 0;
    virtual int Size() = 0;
    virtual void Minimum(T x) = 0;
    virtual void Maximum(T x) = 0;
    virtual int Find(T x) = 0;
    virtual void Insert(T x) = 0;
    virtual void Rank(T x) = 0;
    virtual void Erase(T x) = 0;
};

template <typename T>
class AVLTree : public Set<T>{
public:
    AVLTree() : root_(NULL) {}

    Node<T>* get_root() { return root_; }

    void set_root(Node<T>* root) { root_ = root; }

    bool Empty() override {
        return GetSize(root_) == 0;
    }

    int Size() override {
        return GetSize(root_);
    }
    void Minimum(T x) override;
    void Maximum(T x) override;
    int Find(T x) override;
    void Insert(T x) override;

    //�䱸 ����(advance)
    void Rank(T x) override;
    void Erase(T x) override;

private:
    //��� ���� ��� �Լ�
    Node<T>* GetNode(T key);
    int GetDepth(Node<T>* node);
    int GetHeight(Node<T>* node) { return (node == NULL) ? -1 : node->get_height(); }
    int GetSize(Node<T>* node) { return (node == NULL) ? 0 : node->get_sub_size(); }
    int GetRank(Node<T>* node, T x);
    int IsUnbalance(Node<T>* node);
    int CalculateBalanceFactor(Node<T>* node);
    int CalculateHeight(Node<T>* node);
    int CalculateSubSize(Node<T>* node);

    //��� ������ ���� �߰����� �Լ�
    Node<T>* Insert(Node<T>* node, T key);
    Node<T>* DeleteNode(Node<T>* node, T key);
    Node<T>* MinValueNode(Node<T>* node);
    Node<T>* Restruct(Node<T>* node);
    Node<T>* RightRotate(Node<T>* node);
    Node<T>* LeftRotate(Node<T>* node);

private:
    Node<T>* root_;
};


//��� x�� depth�� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
template <typename T>
int AVLTree<T>::Find(T x) {
    Node<T>* find_node = GetNode(x); // key == x�� ��� ã��

    // find_node�� NULL�̶�� ��尡 ���ٴ� ���̹Ƿ� -1�� ��ȯ�ϰ�, 
    // �ƴ϶�� ����� ���̸� ��ȯ�Ѵ�.
    if (find_node == NULL) {
        return -1; // ��尡 ���� ��� -1 ��ȯ
    }
    else {
        return GetDepth(find_node); // ��尡 �ִ� ��� ���� ��ȯ
    }
}


//��� x�� ��Ʈ�� �κ�Ʈ������ �ִ� key�� ���� ����� key�� depth�� �������� �����Ͽ� ����Ѵ�.
template <typename T>
void AVLTree<T>::Maximum(T x) {
    Node<T>* maximum_node = GetNode(x); //key == x�� ��� ã�� -> sub root

    //�ִ� key�� sub root�� ���� ���ϴܿ� ��ġ�� ������ ����̹Ƿ� loop�� �ش� �������� ��������.
    while (maximum_node->get_right_child() != NULL) { //������ �ڽ��� NULL�̶�� �ִ�� ������ ���̹Ƿ� �ݺ��� ����
        maximum_node = maximum_node->get_right_child();
    }
    cout << maximum_node->get_key() << " " << GetDepth(maximum_node) << endl;
    
    return;
}

//��� x�� ��Ʈ�� �κ�Ʈ������ �ּ� key�� ���� ����� key�� depth�� �������� �����Ͽ� ����Ѵ�.
template <typename T>
void AVLTree<T>::Minimum(T x) {
    Node<T>* minimum_node = GetNode(x);

    //�ּ� key�� sub root�� ���� ���ϴܿ� ��ġ�� ���� ����̹Ƿ� loop�� �ش� �������� ��������.
    while (minimum_node->get_left_child() != NULL) { //���� �ڽ��� NULL�̶�� �ִ�� ������ ���̹Ƿ� �ݺ��� ����
        minimum_node = minimum_node->get_left_child();
    }
    cout << minimum_node->get_key() << " " << GetDepth(minimum_node) << endl;

    return;
}

//���ο� ��� x�� �����ϰ�, ��� x�� depth�� ����Ѵ�.
template <typename T>
void AVLTree<T>::Insert(T x) {
    //��� ����. �������� ������ private �Լ����� �����Ѵ�.
    set_root(Insert(root_, x));

    //������ ����� depth�� ����Ѵ�.
    Node<T>* new_node = GetNode(x);
    cout << GetDepth(new_node) << "\n";

    return;
}


//��� x�� depth�� rank�� �������� �����Ͽ� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
template <typename T>
void AVLTree<T>::Rank(T x) {
    Node<T>* rank_node = GetNode(x); // key == x�� ��� ã��

    // ��� x�� ���ٸ� 0�� ����ϰ� �����Ѵ�.
    if (rank_node == NULL) {
        cout << "0\n";
        return;
    }
    // ��� x�� �����Ѵٸ� depth�� rank�� ����Ѵ�.
    else {
        int depth = GetDepth(rank_node);
        int rank = GetRank(get_root(), rank_node->get_key());
        cout << depth << " " << rank << "\n";
        return;
    }
}

//��� x�� depth�� ����ϰ� �ش� ��带 �����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
template <typename T>
void AVLTree<T>::Erase(T x) {
    Node<T>* node_to_delete = GetNode(x); // ������ ��� ã��

    //���� ��尡 ������ 0�� ����ϰ� �����Ѵ�.
    if (node_to_delete == NULL) {
        cout << "0\n";
        return;
    }

    //������ ����� ���� ���
    int depth = GetDepth(node_to_delete);
    cout << depth << "\n";

    //��� ����. �������� ������ private �Լ����� �����Ѵ�.
    root_ = DeleteNode(root_, x);

    return;
}

//�־��� key�� ��ġ�ϴ� ��带 ã�� ����� �����͸� ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::GetNode(T key) {
    Node<T>* current_node = get_root(); //root���� ����

    while (true) {
        if (current_node == NULL) return NULL; //ã�� ����
        else if (current_node->get_key() == key) return current_node; //ã�� ����

        //AVL tree�� ������ ����Ͽ�, ���� Ȥ�� �Ʒ������� �������� Ž���Ѵ�.
        current_node = (current_node->get_key() < key) ?
            current_node->get_right_child() : current_node->get_left_child();
    }

    return current_node;
}


//�־��� ��忡 ���� ����(depth)�� ����Ͽ� ��ȯ�Ѵ�.
template <typename T>
int AVLTree<T>::GetDepth(Node<T>* current_node) {
    if (current_node == get_root()) return 0; //root�� ���̴� 0���� ����

    //root���� �����Ͽ� Ư�� ��带 ã�� ������ depth�� 1������Ű�� ��������.
    int depth = 0;
    T key = current_node->get_key();
    Node<T>* tempNode = root_;
    while (true) {
        if (current_node == tempNode) return depth; //Ư�� ��带 ã�Ҵٸ� ����

        //�̶� AVL tree�� ������ ����Ͽ�, ���� Ȥ�� �Ʒ������� ��������.
        tempNode = (tempNode->get_key() < key) ?
            tempNode->get_right_child() : tempNode->get_left_child();

        depth++;
    }
}


//�־��� ��忡 ���� ����(height)�� ����Ͽ� ��ȯ�Ѵ�.
//height�� ����: �� �ڽ� ��� �� �� ū height�� ������ �ڽ� ����� height + 1
template <typename T>
int AVLTree<T>::CalculateHeight(Node<T>* node) {
    //�������� �ʴ� ����� ���̴� -1, ���� ����� ���̴� 0���� �����Ѵ�.
    if (node == NULL) return -1;

    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    return max(left_child_height, right_child_height) + 1;
}

//�־��� ��忡 ���� ����(height)�� ����Ͽ� ��ȯ�Ѵ�.
//sub size�� ����:���� �ڽ� ����� ũ�� + 1(������ ������ subTree�� ũ��)
template <typename T>
int AVLTree<T>::CalculateSubSize(Node<T>* node) {
    //�������� �ʴ� ����� ũ��� 0, ���� ����� ũ��� 1�� �����Ѵ�.
    if (node == NULL) return 0;


    int left_child_size = GetSize(node->get_left_child());
    int right_child_size = GetSize(node->get_right_child());

    return left_child_size + right_child_size + 1;
}

//�־��� ��忡 ���� ���� �μ�(balance factor)�� ����Ͽ� ��ȯ�Ѵ�. ��ȯ���� -2~2 �����̴�.
//BalanceFactor�� ����: �� �ڽ� ����� ������ -> left child - right child�� ����
template <typename T>
int AVLTree<T>::CalculateBalanceFactor(Node<T>* node) {
    if (node == NULL) return 0; //�������� �ʴ� ����� �����μ��� 0���� ����

    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    //���� isUnBalance���� �ұ��� ���̽�(UNBLANCE_CASE)�� �з��ϱ� ���� ������ ������ �ʰ� ��ȯ�Ѵ�.
    return left_child_height - right_child_height;
}


//�־��� ��忡 ���� ���� ���θ� �Ǵ��Ͽ� ��ȯ�Ѵ�. ��ȯ���� 0(BALANCE), 1~4(UNBALNCE) �����̴�.
template <typename T>
int AVLTree<T>::IsUnbalance(Node<T>* curNode) {
    int balance_factor = CalculateBalanceFactor(curNode);
    if (abs(balance_factor) < 2) return BALANCE;

    //�������� �ݿ�: yNode�� �� �ڽ� ��尡 ������ ���(child_balance_factor==0) single rotation�� �����ϵ��� �Ѵ�.
    //cf. ���� �ڵ�� yNode�� balance_factor=1�� ���� LEFT_LEFT�� ��ȯ������, �������׿� ���� 1 or 0�� ���� ���ǹ��� �ٲپ���.

    //zNode�� balance_factor == 2: LL Ȥ�� LR
    if (balance_factor > 0) {
        int child_balance_factor = CalculateBalanceFactor(curNode->get_left_child()); //yNode�� balance_factor
        return (child_balance_factor < 0) ? LEFT_RIGHT : LEFT_LEFT;
    }
    //zNode�� balance_factor == -2: RR Ȥ�� RL
    else {
        int child_balance_factor = CalculateBalanceFactor(curNode->get_right_child()); //yNode�� balance_factor
        return (child_balance_factor > 0) ? RIGHT_LEFT : RIGHT_RIGHT;
    }

}

//�־��� ����� rank ��ȯ. ����Լ��� ���� �ڽź��� ���� ���� ������ �����ش�.
template <typename T>
int AVLTree<T>::GetRank(Node<T>* node, T key) {
    //basecase: ������ NULL�̶�� �������� �ʴ� ���̹Ƿ� 0�� ��ȯ
    if (node == NULL)return 0;

    T node_key = node->get_key();
    //���� Ű�� �� ū ��� ����+�ڽ��� ���� �� �������� Ž���غ��� ��
    if (node_key < key) {
        int sub_rank = GetSize(node->get_left_child()) + 1;
        return sub_rank + GetRank(node->get_right_child(), key);
    }
    //���� Ű�� �����ϴٸ� �� �ڽ��� ��ġ�� ã�� ���̹Ƿ� �����ڽ��� ũ��+1(�ڽ�)�� ��ȯ
    else if (node_key == key) {
        int sub_rank = GetSize(node->get_left_child()) + 1;
        return sub_rank;
    }
    //���� Ű�� �� �۴ٸ� �������� �� ������ Ž���ؾ� ��
    else {
        return GetRank(node->get_left_child(), key);
    }
}

//�������� ������ ������ ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::Insert(Node<T>* node, T key) {
    //������ �ڸ��� ã�� ��� -> �� ��带 �Ҵ��Ͽ� ��ȯ
    if (node == NULL) {
        return new Node<T>(key);
    }
    //������ �ڸ��� ã�� ���� ��� -> ��������� �������� ���� ��ġ Ž��
    (node->get_key() < key) ?
        node->set_right_child(Insert(node->get_right_child(), key)) :
        node->set_left_child(Insert(node->get_left_child(), key));

    //������ ������ ���ο� �ڽ� ��尡 �߰��Ǿ����Ƿ� ����, ũ�� ����
    node->set_height(CalculateHeight(node));
    node->set_sub_size(CalculateSubSize(node));

    //�籸��ȭ ����
    return Restruct(node);

}

//�������� ������ ������ ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::DeleteNode(Node<T>* root, T key) {
    if (root == NULL) return root;

    // ������ Ű�� ã��
    if (key < root->get_key()) {
        root->set_left_child(DeleteNode(root->get_left_child(), key));
    }
    else if (key > root->get_key()) {
        root->set_right_child(DeleteNode(root->get_right_child(), key));
    }
    else {
        // key == root->get_key()�� ������ ��带 ã�� ���̴� ���� ����
        if ((root->get_left_child() == NULL) || (root->get_right_child() == NULL)) {
            Node<T>* temp = root->get_left_child() ? root->get_left_child() : root->get_right_child();

            // �ڽ� ��尡 ���� ��� ���� ����
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                // �� ���� �ڽ��� ���� ��� �ڽ� ��带 ������ ����� ��ġ�� �̵���Ŵ
                *root = *temp;
            }
            delete temp;
        }
        else {
            // �� ���� �ڽ��� ���� ��� �����ڸ� �̿��Ͽ� ���� ����
            Node<T>* temp = MinValueNode(root->get_right_child());
            root->set_key(temp->get_key());
            root->set_right_child(DeleteNode(root->get_right_child(), temp->get_key()));
        }
    }

    // Ʈ���� ����ִ� ���
    if (root == NULL) return root;

    //������ ������ �ִ� �ڽ� ��尡 �����Ǿ����Ƿ� ����, ũ�� ����
    root->set_height(CalculateHeight(root));
    root->set_sub_size(CalculateSubSize(root));

    // ���� ������
    return Restruct(root);
}


// �־��� ����� ����Ʈ������ ���� ���� ���� ���� ��带 ã�� ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::MinValueNode(Node<T>* node) {
    Node<T>* current = node;
    while (current->get_left_child() != NULL) {
        current = current->get_left_child();
    }
    return current;
}

//�־��� ��尡 �ұ����� ��� ������ ȸ���Ͽ� ������ ���� ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::Restruct(Node<T>* node) {
    switch (IsUnbalance(node)) { //���� ���� �Ǵ��� isUnbalance���� �����Ͽ� ��ȯ
        //���� -> 0���� ȸ�� �ʿ�
    case BALANCE: {
        return node;
    }

                //�ұ���1 -> 1���� ȸ�� �ʿ�(single rotate)
    case LEFT_LEFT: {
        return RightRotate(node);
    }
    case RIGHT_RIGHT: {
        return LeftRotate(node);
    }

                    //�ұ���2 -> 2���� ȸ�� �ʿ�(double rotate)
    case LEFT_RIGHT: {
        Node<T>* child_node = node->get_left_child();
        node->set_left_child(LeftRotate(child_node)); //yNode�� ���� left rotate ����
        return RightRotate(node); //zNode�� ���� right rotate ����
    }
    case RIGHT_LEFT: {
        Node<T>* child_node = node->get_right_child();
        node->set_right_child(RightRotate(child_node)); //yNode�� ���� right rotate ����
        return LeftRotate(node); //zNode�� ���� left rotate ����
    }
    }
    return node;
}

//������ �� ��带 �μ��� �޾� ������ ȸ���� ��, �� ���(sub tree) ���Ӱ� ��Ʈ�� �� ��带 ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::RightRotate(Node<T>* zNode) {
    Node<T>* yNode = zNode->get_left_child(); //ȸ�� ��� sub root�� �� ���
    Node<T>* tNode = yNode->get_right_child();

    //ȸ�� ����
    yNode->set_right_child(zNode); //yNode�� right child�� tNode���� zNode�� �ٲ۴�.
    zNode->set_left_child(tNode); //zNode�� left child�� yNode���� yNode�� ���� right child(=tNode)�� �ٲ۴�.

    //ȸ���ϸ鼭 ��ġ�� �޶������Ƿ� ���� ����
    zNode->set_height(CalculateHeight(zNode));
    yNode->set_height(CalculateHeight(yNode));


    //ȸ���ϸ鼭 ũ�Ⱑ �޶������Ƿ� ũ�� ����
    zNode->set_sub_size(CalculateSubSize(zNode));
    yNode->set_sub_size(CalculateSubSize(yNode));

    return yNode;
}

//������ �� ��带 �μ��� �޾� ���� ȸ���� ��, �� ���(sub tree) ���Ӱ� ��Ʈ�� �� ��带 ��ȯ�Ѵ�.
template <typename T>
Node<T>* AVLTree<T>::LeftRotate(Node<T>* zNode) {
    Node<T>* yNode = zNode->get_right_child(); //ȸ�� ��� sub root�� �� ���
    Node<T>* tNode = yNode->get_left_child();

    //ȸ�� ����
    yNode->set_left_child(zNode); //yNode�� left child�� tNode���� zNode�� �ٲ۴�.
    zNode->set_right_child(tNode); //zNode�� right child�� yNode���� yNode�� ���� left child(=tNode)�� �ٲ۴�.

    //ȸ���ϸ鼭 ��ġ�� �޶������Ƿ� ���� ����
    zNode->set_height(CalculateHeight(zNode));
    yNode->set_height(CalculateHeight(yNode));

    //ȸ���ϸ鼭 ũ�Ⱑ �޶������Ƿ� ũ�� ����
    zNode->set_sub_size(CalculateSubSize(zNode));
    yNode->set_sub_size(CalculateSubSize(yNode));

    return yNode;
}

#endif // AVL_TREE_H

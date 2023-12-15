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

#include "AVLTree.h"
using namespace std;

// Node Ŭ������ ������ �� ��� �Լ� ����
Node::Node(int key) : key_(key), height_(0), sub_size_(1), left_child_(NULL), right_child_(NULL) {}

Node::~Node() {}

int Node::get_key() { return key_; }
int Node::get_height() { return height_; }
int Node::get_sub_size() { return sub_size_; }
Node* Node::get_left_child() { return left_child_; }
Node* Node::get_right_child() { return right_child_; }

void Node::set_key(int key) { key_ = key; }
void Node::set_height(int height) { height_ = height; }
void Node::set_left_child(Node* left_child) { left_child_ = left_child; }
void Node::set_right_child(Node* right_child) { right_child_ = right_child; }
void Node::set_sub_size(int sub_size) { sub_size_ = sub_size; }

// AVLTree Ŭ������ ������ �� ��� �Լ� ����
AVLTree::AVLTree() : root_(NULL) {}

Node* AVLTree::get_root() { return root_; }

void AVLTree::set_root(Node* root) { root_ = root; }


int AVLTree::GetHeight(Node* node) { return (node == NULL) ? -1 : node->get_height(); }
int AVLTree::GetSize(Node* node) { return (node == NULL) ? 0 : node->get_sub_size(); }

bool AVLTree::Empty() {
    return GetSize(root_) == 0;
}

int AVLTree::Size() {
    return GetSize(root_);
}
//------------------------------------------------------------------------------------------------------�׽�Ʈ�� ���� ����
//void AVLTree::Empty() { printf("%d\n", (GetSize(root_) == 0) ? 1 : 0); }
//void AVLTree::Size() { printf("%d\n", GetSize(root_)); }
//------------------------------------------------------------------------------------------------------

KeyDepthPair AVLTree::Maximum(int x) {
    Node* maximum_node = GetNode(x);
    while (maximum_node->get_right_child() != NULL) {
        maximum_node = maximum_node->get_right_child();
    }
    return { maximum_node->get_key(), GetDepth(maximum_node) };
}

KeyDepthPair AVLTree::Minimum(int x) {
    Node* minimum_node = GetNode(x);
    while (minimum_node->get_left_child() != NULL) {
        minimum_node = minimum_node->get_left_child();
    }
    return { minimum_node->get_key(), GetDepth(minimum_node) };
}

DepthRankPair AVLTree::Rank(int x) {
    Node* rank_node = GetNode(x);

    if (rank_node == NULL) {
        return { 0, 0 }; // ��� x�� ���� ���, depth�� rank ��� 0���� ����
    }
    else {
        int depth = GetDepth(rank_node);
        int rank = GetRank(get_root(), rank_node->get_key());
        return { depth, rank }; // ��� x�� �����ϴ� ���, �ش� depth�� rank�� ��ȯ
    }
}

int AVLTree::Find(int x) {
    Node* find_node = GetNode(x);

    if (find_node == NULL) {
        return -1;  // ��尡 �������� ������ -1 ��ȯ
    }
    else {
        return GetDepth(find_node);  // ��尡 �����ϸ� �ش� ����� ���� ��ȯ
    }
}



// ----------------------------------------------------------------------------------------------------------------------------------------------
/*
//��� x�� depth�� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::Find(int x) {
    Node* find_node = GetNode(x); //key == x�� ��� ã��

    //find_node�� NULL�̶�� ��尡 ���ٴ� ���̹Ƿ� 0�� ����ϰ�, �ƴ϶�� ����� depth�� ����Ѵ�.
    if (find_node == NULL) printf("0\n");
    else printf("%d\n", GetDepth(find_node));

    return;
}

//��� x�� ��Ʈ�� �κ�Ʈ������ �ִ� key�� ���� ����� key�� depth�� �������� �����Ͽ� ����Ѵ�.
void AVLTree::Maximum(int x) {
    Node* maximum_node = GetNode(x); //key == x�� ��� ã�� -> sub root

    //�ִ� key�� sub root�� ���� ���ϴܿ� ��ġ�� ������ ����̹Ƿ� loop�� �ش� �������� ��������.
    while (maximum_node->get_right_child() != NULL) { //������ �ڽ��� NULL�̶�� �ִ�� ������ ���̹Ƿ� �ݺ��� ����
        maximum_node = maximum_node->get_right_child();
    }
    printf("%d %d\n", maximum_node->get_key(), GetDepth(maximum_node));

    return;
}

//��� x�� ��Ʈ�� �κ�Ʈ������ �ּ� key�� ���� ����� key�� depth�� �������� �����Ͽ� ����Ѵ�.
void AVLTree::Minimum(int x) {
    Node* minimum_node = GetNode(x);

    //�ּ� key�� sub root�� ���� ���ϴܿ� ��ġ�� ���� ����̹Ƿ� loop�� �ش� �������� ��������.
    while (minimum_node->get_left_child() != NULL) { //���� �ڽ��� NULL�̶�� �ִ�� ������ ���̹Ƿ� �ݺ��� ����
        minimum_node = minimum_node->get_left_child();
    }
    printf("%d %d\n", minimum_node->get_key(), GetDepth(minimum_node));

    return;
}
*/
// ----------------------------------------------------------------------------------------------------------------------------------------------




//���ο� ��� x�� �����ϰ�, ��� x�� depth�� ����Ѵ�.
void AVLTree::Insert(int x) {
    //��� ����. �������� ������ private �Լ����� �����Ѵ�.
    set_root(Insert(root_, x));

    //������ ����� depth�� ����Ѵ�.
    Node* new_node = GetNode(x);
    printf("%d\n", GetDepth(new_node));

    return;
}




// ----------------------------------------------------------------------------------------------------------------------------------------------
/*
//��� x�� depth�� rank�� �������� �����Ͽ� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::Rank(int x) {
    Node* rank_node = GetNode(x); // key == x�� ��� ã��

    // ��� x�� ���ٸ� 0�� ����ϰ� �����Ѵ�.
    if (rank_node == NULL) {
        printf("0\n");
        return;
    }
    // ��� x�� �����Ѵٸ� depth�� rank�� ����Ѵ�.
    else {
        int depth = GetDepth(rank_node);
        int rank = GetRank(get_root(), rank_node->get_key());
        printf("%d %d\n", depth, rank);
        return;
    }
}
*/
// ----------------------------------------------------------------------------------------------------------------------------------------------


//��� x�� depth�� ����ϰ� �ش� ��带 �����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::Erase(int x) {
    Node* node_to_delete = GetNode(x); // ������ ��� ã��

    //���� ��尡 ������ 0�� ����ϰ� �����Ѵ�.
    if (node_to_delete == NULL) {
        printf("0\n");
        return;
    }

    //������ ����� ���� ���
    int depth = GetDepth(node_to_delete);
    printf("%d\n", depth);

    //��� ����. �������� ������ private �Լ����� �����Ѵ�.
    root_ = DeleteNode(root_, x);

    return;
}



//�־��� key�� ��ġ�ϴ� ��带 ã�� ����� �����͸� ��ȯ�Ѵ�.
Node* AVLTree::GetNode(int key) {
    Node* current_node = get_root(); //root���� ����

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
int AVLTree::GetDepth(Node* current_node) {
    if (current_node == get_root()) return 0; //root�� ���̴� 0���� ����

    //root���� �����Ͽ� Ư�� ��带 ã�� ������ depth�� 1������Ű�� ��������.
    int depth = 0;
    int key = current_node->get_key();
    Node* tempNode = root_;
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
int AVLTree::CalculateHeight(Node* node) {
    //�������� �ʴ� ����� ���̴� -1, ���� ����� ���̴� 0���� �����Ѵ�.
    if (node == NULL) return -1;

    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    return max(left_child_height, right_child_height) + 1;
}

//�־��� ��忡 ���� ����(height)�� ����Ͽ� ��ȯ�Ѵ�.
//sub size�� ����:���� �ڽ� ����� ũ�� + 1(������ ������ subTree�� ũ��)
int AVLTree::CalculateSubSize(Node* node) {
    //�������� �ʴ� ����� ũ��� 0, ���� ����� ũ��� 1�� �����Ѵ�.
    if (node == NULL) return 0;


    int left_child_size = GetSize(node->get_left_child());
    int right_child_size = GetSize(node->get_right_child());

    return left_child_size + right_child_size + 1;
}

//�־��� ��忡 ���� ���� �μ�(balance factor)�� ����Ͽ� ��ȯ�Ѵ�. ��ȯ���� -2~2 �����̴�.
//BalanceFactor�� ����: �� �ڽ� ����� ������ -> left child - right child�� ����
int AVLTree::CalculateBalanceFactor(Node* node) {
    if (node == NULL) return 0; //�������� �ʴ� ����� �����μ��� 0���� ����

    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    //���� isUnBalance���� �ұ��� ���̽�(UNBLANCE_CASE)�� �з��ϱ� ���� ������ ������ �ʰ� ��ȯ�Ѵ�.
    return left_child_height - right_child_height;
}


//�־��� ��忡 ���� ���� ���θ� �Ǵ��Ͽ� ��ȯ�Ѵ�. ��ȯ���� 0(BALANCE), 1~4(UNBALNCE) �����̴�.
int AVLTree::IsUnbalance(Node* curNode) {
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
int AVLTree::GetRank(Node* node, int key) {
    //basecase: ������ NULL�̶�� �������� �ʴ� ���̹Ƿ� 0�� ��ȯ
    if (node == NULL)return 0;

    int node_key = node->get_key();
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
Node* AVLTree::Insert(Node* node, int key) {
    //������ �ڸ��� ã�� ��� -> �� ��带 �Ҵ��Ͽ� ��ȯ
    if (node == NULL) {
        return new Node(key);
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
Node* AVLTree::DeleteNode(Node* root, int key) {
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
            Node* temp = root->get_left_child() ? root->get_left_child() : root->get_right_child();

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
            Node* temp = MinValueNode(root->get_right_child());
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
Node* AVLTree::MinValueNode(Node* node) {
    Node* current = node;
    while (current->get_left_child() != NULL) {
        current = current->get_left_child();
    }
    return current;
}

//�־��� ��尡 �ұ����� ��� ������ ȸ���Ͽ� ������ ���� ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
Node* AVLTree::Restruct(Node* node) {
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
        Node* child_node = node->get_left_child();
        node->set_left_child(LeftRotate(child_node)); //yNode�� ���� left rotate ����
        return RightRotate(node); //zNode�� ���� right rotate ����
    }
    case RIGHT_LEFT: {
        Node* child_node = node->get_right_child();
        node->set_right_child(RightRotate(child_node)); //yNode�� ���� right rotate ����
        return LeftRotate(node); //zNode�� ���� left rotate ����
    }
    }
    return node;
}

//������ �� ��带 �μ��� �޾� ������ ȸ���� ��, �� ���(sub tree) ���Ӱ� ��Ʈ�� �� ��带 ��ȯ�Ѵ�.
Node* AVLTree::RightRotate(Node* zNode) {
    Node* yNode = zNode->get_left_child(); //ȸ�� ��� sub root�� �� ���
    Node* tNode = yNode->get_right_child();

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
Node* AVLTree::LeftRotate(Node* zNode) {
    Node* yNode = zNode->get_right_child(); //ȸ�� ��� sub root�� �� ���
    Node* tNode = yNode->get_left_child();

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
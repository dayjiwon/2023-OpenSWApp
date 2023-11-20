#include "AVLTree.h"
using namespace std;

// Node Ŭ���� ����
Node::Node(int key) : key_(key), height_(1) {
    left_child_ = right_child_ = NULL;
}

Node::~Node() {}

int Node::get_key() { return key_; }
int Node::get_height() { return height_; }
Node* Node::get_left_child() { return left_child_; }
Node* Node::get_right_child() { return right_child_; }

void Node::set_key(int key) { key_ = key; }
void Node::set_height(int height) { height_ = height; }
void Node::set_left_child(Node* left_child) { left_child_ = left_child; }
void Node::set_right_child(Node* right_child) { right_child_ = right_child; }


// AVLTree Ŭ���� ����
AVLTree::AVLTree() : root_(NULL), size_(0) {}

int AVLTree::get_size() { return size_; }
Node* AVLTree::get_root() { return root_; }

void AVLTree::IncreaseSize() { size_++; }
void AVLTree::DecreaseSize() { size_--; }
void AVLTree::set_root(Node* root) { root_ = root; }

void AVLTree::Empty() { (size_ == 0) ? printf("1\n") : printf("0\n"); }
void AVLTree::Size() { printf("%d\n", size_); }

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

//��� x�� depth�� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::Find(int x) {
    Node* find_node = GetNode(x); //key == x�� ��� ã��

    //GetNode()�� �ش� ��尡 ������ �� ����� �����͸�, ���ٸ� NULL�� ��ȯ�Ѵ�. 
    //���� find_node�� NULL�̶�� ��尡 ���ٴ� ���̹Ƿ� 0�� ����ϰ�, �ƴ϶�� ����� depth�� ����Ѵ�.
    if (find_node == NULL) printf("0\n");
    else printf("%d\n", GetDepth(find_node));

    return;
}

//���ο� ��� x�� �����ϰ�, ��� x�� depth�� ����Ѵ�.
void AVLTree::Insert(int x) {
    set_root(Insert(root_, x)); //��� ����: �������� ������ private �Լ����� �����Ѵ�.
    IncreaseSize(); //��尡 �߰��Ǿ����Ƿ� size�� 1 ������Ų��.

    Node* new_node = GetNode(x); //������ ����� ������ ��������
    printf("%d\n", GetDepth(new_node)); //������ ����� depth�� ����Ѵ�.

    return;
}

//��� x�� depth�� rank�� �������� �����Ͽ� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::Rank(int x)
{
    Node* rank_node = GetNode(x); // key == x�� ��� ã��

    if (rank_node == NULL) printf("0\n"); // ��� x�� ���ٸ� 0 ���
    else
    { // ��� x�� ������ ��
        printf("%d ", GetDepth(rank_node));
        printf("%d\n", GetRank(get_root(), rank_node->get_key()) + 1); // ��� x�� rank ���
    }
}

//��� x�� depth�� ����ϰ� �ش� ��带 �����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::Erase(int x) {
    Node* node_to_delete = GetNode(x); // ������ ��� ã��
    if (node_to_delete == NULL) {
        printf("0\n"); // ��尡 ������ 0 ���
        return;
    }

    printf("%d\n", GetDepth(node_to_delete)); // ������ ����� ���� ���
    root_ = DeleteNode(root_, x); // ��� ���� �� ��Ʈ ������Ʈ
    DecreaseSize(); // Ʈ�� ũ�� ����
}

//�־��� key�� ��ġ�ϴ� ��带 ã�� ����� �����͸� ��ȯ�Ѵ�.
Node* AVLTree::GetNode(int key) {
    Node* current_node = get_root(); //root���� ����

    while (true) {
        if (current_node == NULL) return NULL; //ã�� ����
        else if (current_node->get_key() == key) return current_node; //ã�� ����

        //AVL tree�� ����(left child < root < right child)�� ����Ͽ�, ���� Ȥ�� �Ʒ������� �������� Ž���Ѵ�.
        current_node = (current_node->get_key() < key) ?
            current_node->get_right_child() : current_node->get_left_child();
    }

    return current_node;
}

//�־��� ��忡 ���� ����(depth)�� ����Ͽ� ��ȯ�Ѵ�.
int AVLTree::GetDepth(Node* current_node) {
    if (current_node == get_root()) return 0; //root�� ���̴� 0���� ����

    //root���� �����Ͽ� Ư�� ���(current_node)�� ã�� ������ ������ ������ depth�� 1������Ű�� ī��Ʈ�Ѵ�.
    int depth = 0;
    int key = current_node->get_key();
    Node* tempNode = root_;
    while (true) {
        if (current_node == tempNode) return depth;

        //�̶� AVL tree�� ����(left child < root < right child)�� ����Ͽ�, ���� Ȥ�� �Ʒ������� ��������.
        tempNode = (tempNode->get_key() < key) ?
            tempNode->get_right_child() : tempNode->get_left_child();

        depth++;
    }
}

int AVLTree::GetHeight(Node* node) {
    return (node == NULL) ? 0 : node->get_height();
}

//�־��� ��忡 ���� ����(height)�� ����Ͽ� ��ȯ�Ѵ�.
int AVLTree::CalculateHeight(Node* node) {
    if (node == NULL) return -1; //�������� �ʴ� ����� ���̴� -1, ���� ����� ���̴� 0���� ����

    //������ ����:�� �ڽ� ��� �� �� �� ū height�� ������ �ڽ� ����� height + 1
    //���� ���� �ڽ� ����� height�� ��������� ���� ���Ѵ�.
    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    return max(left_child_height, right_child_height) + 1;
}


//�־��� ��忡 ���� ���� �μ�(balance factor, left-right)�� ����Ͽ� ��ȯ�Ѵ�. ��ȯ���� -2~2 �����̴�.
int AVLTree::CalculateBalanceFactor(Node* node) {
    if (node == NULL) return 0; //�������� �ʴ� ����� �����μ��� 0���� ����

    //�����μ��� ����: �� �ڽ� ����� ������ -> left child - right child�� ����
    //���� isUnBalance���� �ұ��� ���̽�(UNBLANCE_CASE)�� �з��ϱ� ���� ������ ������ �ʰ� ��ȯ�Ѵ�.
    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    return left_child_height - right_child_height;
}


//�־��� ��忡 ���� ���� ���θ� �Ǵ��Ͽ� ��ȯ�Ѵ�. ��ȯ���� 0(BALANCE), 1~4(UNBALNCE) �����̴�.
int AVLTree::IsUnbalance(Node* curNode) {
    int balance_factor = CalculateBalanceFactor(curNode);
    if (abs(balance_factor) < 2) return BALANCE;

    //�������� �ݿ�: yNode�� �� �ڽ� ��尡 ������ ���(child_balance_factor==0) single rotation�� �����ϵ��� �Ѵ�.
    //cf. ���� �ڵ�� yNode�� balance_factor=1�� ���� LEFT_LEFT�� ��ȯ������, �������׿� ���� 1 or 0�� ���� ���ǹ��� �ٲپ���.
    if (balance_factor > 0) { //zNode�� balance_factor == 2: LL Ȥ�� LR
        int child_balance_factor = CalculateBalanceFactor(curNode->get_left_child()); //yNode�� balance_factor
        return (child_balance_factor < 0) ? LEFT_RIGHT : LEFT_LEFT;
    }

    else { //zNode�� balance_factor == -2: RR Ȥ�� RL
        int child_balance_factor = CalculateBalanceFactor(curNode->get_right_child()); //yNode�� balance_factor
        return (child_balance_factor > 0) ? RIGHT_LEFT : RIGHT_RIGHT;
    }

}

//�־��� ����� rank ��ȯ. ����Լ��� ���� �ڽź��� ���� ���� ������ �����ش�.
int AVLTree::GetRank(Node* node, int x) {
    if (node == NULL) return 0; // ��尡 �������� ������ 0 ����

    int rank = 0;
    if (node->get_key() < x) rank++;

    rank += GetRank(node->get_left_child(), x);
    rank += GetRank(node->get_right_child(), x);

    return rank;
}

//�������� ������ ������ ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
Node* AVLTree::Insert(Node* node, int key) {
    //������ �ڸ��� ã�� ��� -> �� ��带 �Ҵ��Ͽ� ��ȯ
    if (node == NULL) {
        return new Node(key);
    }

    //������ �ڸ��� ã�� ���� ��� -> ��������� �������� ���� ��ġ Ž��
    //AVL tree�� ����(left child < root < right child)�� ����Ͽ�, ���� Ȥ�� �Ʒ������� ��������.
    (node->get_key() < key) ?
        node->set_right_child(Insert(node->get_right_child(), key)) :
        node->set_left_child(Insert(node->get_left_child(), key));

    //������ ������ ���ο� �ڽ� ��尡 �߰��Ǿ����Ƿ� ���� ����
    node->set_height(CalculateHeight(node));

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

    // ���� ������Ʈ
    root->set_height(CalculateHeight(root));

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
        Node* child_node = node->get_left_child(); //yNode ������ ����
        node->set_left_child(LeftRotate(child_node)); //yNode�� ���� left rotate ����
        return RightRotate(node); //zNode�� ���� right rotate ����
    }
    case RIGHT_LEFT: {
        Node* child_node = node->get_right_child(); //yNode ������ ����
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

    return yNode;
}
/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                        Libraries, Types, Global variables..                                      */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

//balance�ϴٸ� 0(=false), unbalance�ϴٸ� 1~4(=true)
enum UNBLANCE_CASE {
    BALANCE = 0, 
    LEFT_LEFT = 1, 
    RIGHT_RIGHT = 2, 
    LEFT_RIGHT = 3, 
    RIGHT_LEFT = 4 
};




/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                                 Class declaration                                                */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

struct Node {
public:
    //�����ڿ� �Ҹ���
    Node(int key) : key_(key), height_(1) { left_child_ = right_child_ = NULL; }
    ~Node() {}

    //������
    int get_key() { return key_; }
    int get_height() { return (this == NULL) ? -1 : height_; }
    Node* get_left_child() { return left_child_; }
    Node* get_right_child() { return right_child_; }

    //������
    void set_key(int key) { key_ = key; }
    void set_height(int height) { height_ = height; }
    void set_left_child(Node* left_child) { left_child_ = left_child; }
    void set_right_child(Node* right_child) { right_child_ = right_child; }

private:

    int key_;
    int height_;
    Node* left_child_;
    Node* right_child_;
};


class AVLTree {
public:
    //������
    AVLTree() : root_(NULL), size_(0) {}

    //������
    int get_size() { return size_; }
    Node* get_root() { return root_; }

    //������
    void increaseSize() { size_++; }
    void decreaseSize() { size_--; }
    void set_root(Node* root) { root_ = root; }

    //�䱸 ����(basic)
    void empty() { (size_ == 0) ? printf("1\n") : printf("0\n"); }
    void size() { printf("%d\n", size_); }
    void minimum(int x);
    void maximum(int x);
    void find(int x);
    void insert(int x);

    //�䱸 ����(advance)
    void rank(int x);
    void erase(int x);

private:
    //��� ���� ��� �Լ�
    Node* getNode(int key);
    int getDepth(Node* node);
    int getHeight(Node* node) { return (node == NULL) ? 0 : node->get_height(); }
    int isUnbalance(Node* node);
    int calculateBalanceFactor(Node* node);
    int calculateHeight(Node* node);

    //��� ������ ���� �߰����� �Լ�
    Node* insert(Node* node, int key);
    Node* restruct(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

private:
    Node* root_;
    int size_;
};




/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                                  main function                                                   */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        AVLTree avlTree;
        int q;
        cin >> q;
        while (q--) {
            string command;
            cin >> command;

            //�߰� �Է�(x) ���ʿ�
            if (command == "empty") {
                avlTree.empty();
                continue;
            }
            if (command == "size") {
                avlTree.size();
                continue;
            }

            //�߰� �Է�(x) �ʿ� 
            int x;
            cin >> x;
            if (command == "minimum") {
                avlTree.minimum(x);
                continue;
            }
            if (command == "maximum") {
                avlTree.maximum(x);
                continue;
            }
            if (command == "find") {
                avlTree.find(x);
                continue;
            }
            if (command == "insert") {
                avlTree.insert(x);
                continue;
            }
            if (command == "rank") {
                avlTree.rank(x);
                continue;
            }
            if (command == "erase") {
                avlTree.erase(x);
                continue;
            }
        }
    }
}




/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                          AVLTree Class : Requirements definition                                 */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

//��� x�� depth�� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::find(int x) {
    Node* find_node = getNode(x); //key == x�� ��� ã��

    if (find_node == NULL) printf("0\n");
    else printf("%d\n", getDepth(find_node));

    return;
}

//��� x�� ��Ʈ�� �κ�Ʈ������ �ִ� key�� ���� ����� key�� depth�� �������� �����Ͽ� ����Ѵ�.
void AVLTree::maximum(int x) {
    Node* maximum_node = getNode(x); //key == x�� ��� ã�� -> sub root

    //�ִ� key: sub root�� ���� ������ ��� -> loop�� �ش� �������� ��������.
    while (maximum_node->get_right_child() != NULL) {
        maximum_node = maximum_node->get_right_child();
    }
    printf("%d %d\n", maximum_node->get_key(), getDepth(maximum_node));
    
    return;
}

//��� x�� ��Ʈ�� �κ�Ʈ������ �ּ� key�� ���� ����� key�� depth�� �������� �����Ͽ� ����Ѵ�.
void AVLTree::minimum(int x) {
    Node* minimum_node = getNode(x);

    //�ּ� key: sub root�� ���� ���� ��� -> loop�� �ش� �������� ��������.
    while (minimum_node->get_left_child() != NULL) {
        minimum_node = minimum_node->get_left_child();
    }
    printf("%d %d\n", minimum_node->get_key(), getDepth(minimum_node));

    return;
}

//���ο� ��� x�� �����ϰ�, ��� x�� depth�� ����Ѵ�.
void AVLTree::insert(int x) {
    //��� ����
    set_root(insert(root_, x));
    increaseSize();

    Node* new_node = getNode(x); //������ ����� ������ ��������
    printf("%d\n", getDepth(new_node));

    return;
}

//��� x�� depth�� rank�� �������� �����Ͽ� ����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::rank(int x) {

}

//��� x�� depth�� ����ϰ� �ش� ��带 �����Ѵ�. ���� ��� x�� ���ٸ�, 0�� ����Ѵ�.
void AVLTree::erase(int x) {

}


/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                        AVLTree Class : private function definition                               */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

//�־��� key�� ��ġ�ϴ� ��带 ã�� ����� �����͸� ��ȯ�Ѵ�.
Node* AVLTree::getNode(int key) {
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
int AVLTree::getDepth(Node* current_node) {
    if (current_node == get_root()) return 0; //root�� ���̴� 0���� ����

    int depth = 0;
    int key = current_node->get_key();
    Node* tempNode = root_;
    while (true) {
        if (current_node == tempNode) return depth;

        //AVL tree�� ������ ����Ͽ�, ���� Ȥ�� �Ʒ������� �������� depth�� ������Ų��.
        tempNode = (tempNode->get_key() < key) ? 
            tempNode->get_right_child() : tempNode->get_left_child();

        depth++;
    }
}


//�־��� ��忡 ���� ����(height)�� ����Ͽ� ��ȯ�Ѵ�.
int AVLTree::calculateHeight(Node* node) {
    if (node == NULL) return -1; //�������� �ʴ� ����� ���̴� -1, ���� ����� ���̴� 0���� ����

    int left_child_height = getHeight(node->get_left_child());
    int right_child_height = getHeight(node->get_right_child());

    return max(left_child_height, right_child_height) + 1;
}


//�־��� ��忡 ���� ���� �μ�(balance factor, left-right)�� ����Ͽ� ��ȯ�Ѵ�. ��ȯ���� -2~2 �����̴�.
int AVLTree::calculateBalanceFactor(Node* node) {
    if (node == NULL) return 0; //�������� �ʴ� ����� �����μ��� 0���� ����

    int left_child_height = getHeight(node->get_left_child());
    int right_child_height = getHeight(node->get_right_child());

    return left_child_height - right_child_height;
}


//�־��� ��忡 ���� ���� ���θ� �Ǵ��Ͽ� ��ȯ�Ѵ�. ��ȯ���� 0(BALANCE), 1~4(UNBALNCE) �����̴�.
int AVLTree::isUnbalance(Node* curNode) {
    int balance_factor = calculateBalanceFactor(curNode);
    if (abs(balance_factor) < 2) return BALANCE;

    //�������� �ݿ�: yNode�� �� �ڽ� ��尡 ������ ���(child_balance_factor==0) single rotation�� �����ϵ��� �Ѵ�.
    if (balance_factor > 0) { //LL Ȥ�� LR
        int child_balance_factor = calculateBalanceFactor(curNode->get_left_child());
        return (child_balance_factor < 0) ? LEFT_RIGHT : LEFT_LEFT; 
    }

    else {
        int child_balance_factor = calculateBalanceFactor(curNode->get_right_child());
        return (child_balance_factor > 0) ? RIGHT_LEFT : RIGHT_RIGHT;
    }

}

//�������� ������ ������ ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
Node* AVLTree::insert(Node* node, int key) {
    //������ �ڸ��� ã�� ��� -> �� ��带 �Ҵ��Ͽ� ��ȯ
    if (node == NULL) {
        return new Node(key);
    }

    //������ �ڸ��� ã�� ���� ��� -> ��������� �������� ���� ��ġ Ž��
    (node->get_key() < key) ?
        node->set_right_child(insert(node->get_right_child(), key)):
        node->set_left_child(insert(node->get_left_child(), key));

    //������ ������ ���ο� �ڽ� ��尡 �߰��Ǿ����Ƿ� ���� ����
    node->set_height(calculateHeight(node));

    //�籸��ȭ ����
    return restruct(node);
    
}

//�־��� ��尡 �ұ����� ��� ������ ȸ���Ͽ� ������ ���� ��, ���� Ʈ���� ��Ʈ ��带 ��ȯ�Ѵ�.
Node* AVLTree::restruct(Node* node) {
    switch (isUnbalance(node)) { //���� ���� �Ǵ�
    //���� -> 0���� ȸ�� �ʿ�
    case BALANCE: {
        return node;
    }

    //�ұ���1 -> 1���� ȸ�� �ʿ�(single rotate)
    case LEFT_LEFT: {
        return rightRotate(node);
    }
    case RIGHT_RIGHT: {
        return leftRotate(node);
    }

    //�ұ��� -> 2���� ȸ�� �ʿ�(double rotate)
    case LEFT_RIGHT: {
        Node* child_node = node->get_left_child();
        node->set_left_child(leftRotate(child_node));
        return rightRotate(node);
    }
    case RIGHT_LEFT: {
        Node* child_node = node->get_right_child();
        node->set_right_child(rightRotate(child_node));
        return leftRotate(node);
    }
    }
    return node;
}

//������ �� ��带 �μ��� �޾� ������ ȸ���� ��, �� ���(sub tree) ���Ӱ� ��Ʈ�� �� ��带 ��ȯ�Ѵ�.
Node* AVLTree::rightRotate(Node* zNode) {
    Node* yNode = zNode->get_left_child();
    Node* tNode = yNode->get_right_child();

    //ȸ�� ����
    yNode->set_right_child(zNode);
    zNode->set_left_child(tNode);

    //ȸ���ϸ鼭 ��ġ�� �޶������Ƿ� ���� ����
    zNode->set_height(calculateHeight(zNode));
    yNode->set_height(calculateHeight(yNode));

    return yNode;
}

//������ �� ��带 �μ��� �޾� ���� ȸ���� ��, �� ���(sub tree) ���Ӱ� ��Ʈ�� �� ��带 ��ȯ�Ѵ�.
Node* AVLTree::leftRotate(Node* zNode) {
    Node* yNode = zNode->get_right_child();
    Node* tNode = yNode->get_left_child();

    //ȸ�� ����
    yNode->set_left_child(zNode);
    zNode->set_right_child(tNode);

    //ȸ���ϸ鼭 ��ġ�� �޶������Ƿ� ���� ����
    zNode->set_height(calculateHeight(zNode));
    yNode->set_height(calculateHeight(yNode));

    return yNode;
}


#include <iostream> 
/*AVLtree의 node 클래스*/
class Node {
public:
    int key; 
    Node* left; 
    Node* right; 
    int height; 
    
    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};
/*AVLtree의 클래스 정의*/
class AvlTree { 


    Node* root; 
    /*노드의 height반환*/
    int getHeight(Node* n) { 
        if (n == nullptr) return 0;
        return n->height;
    }
    /*노드의 왼쪽과 오른쪽 서브트리의 높이 차이 반환*/
    int getBalanceFactor(Node* n) { 
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }
    /*노드 오른쪽으로 회전*/
    Node* rightRotate(Node* y) { 
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }
    /*노드 왼쪽으로 회전*/
    Node* leftRotate(Node* x) { 
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }
    /*노드 삽입 함수*/
    Node* insertNode(Node* n, int key) { 
        if (n == nullptr) return new Node(key);

        if (key < n->key) {
            n->left = insertNode(n->left, key);
        }
        else if (key > n->key) {
            n->right = insertNode(n->right, key);
        }
        else {
            return n;
        }

        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        int balance = getBalanceFactor(n);

        if (balance > 1 && key < n->left->key)
            return rightRotate(n);

        if (balance < -1 && key > n->right->key)
            return leftRotate(n);

        if (balance > 1 && key > n->left->key) {
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

        if (balance < -1 && key < n->right->key) {
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }

        return n;
    }

    bool isEmpty() const { 
        return root == nullptr;
    }

public:
    AvlTree() : root(nullptr) {} 
    /*key를 삽입하는 함수*/
    void insert(int key) {
        root = insertNode(root, key); 
    }
    /*트리가 비었는지 확인하는 함수*/
    bool empty() const {
        return isEmpty(); 
    }
};

// 
int main() {
    AvlTree t; 
    t.insert(10);
    //t.insert(20);
    //t.insert(5);

    std::cout << "Tree empty? " << (t.empty() ? "Yes" : "No") << std::endl; 
    return 0;
}

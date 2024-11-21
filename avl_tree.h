#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include <algorithm> //std::max()를 사용하기 위함
#include <iostream>
#include "node.h"

/*AVLtree의 클래스 정의*/
template <typename T>
class AvlTree : public BinarySearchTreeSet<T> {

public:
  AvlTree() : BinarySearchTreeSet<T>{} {}

  ~AvlTree() {
    deleteTree(root); // 동적 메모리 해제
  }

  /*key를 삽입하는 함수*/
  void insert(int key) { root = insertNode(root, key); }
  /*트리가 비었는지 확인하는 함수*/
  bool empty() const { return isEmpty(); }

  /* Node 객체를 재귀적으로 삭제하여 메모리 해제 */
  void deleteTree(Node *node) {
    if (node != nullptr) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }
  /*노드의 height반환*/
  int getHeight(Node *n) {
    if (n == nullptr)
      return 0; // node가 없으면 0 반환, 존재하면 높이 반환
    return n->height;
  }
  /*노드의 왼쪽과 오른쪽 서브트리의 높이 차이 반환*/
  int getBalanceFactor(Node *n) {
    if (n == nullptr)
      return 0; // node가 없으면 0 반환, 존재하면 왼쪽과 오른쪽 서브트리의
                // 높이차이 반환
    return getHeight(n->left) - getHeight(n->right);
  }
  /*노드 오른쪽으로 회전*/
  Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y; //회전
    y->left = T2;

    y->height =
        std::max(getHeight(y->left), getHeight(y->right)) + 1; //높이 갱신
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; //회전 후 새로운 루트 반환
  }
  /*노드 왼쪽으로 회전*/
  Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x; //회전
    x->right = T2;

    x->height =
        std::max(getHeight(x->left), getHeight(x->right)) + 1; //높이 갱신
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; //회전 후 새로운 루트 반환
  }
  /*노드 삽입 함수*/
  Node *insertNode(Node *n, int key) {
    if (n == nullptr)
      return new Node(key);

    if (key < n->key) {
      n->left = insertNode(n->left, key); //재귀함수
    } else if (key > n->key) {
      n->right = insertNode(n->right, key);
    } else {
      return n;
    }

    n->height =
        1 + std::max(getHeight(n->left), getHeight(n->right)); //높이 갱신
    int balance = getBalanceFactor(n);

    if (balance > 1 && key < n->left->key) //한 node의 왼쪽 서브트리의 왼쪽
                                           //자식node쪽에 node가 삽입되는 경우
      return rightRotate(n);

    if (balance < -1 &&
        key > n->right->key) //한 node의 오른쪽 서브트리의 오른쪽 자식node쪽에
                             // node가 삽입되는 경우
      return leftRotate(n);

    if (balance > 1 && key > n->left->key) { //한 node의 왼쪽 서브트리의 오른쪽
                                             //자식node쪽에 node가 삽입되는 경우
      n->left = leftRotate(n->left);
      return rightRotate(n);
    }

    if (balance < -1 &&
        key < n->right->key) { //한 node의 오른쪽 서브트리의 왼쪽 자식node쪽에
                               // node가 삽입되는 경우
      n->right = rightRotate(n->right);
      return leftRotate(n);
    }

    return n;
  }

  bool isEmpty() const { return root == nullptr; }
};

  // 복사 생성자 관련 추후 논의 필요
  // DISALLOW_COPY_AND_ASSIGN(AvlTree);
private:
  Node *root; // AVLtree의 루트node 포인터

#endif

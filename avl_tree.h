#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "set.h"
#include <algorithm>

/**
 * AVL 트리 클래스
 * 기능 : AVL 트리 기능 구현
 * 설명 : 이진 탐색 트리의 서브클래스로서, AVL트리에서의 기능을 구현
 */
template <typename T> class AvlTree : public Set<T> {
public:
  // 기본 기능 : Insert 함수
  int Insert(T key) override {
    root_ = InsertNode(root_, key, 0);
    // 루트 노드 부모 설정
    root_->parent_ = nullptr;
    return Find(key);
  }

  // 고급 기능 : Erase 함수
  int Erase(T key) override {
    int findNode = Find(key); // 삭제 전 노드의 깊이와 높이의 합
    if (findNode == 0) {
      // 노드가 존재하지 않는 경우
      return 0;
    } else {
      root_ = EraseNode(root_, key);
      // 루트 노드 부모 설정
      if (root_)
        root_->parent_ = nullptr;
      return findNode;
    }
  }

private:
  /**
   * 기능 : AVL Tree Node 삽입 함수
   * 동작 :
   * 입력값 : root, 삽입하고자 하는 key 값, 현재 depth 값
   * 결과값 :
   */
  Node<T> *InsertNode(Node<T> *node, T key, int depth) {
    if (!node) {
      // 새 노드 삽입 시 크기 증가 ->  BST의 Size 함수에서 반환
      this->size_++;
      return new Node<T>(key);
    }

    if (key < node->key_) {
      node->left_ = InsertNode(node->left_, key, depth + 1);
      node->left_->parent_ = node; // 부모 설정
    } else if (key > node->key_) {
      node->right_ = InsertNode(node->right_, key, depth + 1);
      node->right_->parent_ = node; // 부모 설정
    } else
      return node; // 중복 키는 삽입하지 않음

    // 균형 조정
    ReBalanceTree(node);

    // 높이 갱신
    node = NodeHeightUpdate(node);

    return node;
  }

  /**
   * 기능 : AVL Tree Node 삭제 함수
   * 동작 : 트리에서 특정 키 값을 가진 노드를 삭제하고 트리를 균형 상태로 유지
   * 입력값 : node - 현재 트리의 루트 노드 포인터, key - 삭제할 키 값
   * 결과값 : 새로운 트리의 루트 노드 포인터
   */
  Node<T> *EraseNode(Node<T> *node, T key) {

    // 0. 기본 삭제 과정
    if (!node)
      return node;

    if (key < node->key_) {
      node->left_ = EraseNode(node->left_, key);
      if (node->left_)
        node->left_->parent_ = node; // 부모 설정
    } else if (key > node->key_) {
      node->right_ = EraseNode(node->right_, key);
      if (node->right_)
        node->right_->parent_ = node; // 부모 설정
    }
    // 삭제해야 할 노드일 경우
    // 2. 자식 노드 수에 따라 삭제
    else {
      // 자식 노드가 하나 이하인 경우
      if (!node->left_ || !node->right_) {
        Node<T> *replace_node = node->left_ ? node->left_ : node->right_;
        // 2.1 자식이 없는 경우 (리프 노드)
        if (!replace_node) {
          replace_node = node;
          node = nullptr;
        }
        // 2.2 자식이 하나인 경우
        else {
          *node = *replace_node;
        }
        delete replace_node;
        // 노드 삭제 시 크기 감소
        this->size_--;
      } else {
        // 2.3 자식이 둘인 경우 후임자(successor)를 찾아 대체
        Node<T> *replace_node = Set::FindMinNode(node->right_);
        node->key_ = replace_node->key_;
        node->right_ = EraseNode(node->right_, replace_node->key_);
        if (node->right_)
          node->right_->parent_ = node; // 부모 설정
      }
    }

    // 3. 트리가 하나의 노드만 가지고 있었던 경우
    if (!node)
      return node;

    // 4. 균형 조정
    ReBalanceTree(node);

    // 5. 높이 갱신
    node = NodeHeightUpdate(node);

    return node;
  }

  /**
   * 기능 : 트리의 균형을 맞추기 위한 함수
   * 동작 :
   * 입력값 :
   * 결과값 :
   */
  Node<T> *ReBalanceTree(Node<T> *node) {
    // 균형 인수 계산
    int balance = GetBalanceFactor(node);

    // LL 회전: 왼쪽 자식이 무거운 경우
    if (balance > 1 && GetBalanceFactor(node->left_) >= 0)
      return RightRotate(node);

    // LR 회전: 왼쪽 자식의 오른쪽 자식이 무거운 경우
    if (balance > 1 && GetBalanceFactor(node->left_) < 0) {
      node->left_ = LeftRotate(node->left_);
      node->left_->parent_ = node; // 부모 설정
      return RightRotate(node);
    }

    // RR 회전: 오른쪽 자식이 무거운 경우
    if (balance < -1 && GetBalanceFactor(node->right_) <= 0)
      return LeftRotate(node);

    // RL 회전: 오른쪽 자식의 왼쪽 자식이 무거운 경우
    if (balance < -1 && GetBalanceFactor(node->right_) > 0) {
      node->right_ = RightRotate(node->right_);
      node->right_->parent_ = node; // 부모 설정
      return LeftRotate(node);
    }

    return node;
  }

  /**
   * 기능 : 노드의 높이를 갱신하는 함수
   * 동작 : 노드의 왼쪽과 오른쪽 자식의 높이를 기반으로 현재 노드의 높이를 갱신
   * 입력값 : 높이를 갱신할 노드
   * 결과값 : 없음
   */
  void NodeHeightUpdate(Node<T> *node) {
    int left_height = node->left_ ? node->left_->height_ : 0;
    int right_height = node->right_ ? node->right_->height_ : 0;
    node->height_ = 1 + std::max(left_height, right_height);
  }

  /**
   * 기능 :
   * 동작 : 노드의 균형 인수 계산
   * 입력값 : 노드의 포인터
   * 결과값 : 왼쪽 서브트리 높이와 오른쪽 서브트리 높이의 차
   */
  int GetBalanceFactor(Node<T> *node) {
    if (node == nullptr)
      return 0;
    // 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
    int left_height = node->left_ ? node->left_->height_ : 0;
    int right_height = node->right_ ? node->right_->height_ : 0;
    return left_height - right_height;
  }

  /**
   * 기능 : 오른쪽 회전
   * 동작 :
   * 입력값 :
   * 출력값 :
   */
  Node<T> *RightRotate(Node<T> *y) {
    Node<T> *x = y->left_;
    Node<T> *T2 = x->right_;

    x->right_ = y;
    y->left_ = T2;

    // 부모 업데이트
    x->parent_ = y->parent_;
    y->parent_ = x;
    if (T2)
      T2->parent_ = y;

    // 높이 업데이트
    NodeHeightUpdate(y);
    NodeHeightUpdate(x);

    return x;
  }

  /**
   * 기능 : 왼쪽 회전
   * 동작 :
   * 입력값 :
   * 출력값 :
   */
  Node<T> *LeftRotate(Node<T> *x) {
    Node<T> *y = x->right_;
    Node<T> *T2 = y->left_;

    y->left_ = x;
    x->right_ = T2;

    // 부모 업데이트
    y->parent_ = x->parent_;
    x->parent_ = y;
    if (T2)
      T2->parent_ = x;

    // 높이 업데이트
    NodeHeightUpdate(x);
    NodeHeightUpdate(y);

    return y;
  }
};

#endif

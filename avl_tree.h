#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "binary_search_tree.h"
#include <algorithm>

/**
*AVL 트리 클래스
* 기능 : AVL 트리 상의 기능 구현
* 설명 : 이진 탐색 트리의 서브클래스로서, AVL트리에서의 기능을 구현
*/
template <typename T>
class AvlTree : public BinaryTree<T> {
public:
    /** 
    * AVL Insert 함수(인터페이스)
    * 입력값 : root, key 값
    */
    template <typename T>
    void Insert(T key) override {
        this->root_ = InsertNode(this->root_, key);
    }

private:
    /**
    * AVL Insert 기능 구현
    * 입력값 : 현재 node, 삽입할 key 값
    */
    template <typename T>
    Node<T>* InsertNode(Node<T>* node, T key) {
        if (!node) {
            this->size_++; // 새 노드 삽입 시 크기 증가 ->  BST의 Size 함수에서 반환
            return new Node<T>(key);
        }

        if (key < node->key_)
            node->left_ = InsertNode(node->left_, key);
        else if (key > node->key_)
            node->right_ = InsertNode(node->right_, key);
        else
            return node; // 중복 키는 삽입하지 않음

        // 높이 갱신
        node->height_ = 1 + std::max(this->GetHeightNode(node->left_), this->GetHeightNode(node->right_));

        // 균형 인수 계산
        int balance = GetBalanceFactor(node);

        // LL 회전: 왼쪽 자식이 무거운 경우
        if (balance > 1 && key < node->left_->key_)
            return RightRotate(node);

        // RR 회전: 오른쪽 자식이 무거운 경우
        if (balance < -1 && key > node->right_->key_)
            return LeftRotate(node);

        // LR 회전: 왼쪽 자식의 오른쪽 자식이 무거운 경우
        if (balance > 1 && key > node->left_->key_) {
            node->left_ = LeftRotate(node->left_);
            return RightRotate(node);
        }

        // RL 회전: 오른쪽 자식의 왼쪽 자식이 무거운 경우
        if (balance < -1 && key < node->right_->key_) {
            node->right_ = RightRotate(node->right_);
            return LeftRotate(node);
        }

        return node;
    }

    /**
    * 노드의 균형 인수 계산
    * 입력값 : 노드의 포인터
    * 출력값 : 왼쪽 서브트리 높이와 오른쪽 서브트리 높이의 차
    */
    template <typename T>
    int GetBalanceFactor(Node<T>* node) {
        if (node == nullptr)
            return 0;
        //왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
        return this->GetHeightNode(node->left_) - this->GetHeightNode(node->right_);
    }

    /**
    * 오른쪽 회전
    */
    template <typename T>
    Node<T>* RightRotate(Node<T>* y) {
        Node<T>* x = y->left_;
        Node<T>* T2 = x->right_;

        x->right_ = y;
        y->left_ = T2;

        y->height_ = 1 + std::max(this->GetHeightNode(y->left_), this->GetHeightNode(y->right_));
        x->height_ = 1 + std::max(this->GetHeightNode(x->left_), this->GetHeightNode(x->right_));

        return x;
    }

    /**
    * 왼쪽 회전
    */
    template <typename T>
    Node<T>* LeftRotate(Node<T>* x) {
        Node<T>* y = x->right_;
        Node<T>* T2 = y->left_;

        y->left_ = x;
        x->right_ = T2;

        x->height_ = 1 + std::max(this->GetHeightNode(x->left_), this->GetHeightNode(x->right_));
        y->height_ = 1 + std::max(this->GetHeightNode(y->left_), this->GetHeightNode(y->right_));

        return y;
    }
};

#endif

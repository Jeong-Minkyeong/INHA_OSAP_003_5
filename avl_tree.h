#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "binary_tree.h"
#include <algorithm>

// AVL 트리 클래스
template <typename T>
class AvlTree : public BinaryTree<T> {
public:
    // AVL 삽입 구현
    void insert(T key) {
        this->root_ = insertNode(this->root_, key);
    }

private:
    Node<T>* insertNode(Node<T>* node, T key) {
        if (!node) return new Node<T>(key);

        if (key < node->key_)
            node->left_ = insertNode(node->left_, key);
        else if (key > node->key_)
            node->right_ = insertNode(node->right_, key);
        else
            return node; // 중복 키는 삽입하지 않음

        // 높이 갱신
        node->height_ = 1 + std::max(this->getHeight(node->left_), this->getHeight(node->right_));

        // 균형 인수 계산
        int balance = getBalanceFactor(node);

        // LL 회전
        if (balance > 1 && key < node->left_->key_)
            return rightRotate(node);

        // RR 회전
        if (balance < -1 && key > node->right_->key_)
            return leftRotate(node);

        // LR 회전
        if (balance > 1 && key > node->left_->key_) {
            node->left_ = leftRotate(node->left_);
            return rightRotate(node);
        }

        // RL 회전
        if (balance < -1 && key < node->right_->key_) {
            node->right_ = rightRotate(node->right_);
            return leftRotate(node);
        }

        return node;
    }

    int getBalanceFactor(Node<T>* node) {
        if (node == nullptr)
            return 0;
        return this->getHeight(node->left_) - this->getHeight(node->right_);
    }

    Node<T>* rightRotate(Node<T>* y) {
        Node<T>* x = y->left_;
        Node<T>* T2 = x->right_;

        x->right_ = y;
        y->left_ = T2;

        y->height_ = 1 + std::max(this->getHeight(y->left_), this->getHeight(y->right_));
        x->height_ = 1 + std::max(this->getHeight(x->left_), this->getHeight(x->right_));

        return x;
    }

    Node<T>* leftRotate(Node<T>* x) {
        Node<T>* y = x->right_;
        Node<T>* T2 = y->left_;

        y->left_ = x;
        x->right_ = T2;

        x->height_ = 1 + std::max(this->getHeight(x->left_), this->getHeight(x->right_));
        y->height_ = 1 + std::max(this->getHeight(y->left_), this->getHeight(y->right_));

        return y;
    }
};

#endif

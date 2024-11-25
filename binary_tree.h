#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "node.h"

/*기본 이진 트리 클래스*/
template <typename T>
class BinaryTree {
public:
    BinaryTree() : root_(nullptr) {}

    virtual ~BinaryTree() { deleteTree(); }

    /*트리를 비우는 메서드*/
    void deleteTree() { deleteTree(root_); }

    /*트리가 비어 있는지 확인*/
    bool empty() const { return root_ == nullptr; }

    /*노드 x의 깊이와 높이의 합 반환(인터페이스)*/
    int find(T x) const {
        return find(root_, x, 0); // 초기 깊이는 0으로 시작
    }

    /*트리의 노드 개수 반환(인터페이스)*/
    int size() const {
        return countNodes(root_);
    }

    /*트리에 새 노드 삽입(인터페이스)*/
    virtual void insert(T key) { root_ = insertNode(root_, key); }



protected:
    Node<T>* root_;  // 트리의 루트 노드

    /*노드의 높이를 계산*/ 
    int getHeight(Node<T>* node) const {
        return node ? node->height_ : 0;
    }

    /*재귀적으로 트리를 삭제*/
    void deleteTree(Node<T>* node) {
        if (node) {
            deleteTree(node->left_);
            deleteTree(node->right_);
            delete node;
        }
    }

private:
    /*재귀적으로 노드를 삽입*/
    Node<T>* insertNode(Node<T>* node, T key) {
        if (!node) return new Node<T>(key);

        if (key < node->key_)
            node->left_ = insertNode(node->left_, key);
        else if (key > node->key_)
            node->right_ = insertNode(node->right_, key);

        return node;
    }

    /*노드의 깊이와 높이 합 계산*/
    int find(Node<T>* node, T x, int depth) const {
        if (!node) return 0;

        if (node->key_ == x) {
            return depth + getHeight(node); // 깊이 + 높이
        }

        /*왼쪽 또는 오른쪽에서 검색*/
        int left = find(node->left_, x, depth + 1);
        if (left > 0) return left; // 왼쪽에서 찾았으면 반환

        return find(node->right_, x, depth + 1); // 오른쪽 검색
    }

    /*트리의 노드 개수 계산*/
    int countNodes(Node<T>* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left_) + countNodes(node->right_);
    }
};

#endif

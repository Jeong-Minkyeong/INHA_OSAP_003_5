#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "node.h"

/**
 * 이진 탐색 트리 클래스
 * 기능: 기본 이진 탐색
 * 설명: 이진 탐색 기능을 하는 클래스.ㅌ AVL트리에 기본 기능을 상속해주는 역할.
*/
template <typename T>
class BinaryTree {
public:
    BinaryTree() : root_(nullptr), size_(0) {}

    virtual ~BinaryTree() { DeleteTree(); }

    // 트리를 비우는 메서드
    void DeleteTree() {
        DeleteTree(root_);
        size_ = 0; // 트리 삭제 시 크기 초기화
    }

    //트리가 비어 있는지 확인
    bool Empty() const { return root_ == nullptr; }

    //Find 함수(인터페이스)
    int Find(T x) const {
        return FindNode(root_, x, 0); // 초기 깊이는 0으로 시작
    }

    // Size 함수 (인터페이스)
    int Size() const {
        return size_; // size_ 반환
    }

    // Insert 함수 (인터페이스)
    virtual void Insert(T key) {
        root_ = InsertNode(root_, key);
    }

protected:
    Node<T>* root_;  // 트리의 루트 노드
    int size_;       // 트리의 노드 개수를 저장하는 멤버 변수

    //노드의 높이를 계산
    int GetHeightNode(Node<T>* node) const {
        return node ? node->height_ : 0;
    }

    //재귀적으로 트리를 삭제
    void DeleteTree(Node<T>* node) {
        if (node) {
            DeleteTree(node->left_);
            DeleteTree(node->right_);
            delete node;
        }
    }

private:
    /**
    * BST Insert 기능 구현
    * 기능 : 재귀적으로 노드를 삽입
    */
    template <typename T>
    Node<T>* InsertNode(Node<T>* node, T key) {
        if (!node) {
            size_++; // 새 노드 삽입 시 크기 증가 -> Size 기능 구현
            return new Node<T>(key);
        }

        if (key < node->key_)
            node->left_ = InsertNode(node->left_, key);
        else if (key > node->key_)
            node->right_ = InsertNode(node->right_, key);
        
        return node;
    }

    /**
    * FInd 기능 구현
    * 기능 : 노드의 깊이와 높이 합 계산
    */
    template <typename T>
    int FindNode(Node<T>* node, T x, int depth) const {
        if (!node) return 0;

        if (node->key_ == x) {
            return depth + GetHeightNode(node); // 깊이 + 높이
        }

        //왼쪽 또는 오른쪽에서 검색
        int left = FindNode(node->left_, x, depth + 1);
        if (left > 0) return left; // 왼쪽에서 찾았으면 반환

        return FindNode(node->right_, x, depth + 1); // 오른쪽 검색
    }
};

#endif

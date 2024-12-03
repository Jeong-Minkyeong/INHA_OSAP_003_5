#ifndef SET_H_
#define SET_H_

#include "node.h"
#include <iostream>

/**
 * 이진 탐색 트리 클래스
 * 기능 : 기본 이진 탐색
 * 설명 :
 * - 이진 탐색 기능을 하는 클래스. AVL트리에 기본 기능을 상속해주는 역할
 * - 기본 기능 + 고급 기능 + 추가 기능(기본, 고급 기능을 구현하는데 도움을 주는
 * 기능)으로 구성
 * - 기본 기능과 고급 기능은 사용자 인터페이스 부분과 구현 부분으로 나누어짐
 */
template <typename T> class Set {
public:
  Set() : root_(nullptr), size_(0) {}
  virtual ~Set() { Delete(); }

  // 추가 기능
  void Delete() { DeleteTree(root_); }
  Node<T> *GetRoot() { return root_; }

  // 기본 기능
  bool Empty() const { return root_ == nullptr; }
  int Size() const { return size_; }
  int Height() {
    return root_ ? root_->height_ - 1 : -1;
  } // 초기 root 노드의 높이가 1부터
  int Find(T key) const { return FindNode(root_, key, 0); }

  std::pair<int, int> Ancestor(T key) const {
    // key 값을 가진 노드의 깊이와 높이의 합
    int findNode = Find(key);
    // key 값을 가진 노드를 찾아 해당 노드의 포인터를 얻음
    Node<T> *selectNode = SelectNode(key);
    if (selectNode == root_) {
      return {findNode, 0};
    } else {
      // 루트 노드까지의 key 값들의 합을 저장할 변수 초기화
      int sum = 0;
      // 부모 노드를 따라가며 key 값을 더함
      while (selectNode->parent_) {
        selectNode = selectNode->parent_;
        sum += selectNode->key_;
      }
      return {findNode, sum};
    }
  }
  int Average(T key) const {
    // SelectNode로 키 값에 해당하는 노드 찾기
    Node<T> *selectNode = SelectNode(key);

    // 부분 트리에서 최솟값과 최댓값 찾기
    int minKey = FindMinNode(selectNode).key_;
    int maxKey = FindMaxNode(selectNode).key_;
    // 산술평균 계산
    int average = (minKey + maxKey) / 2.0;
    // 결과 출력
    return average;
  }

  // 서브클래스에서 overriding
  virtual int Insert(T key) = 0;
  virtual int Erase(T key) = 0;

  // 고급 기능

protected:
  Node<T> *root_; // 트리의 루트 노드
  int size_;      // 트리의 노드 개수를 저장하는 멤버 변수

private:
  /**
   * 기능 : Tree 삭제
   * 동작 : 순회하면서 메모리 할당 해제
   * 입력값 : 특정 node
   * 결과값 : None
   */
  void DeleteTree(Node<T> *node) {
    if (node) {
      DeleteTree(node->left_);
      DeleteTree(node->right_);
      delete node;
    }
  }

  /**
   * 기능 : 특정 키 값을 가진 노드의 깊이와 높이의 합을 계산
   * 동작 : 재귀적으로 해당 키 값을 가진 노드를 찾아서 깊이와 높이의 합 반환
   * 입력값 : node - 현재 트리의 루트 노드 포인터, key - 찾고자 하는 키 값,
   * depth - 현재 깊이 결과값 : 해당 노드의 깊이와 높이의 합, 노드가 없는 경우 0
   */
  int FindNode(Node<T> *node, T key, int depth) const {
    if (!node)
      return 0;

    if (node->key_ == key) {
      return depth + node->height_ - 1; // 깊이 + 높이
    }

    // 왼쪽 또는 오른쪽에서 검색
    int left = FindNode(node->left_, key, depth + 1);
    if (left > 0)
      return left; // 왼쪽에서 찾았으면 반환

    return FindNode(node->right_, key, depth + 1); // 오른쪽 검색
  }

  /**
   * 기능 : node가 루트인 부분트리에서 노드들의 key_ 값의 최솟값 리턴
   * 동작 : 반복문을 통해서 key값이 가장 작은 노드를 찾아서 key_값 리턴
   * 입력값 : node - 찾고자 하는 부분트리의 루트
   * 결과값 : key_값이 최소인 node 리턴
   */
  Node<T> *FindMinNode(Node<T> *node) {
    while (node->left_ != nullptr)
      node = node->left_;
    return node;
  }
  /**
   * 기능 : node가 루트인 부분트리에서 노드들의 key 값의 최댓값 리턴
   * 동작 : 재귀적으로 해당 키 값을 가진 노드를 찾아서 리턴
   * 입력값 : node - 찬고자 하는 부분트리의 루트
   * 결과값 : key_값이 최대인 node 리턴
   */
  Node<T> *FindMaxNode(Node<T> *node) {
    while (node->right_ != nullptr)
      node = node->right_;
    return node;
  }

  /**
   * 기능 : 특정 키 값을 가진 노드를 리턴
   * 동작 : 재귀적으로 해당 키 값을 가진 노드를 찾아서 리턴
   * 입력값 : key - 찾고자 하는 키 값
   * 찾고자 하는 key값을 갖고 있는 Node가 없을 시 nullptr 리턴
   * 결과값 : key값을 갖고 있는 node 리턴
   */
  Node<T> *SelectNode(T key) const {
    Node<T> *currentNode = root_;
    while (currentNode) {
      if (currentNode->key_ == key) {
        return currentNode; // 원하는 키 값을 찾으면 반환
      }

      // 키 값에 따라 왼쪽 또는 오른쪽으로 이동
      if (key < currentNode->key_) {
        currentNode = currentNode->left_;
      } else {
        currentNode = currentNode->right_;
      }
    }

    return nullptr; // 키 값을 찾지 못한 경우 nullptr 반환
  }
};

#endif

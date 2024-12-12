/**
 * MIT License
 
Copyright (c) 2024 오픈소스응용프로그래밍 3분반 5팀

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Written by : 오픈소스응용프로그래밍 3분반 5팀
Date : 2024-11-26
*/

#ifndef SET_H_
#define SET_H_

#include "node.h"

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

  //***추가 기능
  void Delete() { DeleteTree(root_); }
  // 트리의 루트 노드를 수정해야 할 때
  Node<T> *&GetRoot() { return root_; }
  // 수정하지 않고 루트를 읽기만 할 때
  const Node<T> *GetRoot() const { return root_; }
  Node<T> *GetMinNode() { return FindMinNode(root_); }
  Node<T> *GetMaxNode() { return FindMaxNode(root_); }

  //***기본 기능
  bool Empty() const { return root_ == nullptr; }
  int Size() const { return size_; }
  int Height() const {
    return root_ ? root_->GetHeight() : -1;
  } // 초기 root 노드의 높이가 1부터
  std::pair<Node<T> *, int> Find(T key) const {
    return FindNode(root_, key, 0);
  }
  std::pair<int, int> Ancestor(T key) const { return AncestorNode(key); }
  int Average(T key) const { return AverageNode(key); }

  // 서브클래스에서 overriding
  virtual int Insert(T key) = 0;
  virtual int Erase(T key) = 0;

  //***고급 기능 : Rank 함수
  std::pair<int, int> Rank(T key) const {
    return GetNodeRank(root_, key, 0, 0);
  }

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
      DeleteTree(node->GetLeft());
      DeleteTree(node->GetRight());
      delete node;
    }
  }

  /**
   * 기능 : 특정 키 값을 가진 노드의 깊이와 높이의 합을 계산
   * 동작 : 재귀적으로 해당 키 값을 가진 노드를 찾아서 깊이와 높이의 합 반환
   * 입력값 : node - 현재 트리의 루트 노드 포인터, key - 찾고자 하는 키 값,
   * depth - 현재 깊이 결과값 : 해당 노드의 깊이와 높이의 합, 노드가 없는 경우 0
   */
  std::pair<Node<T> *, int> FindNode(Node<T> *node, T key, int depth) const {
    // 노드가 없으면 0 반환
    if (!node)
      return {nullptr, 0};

    if (node->GetKey() == key) {
      // 노드의 깊이 + 높이 반환
      return {node, depth + node->GetHeight()};
    } else if (key < node->GetKey()) {
      return FindNode(node->GetLeft(), key, depth + 1);
    } else {
      return FindNode(node->GetRight(), key, depth + 1);
    }
  }

  /**
   * 기능 : 특정 노드의 깊이 + 높이의 합과 랭크를 계산하는 함수
   * 동작 : 재귀적으로 트리를 순회하며 랭크와 합 계산
   * 입력값 : node - 현재 노드, key - 찾고자 하는 키 값, depth - 현재 깊이,
   * cur_rank - 현재까지 누적되어 계산된 랭크 결과값 : { 깊이 + 높이의 합, 순위
   * }
   */
  std::pair<int, int> GetNodeRank(Node<T> *node, T key, int depth,
                                  int cur_rank) const {
    if (node == nullptr) {
      // 노드를 찾지 못한 경우
      return {0, 0};
    }

    if (key < node->GetKey()) {
      // 왼쪽 서브트리로 이동
      return GetNodeRank(node->GetLeft(), key, depth + 1, cur_rank);
    } else if (key > node->GetKey()) {
      // 왼쪽 서브트리의 랭크 계산
      int left_rank = node->GetLeft() ? node->GetLeft()->GetRank() : 0;
      // 현재 노드의 랭크를 누적
      return GetNodeRank(node->GetRight(), key, depth + 1,
                         cur_rank + left_rank + 1);
    } else {
      // 노드를 찾은 경우
      int left_rank = node->GetLeft() ? node->GetLeft()->GetRank() : 0;
      int sum = depth + node->GetHeight();
      int rank = cur_rank + left_rank + 1;
      return {sum, rank};
    }
  }

  /**
   * 기능 :
   * 동작 :
   * 입력값 :
   * 결과값 :
   */
  std::pair<int, int> AncestorNode(T key) const {
    // key 값을 가진 노드의 깊이와 높이의 합
    std::pair<Node<T> *, int> findNode = Find(key);

    // key 값을 가진 노드를 찾아 해당 노드의 포인터를 얻음
    if (findNode.first == this->GetRoot()) {
      return {findNode.second, 0};
    } else {
      // 루트 노드까지의 key 값들의 합을 저장할 변수 초기화
      int sum = 0;
      // 부모 노드를 따라가며 key 값을 더함
      while (findNode.first->GetParent()) {
        findNode.first = findNode.first->GetParent();
        sum += findNode.first->GetKey();
      }
      return {findNode.second, sum};
    }
  }

  /**
   * 기능 :
   * 동작 :
   * 입력값 :
   * 결과값 :
   */
  int AverageNode(T key) const {
    // find로 키 값에 해당하는 노드 찾기
    std::pair<Node<T> *, int> findNode = Find(key);

    if (findNode.first == nullptr)
      return 0;

    // 부분 트리에서 최솟값과 최댓값 찾기
    int minKey = FindMinNode(findNode.first)->GetKey();
    int maxKey = FindMaxNode(findNode.first)->GetKey();
    // 산술평균 계산
    int average = (minKey + maxKey) / 2;
    // 결과 출력
    return average;
  }

  /**
   * 기능 : node가 루트인 부분트리에서 노드들의 key_ 값의 최솟값 리턴
   * 동작 : 반복문을 통해서 key값이 가장 작은 노드를 찾아서 key_값 리턴
   * 입력값 : node - 찾고자 하는 부분트리의 루트
   * 결과값 : key_값이 최소인 node 리턴
   */
  Node<T> *FindMinNode(Node<T> *node) const {
    while (node->GetLeft() != nullptr)
      node = node->GetLeft();
    return node;
  }

  /**
   * 기능 : node가 루트인 부분트리에서 노드들의 key 값의 최댓값 리턴
   * 동작 : 재귀적으로 해당 키 값을 가진 노드를 찾아서 리턴
   * 입력값 : node - 찬고자 하는 부분트리의 루트
   * 결과값 : key_값이 최대인 node 리턴
   */
  Node<T> *FindMaxNode(Node<T> *node) const {
    while (node->GetRight() != nullptr)
      node = node->GetRight();
    return node;
  }
};

#endif
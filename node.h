#ifndef NODE_H_
#define NODE_H_

/*AVLtree의 node 클래스*/
template <typename T>
class Node {
public:
  Node *left_;  // 왼쪽 자식node 포인터
  Node *right_; // 오른쪽 자식node 포인터
  int key_;     // node의 키값
  int rank_;    // node 랭크
  int height_;  // node 높이

// 기본 생성자
Node() : key_(nullptr), left_(nullptr), right_(nullptr), height_(-1), rank_(1) {}

// 키값으로 노드 초기화 하는 생성자
Node(int value) : key_(value), left_(nullptr), right_(nullptr), height_(1), rank_(1) {}

// 소멸자
  ~Node() {}
};

#endif
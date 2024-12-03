#ifndef NODE_H_
#define NODE_H_

/**
 * 노드 클래스
 * 기능 : tree의 요소를 Node 클래스로 정의
 * 설명 : 인자에 따라 node의 정보를 초기화
 */
template <typename T> class Node {
public:
  Node *parent_; // 부모 노드 포인터
  Node *left_;   // 왼쪽 자식 노드 포인터
  Node *right_;  // 오른쪽 자식 노드 포인터
  T key_;        // 노드의 키 값
  int height_;   // 노드 높이 (AVL 트리에서 사용)
  int rank_;     // 노드의 랭크(순위)

  // 기본 생성자
  Node()
      : key_(T()), parent_(nullptr), left_(nullptr), right_(nullptr),
        height_(1), rank_(1) {}

  // 키 값으로 초기화하는 생성자
  Node(T value)
      : key_(value), parent_(nullptr), left_(nullptr), right_(nullptr),
        height_(1), rank_(1) {}

  // 소멸자
  ~Node() {}
};

#endif

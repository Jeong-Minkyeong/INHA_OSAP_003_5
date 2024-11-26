#ifndef NODE_H_
#define NODE_H_

template <typename T>
class Node {
public:
    Node* left_;   // 왼쪽 자식 노드 포인터
    Node* right_;  // 오른쪽 자식 노드 포인터
    T key_;        // 노드의 키 값
    int height_;   // 노드 높이 (AVL 트리에서 사용)

    // 기본 생성자
    Node() : key_(T()), left_(nullptr), right_(nullptr), height_(1) {}

    // 키 값으로 초기화하는 생성자
    Node(T value) : key_(value), left_(nullptr), right_(nullptr), height_(1) {}

    // 소멸자
    ~Node() {}
};

#endif

#ifndef NODE_H_
#define NODE_H_

/**
 * 노드 클래스
 * 기능 : tree의 요소를 Node 클래스로 정의
 * 설명 : 인자에 따라 node의 정보를 초기화
 */
template <typename T>
class Node {
public:
    // 생성자
    Node();
    explicit Node(T value);

    // 소멸자
    ~Node();

    // 접근자 (Getter)
    Node* GetParent() const { return parent_; }
    Node*& GetLeft() { return left_; }
    Node*& GetRight() { return right_; }
    T GetKey() const { return key_; }
    int GetHeight() const { return height_; }
    int GetRank() const { return rank_; }

    // 설정자 (Setter)
    void SetParent(Node* parent) { parent_ = parent; }
    void SetLeft(Node* left) { left_ = left; }
    void SetRight(Node* right) { right_ = right; }
    void SetKey(T key) { key_ = key; }
    void SetHeight(int height) { height_ = height; }
    void SetRank(int rank) { rank_ = rank; }

private:
    Node* parent_;   // 부모 노드 포인터
    Node* left_;     // 왼쪽 자식 노드 포인터
    Node* right_;    // 오른쪽 자식 노드 포인터
    T key_;          // 노드의 키 값
    int height_;     // 노드 높이 (AVL 트리에서 사용)
    int rank_;       // 노드의 랭크(순위)
};

// 기본 생성자
template <typename T>
Node<T>::Node() 
    : parent_(nullptr), left_(nullptr), right_(nullptr),
      key_(T()), height_(1), rank_(1) {}

// 키 값으로 초기화하는 생성자
template <typename T>
Node<T>::Node(T value)
    : parent_(nullptr), left_(nullptr), right_(nullptr),
      key_(value), height_(1), rank_(1) {}

// 소멸자
template <typename T>
Node<T>::~Node() {}

#endif
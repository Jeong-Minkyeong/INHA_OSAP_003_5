#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "set.h"
#include <algorithm>

/**
 * AVL 트리 클래스
 * 기능 : AVL 트리 기능 구현
 * 설명 : 이진 탐색 트리의 서브클래스로서, AVL트리에서의 기능을 구현
 */
template <typename T>
class AvlTree : public Set<T> {
public:
    // 기본 기능 : Insert 함수
    int Insert(T key) override {
        return InsertNode(this->GetRoot(), key, 0);
    }

    // 고급 기능 : Erase 함수
    int Erase(T key) override {
        return EraseNode(this->GetRoot(), key, 0);
    }

private:
    /** 
     * 기능 : AVL Tree Node 삽입 함수
     * 동작 : 적절한 위치에 노드를 삽입하고, 삽입 후 균형 조정 수행
     * 입력값 : node - 현재 노드의 포인터, key - 삽입할 키 값, depth - 삽입하고자 하는 노드의 깊이
     * 결과값 : 삽입된 노드의 깊이와 높이의 합
     */
    int InsertNode(Node<T>*& node, T key, int depth) {
        if (!node) {
            node = new Node<T>(key);
            this->size_++;
            return depth + node->GetHeight(); // 깊이 + 높이 합 반환
        }

        int sum;
        if (key < node->GetKey()) {
            // 왼쪽 서브트리에 삽입
            sum = InsertNode(node->GetLeft(), key, depth + 1);
            node->GetLeft()->SetParent(node);
        }  
        else if (key > node->GetKey()) {
            // 오른쪽 서브트리에 삽입
            sum = InsertNode(node->GetRight(), key, depth + 1);
            node->GetRight()->SetParent(node);
        }
        else {
            return 0;
        }

        // 균형 조정
        node = ReBalanceTree(node);

        // 조정 후 높이 및 랭크 업데이트
        NodeHeightUpdate(node);
        NodeRankUpdate(node);

        return sum;
    }   


    /**
     * 기능 : AVL Tree Node 삭제 함수
     * 동작 : 트리에서 특정 키 값을 가진 노드를 삭제하고 트리를 균형 상태로 유지
     * 입력값 : node - 현재 노드의 포인터, key - 삭제할 키 값, depth - 삭제하고자 하는 노드의 깊이
     * 결과값 : 삭제된 노드의 깊이와 높이의 합
     */
    int EraseNode(Node<T>*& node, T key, int depth) {
        if (node == nullptr) {
            // 노드가 없으면 0 반환
            return 0;
        }

        int sum = 0;

        if (key < node->GetKey()) {
            sum = EraseNode(node->GetLeft(), key, depth + 1);
            // sum이 0 이상이면 삭제가 이루어졌다는 뜻
            if (sum > 0) {
                // 부모 설정
                if (node->GetLeft()) node->GetLeft()->SetParent(node);
                // 균형 조정
                node = ReBalanceTree(node);

                // 조정 후 높이 및 랭크 업데이트
                NodeHeightUpdate(node);
                NodeRankUpdate(node);
            }
        }
        else if (key > node->GetKey()) {
            sum = EraseNode(node->GetRight(), key, depth + 1);
            if (sum > 0) {
                // 부모 설정
                if (node->GetRight()) node->GetRight()->SetParent(node);
                // 균형 조정
                node = ReBalanceTree(node);

                // 조정 후 높이 및 랭크 업데이트
                NodeHeightUpdate(node);
                NodeRankUpdate(node);
            }
        }
        // 삭제해야 할 노드일 경우
        // 2. 자식 노드 수에 따라 삭제
        else {
            // 삭제해야하는 노드의 깊이와 높이의 합 계산
            sum = depth + node->GetHeight();

            // 자식 노드가 하나 이하인 경우
            if (!node->GetLeft() || !node->GetRight()) {
                Node<T>* replace_node = node->GetLeft() ? node->GetLeft() : node->GetRight();
                // 2.1 자식이 없는 경우 (리프 노드)
                if (!replace_node) {
                    delete node;
                    node = nullptr;
                } 
                // 2.2 자식이 하나인 경우
                else {
                    Node<T>* cur_node = node;
                    node = replace_node;
                     // 부모 설정
                    node->SetParent(cur_node->GetParent()); 
                    delete cur_node;
                }
                // 노드 삭제 시 크기 감소
                this->size_--;
            }
            else {
                // 2.3 자식이 둘인 경우 후임자(successor)를 찾아 대체
                Node<T>* replace_node = Set<T>::FindMinNode(node->GetRight());
                node->SetKey(replace_node->GetKey());
                // 후임자 노드를 삭제
                // 이때 반환되는 깊이와 높이의 합은 삭제 연산과 직접적인 관련이 없으므로 무시 가능
                int dummy_sum = EraseNode(node->GetRight(), replace_node->GetKey(), depth + 1);
                if (node->GetRight()) node->GetRight()->SetParent(node);
                // 균형 조정
                node = ReBalanceTree(node);

                // 조정 후 높이 및 랭크 업데이트
                NodeHeightUpdate(node);
                NodeRankUpdate(node);
            }
        }

        if (node != nullptr) {
            // 균형 조정
            node = ReBalanceTree(node);

            // 조정 후 높이 및 랭크 업데이트
            NodeHeightUpdate(node);
            NodeRankUpdate(node);
        }

        return sum;
    }


    /**
     * 기능 : 트리의 균형을 맞추기 위한 함수
     * 동작 : 균형 인수를 계산 후, 조건에 따른 회전 수행
     * 입력값 : node - 균형 조정을 수행할 노드
     * 결과값 : 균형 조정된 서브트리의 새로운 루트 노드
     */
    Node<T>* ReBalanceTree(Node<T>* node) {
        // 균형 인수 계산
        int balance = GetBalanceFactor(node);

        // LL 회전: 왼쪽 자식이 무거운 경우
        if (balance > 1 && GetBalanceFactor(node->GetLeft()) >= 0)
            return RightRotate(node);

        // LR 회전: 왼쪽 자식의 오른쪽 자식이 무거운 경우
        if (balance > 1 && GetBalanceFactor(node->GetLeft()) < 0) {
            node->GetLeft() = LeftRotate(node->GetLeft());
            node->GetLeft()->SetParent(node);
            return RightRotate(node);
        }

        // RR 회전: 오른쪽 자식이 무거운 경우
        if (balance < -1 && GetBalanceFactor(node->GetRight()) <= 0)
            return LeftRotate(node);

        // RL 회전: 오른쪽 자식의 왼쪽 자식이 무거운 경우
        if (balance < -1 && GetBalanceFactor(node->GetRight()) > 0) {
            node->GetRight() = RightRotate(node->GetRight());
            node->GetRight()->SetParent(node);
            return LeftRotate(node);
        }

        return node;
    }

    /**
     * 기능 : 노드의 높이를 갱신하는 함수
     * 동작 : 노드의 왼쪽과 오른쪽 자식의 높이를 기반으로 현재 노드의 높이를 갱신
     * 입력값 : node - 높이를 갱신할 노드
     * 결과값 : 없음
     */
    void NodeHeightUpdate(Node<T>* node) {
        int left_height = node->GetLeft() ? node->GetLeft()->GetHeight() : 0;
        int right_height = node->GetRight() ? node->GetRight()->GetHeight() : 0;
        node->SetHeight(1 + std::max(left_height, right_height));
    }

    /**
     * 기능 : 노드의 랭크를 갱신하는 함수
     * 동작 : 
     * 입력값 : node - 랭크를 갱신할 노드
     * 결과값 : 없음
     */
    void NodeRankUpdate(Node<T>* node) {
        int left_rank = node->GetLeft() ? node->GetLeft()->GetRank() : 0;
        int right_rank = node->GetRight() ? node->GetRight()->GetRank() : 0;
        node->SetRank(1 + left_rank + right_rank);
    }

    /**
     * 기능 : 노드의 균형 인수 계산 함수
     * 동작 : 왼쪽 서브트리의 높이와 오른쪽 서브트리의 높이의 차(균형 인수) 계산 후 반환 
     * 입력값 : node - 균형 인수를 계산할 노드
     * 결과값 : 균형 인수 (왼쪽 서브트리 높이 - 오른쪽 서브트리 높이)
     */
    int GetBalanceFactor(Node<T>* node) {
        if (node == nullptr)
            return 0;
        // 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
        int left_height = node->GetLeft() ? node->GetLeft()->GetHeight() : 0;
        int right_height = node->GetRight() ? node->GetRight()->GetHeight() : 0;
        return left_height - right_height;
    }

    /**
     * 기능 : 왼쪽 회전 수행 함수
     * 동작 : 불균형이 발생한 노드에서 왼쪽 회전 수행하여 트리의 균형 유지
     * 입력값 : node - 회전 수행할 불균형이 발생한 노드
     * 출력값 : 회전 후 서브트리의 새로운 루트 노드
     */

    /**
     * LeftRotate 예시
     * 
     *    node                  new_root
     *   /    \                 /      \
     *  A   new_root   ===>    node     C
     *      /      \          /    \
     *  moved_node  C        A  moved_node
     * 
     */
    Node<T>* LeftRotate(Node<T>* node) {
        // node: 회전 전의 루트 노드 (불균형이 발생한 노드)
        // new_root: node의 오른쪽 자식 노드 (회전 후 새로운 루트 노드가 됨)
        // moved_node: new_root의 왼쪽 자식 노드 (회전 과정에서 위치가 변경되는 서브트리)
        Node<T>* new_root = node->GetRight();
        Node<T>* moved_node = new_root->GetLeft();

        new_root->SetLeft(node);
        node->SetRight(moved_node);

        // 부모 업데이트
        new_root->SetParent(node->GetParent());
        node->SetParent(new_root);
        if (moved_node) moved_node->SetParent(node);

        // 높이 및 랭크 업데이트
        NodeHeightUpdate(node);
        NodeRankUpdate(node);

        NodeHeightUpdate(new_root);
        NodeRankUpdate(new_root);

        return new_root;
    }

    /**
     * 기능 : 오른쪽 회전 수행 함수
     * 동작 : 불균형이 발생한 노드에서 오른쪽 회전 수행하여 트리의 균형 유지
     * 입력값 : node - 회전 수행할 불균형이 발생한 노드
     * 출력값 : 회전 후 서브트리의 새로운 루트 노드
     */
    
    /**
     * RightRotate 예시
     * 
     *          node             new_root
     *         /    \            /      \
     *    new_root   C   ===>   A      node
     *     /     \                    /    \
     *    A  moved_node         moved_node  C
     * 
     */
    Node<T>* RightRotate(Node<T>* node) {
        // node: 회전 전의 루트 노드 (불균형이 발생한 노드)
        // new_root: node의 왼쪽 자식 노드 (회전 후 새로운 루트 노드가 됨)
        // moved_node: new_root의 오른쪽 자식 노드 (회전 과정에서 위치가 변경되는 서브트리)
        Node<T>* new_root = node->GetLeft();
        Node<T>* moved_node = new_root->GetRight();

        new_root->SetRight(node);
        node->SetLeft(moved_node);

        // 부모 업데이트
        new_root->SetParent(node->GetParent());
        node->SetParent(new_root);
        if (moved_node) moved_node->SetParent(node);


        // 높이 및 랭크 업데이트
        NodeHeightUpdate(node);
        NodeRankUpdate(node);

        NodeHeightUpdate(new_root);
        NodeRankUpdate(new_root);

        return new_root;
    }
};

#endif
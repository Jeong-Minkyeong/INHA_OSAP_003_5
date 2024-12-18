#include "node.h"
#include "avl_tree.h" 
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>




using namespace testing;

class AvlTreeSetFixture : public testing::Test
{

public:
  AvlTreeSetFixture();
  virtual ~AvlTreeSetFixture();
  void SetUp() override;
  void TearDown() override;
  static void SetUpTestCase();
  static void TearDownTestCase();

protected:
  AvlTree<int> avltree_set_;
};

AvlTreeSetFixture::AvlTreeSetFixture()
{
  // 생성자, 테스트 모음 실행 시 항상 실행됨
  std::cout << "Constructor called\n";
}
AvlTreeSetFixture::~AvlTreeSetFixture()
{
  // 소멸자, 테스트 모음 실행 시 항상 실행됨
  std::cout << "Destructor called\n";
}
void AvlTreeSetFixture::SetUp()
{
  /**
   * 테스트 시작 전 기본 설정
   * avltree_set_에 40, 20, 60을 key로 갖는 Node들을 순서대로 삽입
   * 기본 설정된 avltree_set_ 상태
   * 
   *     40
   *    /  \
   *   20  60
   * 
   */
  std::cout << "SetUp called\n";
  avltree_set_.Insert(40);
  avltree_set_.Insert(20);
  avltree_set_.Insert(60);
}
void AvlTreeSetFixture::TearDown()
{
  // 종료 후 항상 TeaDown 실행
  std::cout << "TearDown called\n";
}
void AvlTreeSetFixture::SetUpTestCase()
{
  // fixture를 선언할 때 서브 루틴 만들 수 있음
  std::cout << "SetUpTestCase called\n";
}
void AvlTreeSetFixture::TearDownTestCase()
{
  std::cout << "TearDownTestCase called\n";
}

// 기본 생성자 테스트 케이스
TEST_F(AvlTreeSetFixture, TestNodeDefaultConstructor) {
    // 기본 생성자를 사용하여 Node 객체를 생성
    Node<int> node;

    // 기본 생성자가 적절히 초기화되었는지 확인
    EXPECT_EQ(nullptr, node.GetParent());  // 부모는 nullptr
    EXPECT_EQ(nullptr, node.GetLeft());    // 왼쪽 자식은 nullptr
    EXPECT_EQ(nullptr, node.GetRight());   // 오른쪽 자식은 nullptr
    EXPECT_EQ(0, node.GetKey());           // 기본 키 값은 0
    EXPECT_EQ(1, node.GetHeight());        // 기본 높이는 1
    EXPECT_EQ(1, node.GetRank());          // 기본 랭크는 1
}

// 키 값으로 초기화하는 생성자 테스트 케이스
TEST_F(AvlTreeSetFixture, TestNodeConstructorWithKey) {
    // 특정 키 값으로 Node 객체를 생성
    Node<int> node(10);

    // 주어진 키 값이 제대로 설정되었는지 확인
    EXPECT_EQ(nullptr, node.GetParent());  // 부모는 nullptr
    EXPECT_EQ(nullptr, node.GetLeft());    // 왼쪽 자식은 nullptr
    EXPECT_EQ(nullptr, node.GetRight());   // 오른쪽 자식은 nullptr
    EXPECT_EQ(10, node.GetKey());          // 키 값은 10
    EXPECT_EQ(1, node.GetHeight());        // 기본 높이는 1
    EXPECT_EQ(1, node.GetRank());          // 기본 랭크는 1
}

// 존재하지 않는 key 값에 대한 Find 함수 테스트
TEST_F(AvlTreeSetFixture, TestFindNonExistentKey) {
    // 존재하지 않는 key 값을 사용하여 Find 호출
    auto result = avltree_set_.Find(100);  // 100은 트리에 존재하지 않는 값

    // 결과는 nullptr과 height + 0이어야 합니다.
    EXPECT_EQ(result.first, nullptr);  // 노드를 찾을 수 없으므로 nullptr 반환
    EXPECT_EQ(result.second, 0);       // 높이 + 깊이는 0이어야 함
}

// 존재하지 않는 key 값에 대한 Rank 함수 테스트
TEST_F(AvlTreeSetFixture, TestRankNonExistentKey) {
    // 존재하지 않는 key 값을 사용하여 Rank 호출
    auto result = avltree_set_.Rank(100);  // 100은 트리에 존재하지 않는 값

    // Rank는 0을 반환해야 합니다.
    EXPECT_EQ(result.first, 0);  // 존재하지 않으므로 rank는 0
    EXPECT_EQ(result.second, 0); // 존재하지 않으므로 rank는 0
}

// 존재하지 않는 key 값에 대한 Erase 함수 테스트
TEST_F(AvlTreeSetFixture, TestEraseNonExistentKey) {
    // 존재하지 않는 key 값을 사용하여 Erase 호출
    int result = avltree_set_.Erase(100);  // 100은 트리에 존재하지 않는 값

    // 삭제할 노드가 없으므로, 0 (삭제 실패)을 반환해야 합니다.
    EXPECT_EQ(result, 0);  // 삭제된 노드가 없으므로 0 반환
}

// 존재하지 않는 key 값에 대한 Ancestor 함수 테스트
TEST_F(AvlTreeSetFixture, TestAncestorNonExistentKey) {
    // 존재하지 않는 key 값을 사용하여 Ancestor 호출
    auto result = avltree_set_.Ancestor(100);  // 100은 트리에 존재하지 않는 값

    // 존재하지 않으면 (0, 0)을 반환해야 합니다.
    EXPECT_EQ(result.first, 0);  // 깊이는 0
    EXPECT_EQ(result.second, 0); // 키 값 합은 0
}

// 존재하지 않는 key 값에 대한 Average 함수 테스트
TEST_F(AvlTreeSetFixture, TestAverageNonExistentKey) {
    // 존재하지 않는 key 값을 사용하여 Average 호출
    int result = avltree_set_.Average(100);  // 100은 트리에 존재하지 않는 값

    // 존재하지 않으면 0을 반환해야 합니다.
    EXPECT_EQ(result, 0);  // 평균은 0이어야 함
}

// 14. Right-Heavy 상황에서 height 변경이 제대로 이루어졌는지 확인
TEST_F(AvlTreeSetFixture, TestHeightUpdate)
{
  /**
   * Right-Heavy 상황에서 height변경이 제대로 이루어졌는지 확인함
   */

  // 40 20 60 75 87 93
  avltree_set_.Insert(75);
  avltree_set_.Insert(87);
  avltree_set_.Insert(93);

  /**
   *    현재 상태
   * 
   *        75
   *       /  \
   *      40   87
   *     /  \   \
   *   20   60   93
   */

  int height;
  std::pair<Node<int>*, int> findNode;
  
  findNode = avltree_set_.Find(20);
  height = findNode.first->GetHeight();
  EXPECT_EQ(1, height);

  findNode = avltree_set_.Find(60);
  height = findNode.first->GetHeight();
  EXPECT_EQ(1, height);

  findNode = avltree_set_.Find(93);
  height = findNode.first->GetHeight();
  EXPECT_EQ(1, height);

  findNode = avltree_set_.Find(40);
  height = findNode.first->GetHeight();
  EXPECT_EQ(2, height);

  findNode = avltree_set_.Find(87);
  height = findNode.first->GetHeight();
  EXPECT_EQ(2, height);

  findNode = avltree_set_.Find(75);
  height = findNode.first->GetHeight();
  ASSERT_EQ(3, height);
}

// 15. Right-Heavy 상황에서 Rank 변경이 제대로 이루어졌는지 확인함
TEST_F(AvlTreeSetFixture, TestRankUpdate)
{
  /**
   * LeftRotation 상황에서 Rank변경이 제대로 이루어졌는지 확인함
   */

  // 40 20 60 75 87 93
  avltree_set_.Insert(75);
  avltree_set_.Insert(87);
  avltree_set_.Insert(93);

  /**
   *     현재 상태
   * 
   *        75
   *       /  \
   *      40  87
   *     /  \   \
   *   20   60   93
   */

  int rank;
  std::pair<int, int> rankNode;

  rankNode = avltree_set_.Rank(20);
  rank = rankNode.second;
  EXPECT_EQ(1, rank);
    
  rankNode = avltree_set_.Rank(40);
  rank = rankNode.second;
  EXPECT_EQ(2, rank);

  rankNode = avltree_set_.Rank(60);
  rank = rankNode.second;
  EXPECT_EQ(3, rank);

  rankNode = avltree_set_.Rank(75);
  rank = rankNode.second;
  EXPECT_EQ(4, rank);

  rankNode = avltree_set_.Rank(87);
  rank = rankNode.second;
  EXPECT_EQ(5, rank);

  rankNode = avltree_set_.Rank(93);
  rank = rankNode.second;
  ASSERT_EQ(6, rank);
}

// 16. LeftRotation 함수가 제대로 실행되는지 확인
// 20 40 50 60 75 82 87 순서대로 Find하면서 depth + 높이를 예측값과 비교
TEST_F(AvlTreeSetFixture, TestRightRightCase)
{
  /**
   * 50, 75, 82, 87을 key로 갖는 노드들을 추가 후, LeftRotation 함수가 제대로 실행되는지 확인
   * 20 40 50 60 75 87를 Find하면서 depth를 예측값과 비교
   */
  avltree_set_.Insert(50);
  avltree_set_.Insert(75);
  /**
   *   현재 상태
   * 
   *     40
   *    /  \
   *   20   60
   *       /  \
   *      50  75
   */

  avltree_set_.Insert(82);
  avltree_set_.Insert(87);
  /**
   *   로테이션 전          로테이션 후
   * 
   *     40                    60
   *    /  \                 /    \
   *   20   60              40     75
   *       /  \     ==>    /  \   /  \
   *      50  75          20  50 82  87
   *         /  \
   *        82  87
   */

  int sum;
  std::pair<Node<int>*, int> findNode;

  findNode = avltree_set_.Find(20);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(40);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(50);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(60);
  // 높이 3 + 깊이 0
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(75);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(82);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(87);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  ASSERT_EQ(3, sum);
}

// 17. RightRotation 함수가 제대로 실행되는지 확인
// 10 13 18 20 37 40 60 순서대로 Find하면서 높이 + depth를 예측값과 비교
TEST_F(AvlTreeSetFixture, TestLeftLeftCase)
{
  /**
   * 13, 37, 10, 18을 key로 갖는 노드들을 추가 후, RightRotation함수가 제대로 실행되는지 확인
   * 10 13 18 20 37 40 60를 Find하면서 높이 + depth를 예측값과 비교
   */
  avltree_set_.Insert(13);
  avltree_set_.Insert(37);
  /**
   *    현재 상태
   * 
   *       40
   *      /  \
   *     20   60
   *    /  \
   *   13  37
   */

  avltree_set_.Insert(10);
  avltree_set_.Insert(18);
  /**
   *     로테이션 전         로테이션 후
   * 
   *         40                 20
   *        /  \              /    \
   *       20   60           13     40
   *      /  \       ==>    /  \   /  \
   *     13  37           10   18 37  60
   *    /  \
   *   10  18
   */

  int sum;
  std::pair<Node<int>*, int> findNode;

  findNode = avltree_set_.Find(10);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(13);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(18);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(20);
  // 높이 3 + 깊이 0
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(37);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(40);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(60);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);
}

// 18. Left-Right Case에서 Rotation 함수들이 제대로 실행되는지 확인
// 17 20 25 37 39 40 60 70를 Find하면서 높이 + depth를 예측값과 비교
TEST_F(AvlTreeSetFixture, TestLeftRightCase)
{
  /**
   * 17, 37, 25, 39을 key로 갖는 노드들을 추가 후, Left-Right Case에서 Rotation 함수들이 제대로 실행되는지 확인
   * 17 20 25 37 39 40 60 70를 Find하면서 높이 + depth를 예측값과 비교
   */
  avltree_set_.Insert(17);
  avltree_set_.Insert(37);
  /**
   *    현재 상태
   * 
   *       40
   *      /  \
   *     20  60
   *    /  \
   *   17  37
   */

  avltree_set_.Insert(25);
  avltree_set_.Insert(39);
  /**
   *   로테이션 전         Left Rotation          최종 결과
   * 
   *       40                  40                   37
   *      /  \                /  \                /    \
   *     20  60              37  60             20      40
   *    /  \       ==>      /  \        ==>    /  \    /  \
   *   17  37              20  39             17  25  39  60
   *      /  \            /  \
   *     25  39          17  25
   */

  int sum;
  std::pair<Node<int>*, int> findNode;

  findNode = avltree_set_.Find(17);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(20);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(25);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(37);
  // 높이 3 + 깊이 0
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(39);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(40);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(60);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  ASSERT_EQ(3, sum);
}

// 19. 마찬가지로 Right-Left Case에서 Rotation 함수들이 제대로 실행되는지 확인
TEST_F(AvlTreeSetFixture, TestRightLeftCase)
{
    /**
   * 50, 75, 45, 55을 key로 갖는 노드들을 추가 후, LeftRotation 함수가 제대로 실행되는지 확인
   * 20 40 45 50 55 60 75를 Find하면서 depth를 예측값과 비교
   */
  avltree_set_.Insert(50);
  avltree_set_.Insert(75);
  /**
   *   현재 상태
   * 
   *     40
   *    /  \
   *   20   60
   *       /  \
   *      50  75
   */

  avltree_set_.Insert(45);
  avltree_set_.Insert(55);
  /**
   *   로테이션 전       Right Rotation         최종 결과
   * 
   *     40                40                     50
   *    /  \              /  \                  /    \
   *   20   60           20  50               40      60
   *       /  \    ==>      /  \      ==>    /  \    /  \
   *      50  75           45  60           20  45  55  75
   *     /  \                 /  \
   *    45  55               55  75
   */

  int sum;
  std::pair<Node<int>*, int> findNode;

  findNode = avltree_set_.Find(20);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(40);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(45);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(50);
  // 높이 3 + 깊이 0
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(55);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(60);
  // 높이 2 + 깊이 1
  sum = findNode.second;
  EXPECT_EQ(3, sum);

  findNode = avltree_set_.Find(75);
  // 높이 1 + 깊이 2
  sum = findNode.second;
  ASSERT_EQ(3, sum);
}


// main 함수는 Google Test가 제공하는 기본 메인 함수를 사용
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
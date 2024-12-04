#include "node.h" 
#include <gtest/gtest.h>

/**
 * Node 클래스의 기본 생성자를 테스트하는 테스트 케이스
 */
TEST(NodeTest, DefaultConstructor) {
  // 템플릿 인자로 int를 사용하여 Node 인스턴스 생성
  Node<int> node;

  // parent_ 포인터가 nullptr인지 확인
  EXPECT_EQ(node.parent_, nullptr);

  // left_ 포인터가 nullptr인지 확인
  EXPECT_EQ(node.left_, nullptr);

  // right_ 포인터가 nullptr인지 확인
  EXPECT_EQ(node.right_, nullptr);

  // key_가 기본값(0)인지 확인
  EXPECT_EQ(node.key_, 0);

  // height_가 1인지 확인
  EXPECT_EQ(node.height_, 1);

  // rank_가 1인지 확인
  EXPECT_EQ(node.rank_, 1);
}

/**
 * Node 클래스의 키 값으로 초기화하는 생성자를 테스트하는 테스트 케이스
 */
TEST(NodeTest, ParameterizedConstructor) {
  // 키 값을 10으로 설정하여 Node 인스턴스 생성
  Node<int> node(10);

  // parent_ 포인터가 nullptr인지 확인
  EXPECT_EQ(node.parent_, nullptr);

  // left_ 포인터가 nullptr인지 확인
  EXPECT_EQ(node.left_, nullptr);

  // right_ 포인터가 nullptr인지 확인
  EXPECT_EQ(node.right_, nullptr);
  
  // key_가 10인지 확인
  EXPECT_EQ(node.key_, 10);

  // height_가 1인지 확인
  EXPECT_EQ(node.height_, 1);

  // rank_가 1인지 확인
  EXPECT_EQ(node.rank_, 1);
}

// main 함수는 Google Test가 제공하는 기본 메인 함수를 사용
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
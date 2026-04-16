#include <gtest/gtest.h>
#include "avl_tree.hpp"
#include <random>

class AVLTest : public testing::Test {
  protected:
    AVLTest() {
      // leave t0 empty
    }

    AVLTree t0;
};

TEST_F(AVLTest, InsertWorks) {
  EXPECT_EQ(t0.getSize(), 0);
  t0.Insert(1);
  EXPECT_EQ(t0.getSize(), 1);
  t0.Insert(2);
  EXPECT_EQ(t0.getSize(), 2);
  t0.Insert(3);
  EXPECT_EQ(t0.getSize(), 3);

  int prevHeight = t0.getHeight(t0.searchNode(1));
  t0.Insert(1);
  t0.Insert(1);
  t0.Insert(1);
  t0.Insert(1);
  t0.Insert(1);
  t0.Insert(1);
  t0.Insert(1);
  EXPECT_EQ(t0.getSize(), 3);
  EXPECT_EQ(t0.getHeight(t0.searchNode(1)), prevHeight);
}

TEST_F(AVLTest, SearchWorks) {
  EXPECT_FALSE(t0.Search(12));
  t0.Insert(12);
  EXPECT_TRUE(t0.Search(12));
  t0.Insert(5);
  t0.Insert(2);
  t0.Insert(4);
  EXPECT_TRUE(t0.Search(5));
  EXPECT_TRUE(t0.Search(2));
  EXPECT_TRUE(t0.Search(4));
  EXPECT_FALSE(t0.Search(3));

  t0.Print();
  t0.Delete(5);
  t0.Print();
  EXPECT_FALSE(t0.Search(5));
  t0.Delete(2);
  EXPECT_FALSE(t0.Search(2));
  t0.Delete(4);
  EXPECT_FALSE(t0.Search(4));
}

TEST_F(AVLTest, InsertMaintainsProperties) {
  std::mt19937 gen(42); // Fixed seed for reproducibility
  std::uniform_int_distribution<> dis(-100, 100);

  for (size_t i = 0; i < 1000; ++i) {
    t0.Insert(dis(gen));
    EXPECT_TRUE(t0.isSorted());
    EXPECT_TRUE(t0.isBalanced());
  }
}

TEST_F(AVLTest, DeleteMaintainsProperties) {
  std::mt19937 gen(52); // Fixed seed for reproducibility
  std::uniform_int_distribution<> dis(-50, 50);

  for (size_t i = 0; i < 1000; ++i) {
    t0.Insert(dis(gen));
    EXPECT_TRUE(t0.isSorted());
    EXPECT_TRUE(t0.isBalanced());
  }
  for (size_t i = 0; i < 1000; ++i) {
    t0.Delete(dis(gen));
    EXPECT_TRUE(t0.isSorted());
    EXPECT_TRUE(t0.isBalanced());
  }
}

TEST_F(AVLTest, PrintsLevelOrder) { // add `-V` to `ctest` to check output
  t0.Insert(5);
  t0.Insert(3);
  t0.Insert(8);
  t0.Insert(2);
  t0.Insert(4);
  t0.Insert(7);
  t0.Insert(9);
  t0.Print();
}

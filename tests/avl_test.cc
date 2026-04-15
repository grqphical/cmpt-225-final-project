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
  t0.insert(1);
  EXPECT_EQ(t0.getSize(), 1);
  t0.insert(2);
  EXPECT_EQ(t0.getSize(), 2);
  t0.insert(3);
  EXPECT_EQ(t0.getSize(), 3);

  int prevHeight = t0.getHeight(t0.searchNode(1));
  t0.insert(1);
  t0.insert(1);
  t0.insert(1);
  t0.insert(1);
  t0.insert(1);
  t0.insert(1);
  t0.insert(1);
  EXPECT_EQ(t0.getSize(), 3);
  EXPECT_EQ(t0.getHeight(t0.searchNode(1)), prevHeight);
}

TEST_F(AVLTest, SearchWorks) {
  EXPECT_FALSE(t0.search(12));
  t0.insert(12);
  EXPECT_TRUE(t0.search(12));
  t0.insert(5);
  t0.insert(2);
  t0.insert(4);
  EXPECT_TRUE(t0.search(5));
  EXPECT_TRUE(t0.search(2));
  EXPECT_TRUE(t0.search(4));
  EXPECT_FALSE(t0.search(3));

  // TODO: Delete then search
}

TEST_F(AVLTest, InsertMaintainsProperties) {
  std::mt19937 gen(42); // Fixed seed for reproducibility
  std::uniform_int_distribution<> dis(-100, 100);

  for (size_t i = 0; i < 1000; ++i) {
    t0.insert(dis(gen));
    EXPECT_TRUE(t0.isSorted());
    EXPECT_TRUE(t0.isBalanced());
  }
}

// TODO: DeleteMaintainsProperties

TEST_F(AVLTest, PrintsLevelOrder) { // add `-V` to `ctest` to check output
  t0.insert(5);
  t0.insert(3);
  t0.insert(8);
  t0.insert(2);
  t0.insert(4);
  t0.insert(7);
  t0.insert(9);
  t0.printLevelOrder();
}

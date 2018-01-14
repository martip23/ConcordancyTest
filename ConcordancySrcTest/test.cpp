#include "pch.h"
#include"../ConcordancyTestSource/utils.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(UtilsTest, Comparisons) {
	ASSERT_EQ(false, galeCompare(3, 6, 5, 8));
	ASSERT_EQ(true, galeCompare(6, 3, 5, 8));
	ASSERT_EQ(false, galeCompare(3, 2, 1, 8));
	ASSERT_EQ(true, galeCompare(1, 2, 5, 25));
	ASSERT_EQ(false, galeCompare(7, 8, 8, 100));
	ASSERT_EQ(true, galeCompare(209, 102, 150, 300));
	ASSERT_EQ(false, galeCompare(151, 999, 152, 2000));
	ASSERT_EQ(true, galeCompare(9001, 9002, 9000, 25000));
	ASSERT_EQ(false, galeCompare(625, 333, 1, 1000));
	ASSERT_EQ(true, galeCompare(852, 6541, 7000, 12000));
}
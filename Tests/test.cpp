#include "pch.h"
#include <vector>
#include"../Concordancy/utils.h"
using namespace std;

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

TEST(InverseTest, ReturnInverse) {
	vector<int> p = { 3,1,6,5,4,2 };
	vector<int> ip = { 2,6,1,5,4,3 };
	ASSERT_EQ(ip, inverse(p, 6));
	ASSERT_EQ(p, inverse(inverse(p, 6),6));
	p = { 3,8,5,10,9,4,6,1,7,2 };
	ip = { 8,10,1,6,3,7,9,2,5,4 };
	ASSERT_EQ(ip, inverse(p, 10));
	ASSERT_EQ(p, inverse(ip, 10));
	ASSERT_EQ(p, inverse(inverse(p, 10), 10));
}

TEST(GrassmannNecklaceTest, PermutationToGM) {
	vector<vector<int>> gm = { {1,2,4},{2,3,4},{3,4,1},{4,6,1},{5,6,1},{6,1,4} };
	vector<int> perm = { 3,1,6,5,4,2 };
	ASSERT_EQ(gm, grassmannNecklace(perm));
	perm = { 3,6,8,1,4,7,2,5 };
	gm = { {1,2,4,5},{2,3,4,5},{3,4,5,6},{4,5,6,8},
		{5,6,8,1},{6,8,1,4},{7,8,1,4},{8,1,2,4} };
	ASSERT_EQ(gm, grassmannNecklace(perm));
	perm = { 2,3,1,5,4 };
	gm = { {1,4},{2,4},{3,4},{4,1},{5,1} };
	ASSERT_EQ(gm, grassmannNecklace(perm));
}
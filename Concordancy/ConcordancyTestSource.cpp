// ConcordancyTestSource.cpp : Defines the entry point for the console application.
/*
	By: Patrick Martinez
	ConcordancyTestSource.
	This holds all of the utilities and code needed to check concordancy of two bases of 
	all subsets of a given Matroid.
*/

#include "stdafx.h"
#include "utils.h"
#include <iostream>
using namespace std;

int main()
{
	//vector<int> permutation = { 11, 18, 5, 16, 8, 4, 12, 20, 7, 1, 13, 6, 14, 2, 17, 9, 19, 3, 15, \
	//	10 };
	//findBases(grassmannNecklace(permutation));
 //   return 0;

	vector<vector<int>> bases = {
	{ 1, 2, 5, 6 },{ 1, 2, 5, 7 },{ 1, 2, 5, 8 },{ 1, 3, 4, 5 },
	{ 1, 3, 4, 6 },{ 1, 3, 4, 7 },{ 1, 3, 4, 8 },{ 1, 3, 5, 6 },
	{ 1, 3, 5, 7 },{ 1, 3, 5, 8 },{ 1, 4, 5, 6 },{ 1, 4, 5, 7 },
	{ 1, 4, 5, 8 },{ 1, 4, 6, 8 },{ 1, 4, 7, 8 },{ 1, 5, 6, 8 },
	{ 1, 5, 7, 8 },{ 2, 3, 4, 5 },{ 2, 3, 4, 6 },{ 2, 3, 4, 7 },
	{ 2, 3, 4, 8 },{ 2, 3, 5, 6 },{ 2, 3, 5, 7 },{ 2, 3, 5, 8 },
	{ 2, 4, 5, 6 },{ 2, 4, 5, 7 },{ 2, 4, 5, 8 },{ 2, 4, 6, 8 },
	{ 2, 4, 7, 8 },{ 2, 5, 6, 8 },{ 2, 5, 7, 8 },{ 3, 4, 5, 6 },
	{ 3, 4, 5, 7 },{ 3, 4, 5, 8 },{ 3, 4, 6, 8 },{ 3, 4, 7, 8 },
	{ 3, 5, 6, 8 },{ 3, 5, 7, 8 },{ 4, 5, 6, 8 },{ 4, 5, 7, 8 } };
	vector<int> base = { 5,6,7 };
	rankFind(base, bases);
}
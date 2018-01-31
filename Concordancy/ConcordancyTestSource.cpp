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
	vector<int> permutation = { 4,1,2,3 };
	vector<vector<int>> bases = findBases(grassmannNecklace(permutation));
	vector<vector<int>> flats = {
		{ 1 },{ 2 },{ 3 },{ 4 },{ 1,2 },{ 1,3 },{ 1,4 },
	{ 2,3 },{ 2,4 },{ 3,4 },{ 1,2,3,4 } };
	findFlats(bases, 4);
}
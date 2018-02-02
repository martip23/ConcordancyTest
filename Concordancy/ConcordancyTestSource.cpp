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

int main() {	
	string permutationString = "";
	cout << "Perm1:";
	getline(cin, permutationString);
	
	vector<vector<int>> bases =
	findBases(grassmannNecklace({ 11,18,5,16,8,4,12,20,7,1,13,6,14,2,17,9,19,3,15,10 }));

	
	return 0;
}
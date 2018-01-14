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
	cout << galeCompare(3, 6, 5, 8) << endl;
	cin.get();
    return 0;
}
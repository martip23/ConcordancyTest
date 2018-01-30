#pragma once

#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
using namespace std;

// Utilities for concordancy test

// Custom mod function since % is only "division remainder"
int mod(int a, int b) {
	return (a%b + b) % b;
}

// Does a Gale Comparison of two sets of numbers on a different cyclical order
// Returns true if a <i b.
// a: First value
// b: Second value
// i: "first" digit
// n: ground set
// ALL INTS MUST BE POSITIVE INTEGERS
bool galeCompare(int a, int b, int i, int n) {
	return mod(a - i, n) < mod(b - i, n);
}


// Returns the inverse of a vector assuming it is a valid permutation
vector<int> inverse(const vector<int> permutation, const int length) {
	vector<int> inverse;
	for (int i = 1; i <= length; i++) {
			for (int j = 1; j <= length; j++) {
				if (i == permutation[j-1]) {
					inverse.push_back(j);
					break;
			}
		}
	}
	return inverse;
}

// Computes the grassmann necklace of a derangement and gives each element
// ordered under i. Done by removing k-1 and replacing with item at index k-1
// permutation: The permutation to build a grassmann necklace out of
vector<vector<int>> grassmannNecklace(const vector<int> permutation) {
	int length = permutation.size();
	vector<vector<int>> grassmann;

	// Make initial grassmann bead
	// Using set to add in order using BST
	set<int> tempSet;
	for (int i = 1; i <= length; i++) {
		if (i >= permutation[i - 1]) {
			tempSet.insert(permutation[i - 1]);
		}
	}
	vector<int> prevVect(tempSet.begin(), tempSet.end());
	grassmann.push_back(prevVect);

	// Remove element of last i and replace it with element at perm[i]
	for (int i = 2; i <= length; i++) {
		replace(prevVect.begin(), prevVect.end(), (i - 1), permutation[i - 2]);
		sort(prevVect.begin(), prevVect.end(), [i, length](int a, int b) {
			return galeCompare(a, b, i, length); });
		grassmann.push_back(prevVect);
	}
	return grassmann;
}

// Finds all subsets of size n from a permutation size k
vector<vector<int>> subsetsOfSizeN(int n, int k) {
	vector<vector<int>> subsets;

	string bitmask(k, 1); // K leading 1's
	bitmask.resize(n, 0); // N-K trailing 0's
	int timesIterated = 0;
						  // print integers and permute bitmask
	do {
		subsets.push_back({});
		for (int i = 0; i < n; ++i) // [0..N-1] integers
		{
			if (bitmask[i]) {
				subsets[timesIterated].push_back(i+1);
			}
		}
		timesIterated++;
	} while (prev_permutation(bitmask.begin(), bitmask.end()));
	
	return subsets;
}

// Finds all of the bases of a specific grassman necklace.
vector<vector<int>> findBases(const vector<vector<int>> grassmann) {
	vector<vector<int>> bases;
	int gmLength = grassmann.size(); // grassmann length
	int beadSize = grassmann[0].size();
	vector<vector<int>> subsets = subsetsOfSizeN(gmLength, beadSize);

	// Grab a subset
	for (int i = 1; i <= subsets.size(); i++) {
		bool good = true;

		// Grab a bead
		for (int j = 1; j <= gmLength; j++) {
			sort(subsets[i-1].begin(), subsets[i-1].end(), [j, gmLength](int a, int b) {
				return galeCompare(a, b, j, gmLength); });

			// Compare subset digit with bead digit
			for (int k = 1; k <= beadSize; k++) {
				if (galeCompare(subsets[i - 1][k - 1],
					grassmann[j - 1][k - 1], j, gmLength)) {
					good = false;
					break;
				}
			}
			if (!good) { break; }
		}
		if (good) {
			sort(subsets[i-1].begin(), subsets[i-1].end(), [](int a, int b) {
				return a < b; });
			bases.push_back(subsets[i-1]);
		}
	}
	return bases;
}

// Checks rank of base against bases
int rankFind(vector<int> base, vector<vector<int>> bases) {
	int baseRank = 0;
	int maxRank = 0;
	int basesListSize = bases.size();
	int baseSize = base.size();
	int basesListElementSize = bases[0].size();

	// Each base
	for (int i = 0; i < basesListSize; i++) {
		baseRank = 0;
		// For each digit in base
		for (int j = 0; j < baseSize; j++) {
			// For each digit in selected base
			for (int k = 0; k < basesListElementSize; k++) {
				if (base[j] == bases[i][k]) {
					baseRank++;
					break;
				}
				else if (base[j] < bases[i][k])
					break;
			}
		}
		if (baseRank == baseSize || baseRank == basesListElementSize)
			return baseRank;
		if (baseRank > maxRank)
			maxRank = baseRank;
	}
	return maxRank;
}

// Checks if the flat is actually a flat.
// n is the size of the permutation
bool isAFlat(vector<int> base, const vector<vector<int>> bases, int n) {
	int baseRank = rankFind(base, bases);
	int baseSize = base.size();
	int basesSize = bases[0].size();
	if (basesSize == baseRank) return true;

	for (int i = 0; i < n; i++) {
		bool breakLoop = false;

		// Break loop (don't do check) if i is already in base
		for (int j = 0; j < baseSize; j++) {
			if (i + 1 == base[j]) {
				breakLoop = true;
				break;
			}
		}
		if (breakLoop) continue;

		int newRank;
		base.push_back(i + 1);
		newRank = rankFind(base, bases);
		base.pop_back();
		if (newRank > baseRank) { }
		else {
			return false;
		}
	}
	return true;
}

/*
	Finds and creates a list of all the flats of a set of bases.
	@bases - the bases of a permutation
	@n - size of permutation [n]
	*/
vector<vector<int>> findFlats(const vector<vector<int>> bases, int n) {
	vector<vector<int>> flatsSet;
	for (int i = 0; i < n; i++) {
		vector<vector<int>> tempFlatsSet;
		tempFlatsSet = subsetsOfSizeN(i + 1, n);
		flatsSet.insert(flatsSet.end, tempFlatsSet.begin, tempFlatsSet.end);
	}

	for (int i = 0; i < flatsSet.size(); i++) {
		if (isAFlat(flatsSet[i], bases, n)) {}
		else {
			flatsSet.erase(i);
		}
	}
	return flatsSet;
}

/*
		Checks whether 2 sets of bases are concordant. Concordant means that
		all flats of base1 are also flats of base2
		@bases1 - First set of bases
		@bases2 - Second set of bases
		@n - size of permutation [n]
*/
bool isConcordant(const vector<vector<int>> bases1,
	const vector<vector<int>> base2, int n) {

}
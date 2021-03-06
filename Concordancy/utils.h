#pragma once

#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

/* Set of utilities to be used with matroids. Includes gale ordering greater
	than function, modular arithmetic, inverse permutation, grassmann Necklace,
	finds subsets of a certain size of a value, all bases pertaining to a 
	grassmann necklace, ranks of subsets in a permutation, checks if a subset
	is a flat of a permutation, a fucntion to find all flats of a permutation
	and a function to check if two permutations are concordant.

*/

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
int rankFind(const vector<int> base, const vector<vector<int>> bases) {
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
	if (basesSize == n) return true;

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
		if (newRank <= baseRank) {
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
	int baseSize = bases[0].size();

	// Add subsets of baseSize - 1
	for (int i = 1; i < baseSize; i++) {
		vector<vector<int>> tempFlatsSet;
		tempFlatsSet = subsetsOfSizeN(n, i);
		flatsSet.insert(flatsSet.end(), tempFlatsSet.begin(), tempFlatsSet.end());
	}

	// Prune subsets that are not flats
	for (int i = 0; i < flatsSet.size(); i++) {
		if (isAFlat(flatsSet[i], bases, n)) {}
		else {
			flatsSet.erase(flatsSet.begin() + i);
		}
	}

	vector<int> tempVect;
	// Push biggest rank
	for (int i = 1; i <= n; i++) {
		tempVect.push_back(i);
	}
	flatsSet.push_back(tempVect);

	return flatsSet;
}

/*
		Checks whether 2 sets of bases are concordant. Concordant means that
		all flats of base1 are also flats of base2
		@bases1 - Smaller flats
		@bases2 - Bigger flats
*/
bool isConcordant(const vector<vector<int>> smFlats,
	const vector<vector<int>> lgFlats) {
	const int smSize = smFlats.size();
	const int lgSize = lgFlats.size();

	// Get each small flat
	for (int i = 0; i < smSize; i++) {
		bool found = false;
		// Get each flat in the same index or higher (matching flats will never
		// be at indexes below i
		for (int j = i; j < lgSize; j++) {
			if (smFlats[i] == lgFlats[j]) {
				found = true;
				break;
			}
		}
		if (found == false) {
			return false;
		}
	}
	return true;
}

/*
	Checks whether two permutations are concordant.
	@perm1 - Smaller permutation
	@perm2 - Larger permutation
*/
bool isConcordant(const vector<int> perm1, const vector<int> perm2) {
	return isConcordant(
		findFlats(findBases(grassmannNecklace(perm1)), perm1.size()) ,
		findFlats(findBases(grassmannNecklace(perm2)), perm2.size()));
}
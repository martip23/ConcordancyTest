#pragma once

// Utilities for concordancy test


// Custom mod function since % is only "division remainder"
int mod(int a, int b) {
	{return (a%b + b) % b; }
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


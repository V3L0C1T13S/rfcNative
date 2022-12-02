#include "util.h"
#include <algorithm>
#include <string>

int getEditDistance(std::string first, std::string second)
{
	int m = first.length();
	int n = second.length();

	int T[m + 1][n + 1];
	for (int i = 1; i <= m; i++) {
		T[i][0] = i;
	}

	for (int j = 1; j <= n; j++) {
		T[0][j] = j;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			int weight = first[i - 1] == second[j - 1] ? 0: 1;
			T[i][j] = std::min(std::min(T[i-1][j] + 1, T[i][j-1] + 1), T[i-1][j-1] + weight);
		}
	}

	return T[m][n];
}

double findStringSimilarity(std::string first, std::string second) {
	double max_length = std::max(first.length(), second.length());
	if (max_length > 0) {
		return (max_length - getEditDistance(first, second)) / max_length;
	}
	return 1.0;
}

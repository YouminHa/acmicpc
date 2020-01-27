#include <stdio.h>
#include <iostream>
using namespace std;

#define DEBUG 1

#ifdef DEBUG
#define LOG(s, ...) do { printf(s"\n", __VA_ARGS__); } while (0);
#else
#define LOG(s, ...)
#endif

#define MAX_SIZE 301
#define NA -1

int dp[MAX_SIZE][MAX_SIZE] = {0,};

void init(int n, int m) {
	for (int i=0; i<=n; ++i) {
		for (int j=0; j<=m; ++j) {
			dp[i][j] = NA;
		}
	}
}

int val(int a, int b) {
	if (a == 0 || b == 0) return 0;

	// dp table
	if (dp[a][b] != NA) return dp[a][b];

	int c = NA;
	// 1*1 : no cut
	if (a == 1 && b == 1) {
		c = 0;
		goto RETURN;
	}

	// else, get min value from possible cuts, and add 1
	c = a*b;	// possible max

	int v;
	// test horizontal cut
	for (int i=1; i < a; ++i) {
		v = val(i, b) + val(a-i, b) + 1;
		if (v < c) c = v;
	}
	// test vertical cut
	for (int i=1; i < b; ++i) {
		v = val(a, i) + val(a, b-i) + 1;
		if (v < c) c = v;
	}

RETURN:
	LOG("(%d, %d) = %d", a, b, c);
	dp[a][b] = c;
	dp[b][a] = c;
	return c;
}

int solve(int N, int M) {
	for (int i=1; i<=N; ++i) {
		for (int j=1; j<=M; ++j) {
			val(i, j);
		}
	}
	return val(N, M);
}


int main() {
	int n, m;
	cin >> n >> m;
	init(n, m);
	cout << solve(n, m) << endl;
	return 0;
}


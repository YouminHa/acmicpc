#include <iostream>
using namespace std;
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX_N 1000

// Not Decided Yet
#define NDY -1

int N;
int d[MAX_N+1][3];
int sum[MAX_N+1][3];

void
read() {
	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> d[i][0] >> d[i][1] >> d[i][2];

		for (int j=0; j<3; j++) {
			sum[i][j] = NDY;
		}
	}
}

inline int
min(int a, int b) {
	if (a == NDY) return b;
	if (b == NDY) return a;
	return MIN(a, b);
}

void
solve() {
	for (int i=0; i<N; i++) {
		for (int j=0; j<3; j++) {
			// 1st line
			if (i == 0) {
				sum[i][j] = d[i][j];	
			}
			// all lines
			else {
				for (int k=0; k<3; k++) {
					sum[i][j] = min(sum[i][j], sum[i-1][(j+1)%3] + d[i][j]);
					sum[i][j] = min(sum[i][j], sum[i-1][(j+2)%3] + d[i][j]);
				}
			}
		}
	}

	int min_sum = NDY;
	for (int i=0; i<3; i++) {
		min_sum = min(min_sum, sum[N-1][i]);
	}
	cout << min_sum << endl;
}

int main() {
	read();
	solve();
	return 0;
}

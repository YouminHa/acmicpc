#define DEBUG 1

#include "../util.h"
#include <iostream>
using namespace std;

#define MAX_N 251

// NOTE: 합계가 너무 커서 long long 으로 처리할 수 있는 수를 넘는다.
// java 의 BigInteger 클래스 같은 큰 수 출력용 자료구조를 만들어서 처리해야 함.
unsigned long long c[MAX_N] = {0,};

unsigned long long solve(int n) {
	for (int i=0; i<=n; i++) {
		if (i == 0) c[i] = 1;	// no box : 1 case
		else {
			if (i == 1) c[i] = 1;
			else if (i == 2) c[i] = 3;	// 3 cases
			else {
				if (c[i] == 0) {	// calculate only empty count
					c[i] = c[i-2] * 2 + c[i-1]; // exclude duplicated case
				}
			}
		}
	}
	return c[n];
}


int main() {
	int N;
	while (cin >> N) {
		cout << solve(N) << endl;
	}
}

#include <iostream>
using namespace std;

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))

#define MAX_N 100001


int sticker[2][MAX_N];
int dp[2][MAX_N];

int N, T;


void read() {
        cin >> N;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> sticker[i][j];
                dp[i][j] = 0;
            }
        }
}

void solve() {
    // dp[a][b] = a,b 위치 스티커를 뗄 때, 가능한 최대값의 합
    for (int i = 0; i < N; ++i) {
        if (0 == i) {
            dp[0][i] = sticker[0][i];
            dp[1][i] = sticker[1][i];
        }
        else if (1 == i) {
            dp[0][i] = dp[1][i - 1] + sticker[0][i];
            dp[1][i] = dp[0][i - 1] + sticker[1][i];
        }
        else {
            for (int j = 0; j < 2; ++j) {
                int inv_j = (j + 1) % 2;
                int before_2_max = max(dp[j][i - 2], dp[inv_j][i - 2]);
                dp[j][i] = max(dp[inv_j][i - 1], before_2_max) + sticker[j][i];
            }
        }
    }
    cout << max(dp[0][N - 2], max(dp[1][N - 2], max(dp[0][N - 1], dp[1][N - 1]))) << endl;
}

int main() {
    cin >> T;
    for (int t = 0; t < T; ++t) {
        read();
        solve();
    }
    return 0;
}


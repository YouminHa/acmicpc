#include <iostream>
using namespace std;

#define MAX_K 10
#define MAX_DIAGONAL (2*MAX_K - 1)

int K;          // board size
int nDiagonal;  // # of diagonals;
int board[MAX_K][MAX_K];
int maxB;       // Current max # of bishops
int d_l2r[MAX_DIAGONAL];

void init() {
  // read data
  cin >> K;
  for (int i=0; i<K; i++) {
    for (int j=0; j<K; j++) {
      cin >> board[i][j];
    }
  }

  // set initial values
  maxB = 0;
  nDiagonal = 2*K - 1;
  for (int i=0; i<nDiagonal; i++) {
    d_l2r[i] = 0;
  }
}


void dfs(int count, int d) {
  // count: current bishop count
  // d: current r2l diagonal number

  // Prunning phase

  // 1) If current count + expected max bishops (= # of remained diagonals)
  //    are not bigger than current max. bishops, prune it.
  if (count + (nDiagonal - d) <= maxB) return;

  // 2) When the search is finished, end search
  if (d >= nDiagonal) {
    if (count > maxB) maxB = count; // replace maxB if better count is found
    return;
  }

  // Tree expansion phase

  // Start r2l diagonal search from 1st position.
  // 1) Get the 1st x, y position of each diagonal
  // NOTE: r2l diagonal idx
  //      0  1      2
  //    +---------+
  //    | 1  1  0 |
  //    | 0  0  0 | 3
  //    | 0  1  1 | 4
  //    +---------+
  int x, y;
  if (d < K) {    // 0 ~ K-1
    x = d;
    y = 0;
  }
  else {        // K ~ (nDiagonal-1)
    x = K - 1;
    y = d - K + 1;
  }

  // 2) Search each diagonal
  while (0 <= x && x < K &&
         0 <= y && y < K) {
    if (board[y][x] == 1) { // Find available place
      int idx_l2r = x - y + K - 1;
      // NOTE: l2r diagonal idx
      //  2      3  4
      //    +---------+
      //    | 1  1  0 |
      //  1 | 0  0  0 |
      //  0 | 0  1  1 |
      //    +---------+
      if (d_l2r[idx_l2r] == 0) {    // No l2r diagonal is checked
        // New bishop can be put here! Seach more.
        d_l2r[idx_l2r] = 1;   // Set l2r diagonal
        dfs(count+1, d+1);    // Search next r2l diagonal
        d_l2r[idx_l2r] = 0;   // Unset l2r diagonal
      }
    }

    // move to next place
    x--; y++;
  }

  // Check the case when the current r2l diagonal is not used
  dfs(count, d+1);
}


void
solve() {
  dfs(0, 0);
  cout << maxB << endl;
}


int main(int argc, char* argv[]) {
  init();
  solve();
  return 0;
}

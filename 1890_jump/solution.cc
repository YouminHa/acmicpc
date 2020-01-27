#include <stdio.h>

int n;
int map[100][100];

void read() {
  scanf("%d", &n);
  int v;

  for (int r=0; r < n; ++r) {
    for (int c=0; c < n; ++c) {
      scanf("%d", &v);
      map[r][c] = v;

      //printf("%d ", map[r][c]);
    }
    //printf("\n");
  }
}

unsigned long n_ways[100 * 100];

void solve() {
  // init n_ways
  for (int r = n-1; r >= 0; --r) {
    for (int c = n-1; c >= 0; --c) {
      n_ways[r * n + c] = 0;
    }
  }

  // DP: remember # of ways to bottom right
  for (int r = n-1; r >= 0; --r) {
    for (int c = n-1; c >= 0; --c) {
      // bottom right
      if (r == n-1 && c == n-1) {
        n_ways[r * n + c] = 1;
        continue; 
      }

      auto k = map[r][c];
      // avoid 0 (no way to jump)
      if (k == 0) continue;

      // see right
      if (c + k <= n - 1) {
        n_ways[r * n + c] += n_ways[r * n + (c + k)];
      }

      // see down
      if (r + k <= n - 1) {
        n_ways[r * n + c] += n_ways[(r + k) * n + c];
      }
    }
  }
  
  // return 0 * 0 value
  printf("%ld\n", n_ways[0]);
}

int main(int argc, char* argv[]) {
  read();
  solve();
  return 0;
}

#include <iostream>
using namespace std;

#ifdef DEBUG
#define LOG(s) cerr << s << endl
#define LOG_NONL(s) cerr << s
#else
#define LOG(s);
#define LOG_NONL(s);
#endif

#define MAX_SIZE 100

int map[MAX_SIZE][MAX_SIZE];
int N, M;
int min_count;

int queue[MAX_SIZE*MAX_SIZE][3];
int queue_head, queue_tail, queue_size;

void queue_init() {
  queue_head = 0;
  queue_tail = 0;
  queue_size = N*M;
}

void queue_push(int x, int y, int count) {
  //int val = x + (y * M);

  queue[queue_head][0] = x;
  queue[queue_head][1] = y;
  queue[queue_head][2] = count;

  queue_head = (queue_head+1)%queue_size;
}

int queue_pop(int* x, int* y, int* count) {
  if (queue_tail == queue_head) return 0;

  *x = queue[queue_tail][0];
  *y = queue[queue_tail][1];
  *count  = queue[queue_tail][2];
  //*y = val / M;
  //*x = val % M;

  queue_tail = (queue_tail+1)%queue_size;

  return 1;
}


void read() {
  cin >> N >> M;
  char c;
  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      cin >> c;
      map[i][j] = c - '0';
    }
  }
}

int dfs(int x, int y, int count) {
  // Prunning

  // possible path check
  if (map[y][x] != 1) {
    LOG( "not a way: "<< x << "," << y << " = " << map[y][x] );
    return count;
  }

  // bound check
  if (x < 0 || y < 0 || x >= M || y >= N) {
    LOG("out of the bound: " << x << "," << y);
    return count;
  }

  // min_count check
  if (count >= min_count) return count;

  // possible best remained path check 
  int possible_best_count = count + (M-1-x)+(N-1-y);
  if (possible_best_count >= min_count) return count;

  // Possible path: add a count
  count++;
  map[y][x] = 2;
  
  // finish check
  if (x == M-1 && y == N-1) {
    if (min_count > count) {
      min_count = count;
    }
    return count;
  }

  // next path
  dfs(x-1, y, count);
  dfs(x+1, y, count);
  dfs(x, y-1, count);
  dfs(x, y+1, count);

  // restore map
  map[y][x] = 1;

  return count;
}


int bfs(int x, int y, int count) {
  LOG_NONL( "bfs(" << x << "," << y  << "," << count << ") ---- " );

  // Prunning

  // bound check
  if (x < 0 || y < 0 || x >= M || y >= N) {
    LOG("out of the bound: " << x << "," << y );
    return count;
  }

  // possible path check
  if (map[y][x] != 1) {
    LOG("not a way: "<< x << "," << y << " = " << map[y][x] );
    return count;
  }

  // min_count check
  if (count >= min_count) return count;

  // possible best remained path check 
  int possible_best_count = count + (M-1-x)+(N-1-y);
  if (possible_best_count >= min_count) return count;

  //LOG( "bfs: "<< x << "," << y << " = " << map[y][x] << ", count=" << count );

  // Possible path: add a count
  count++;
  map[y][x] = 2;

  // finish check
  if (x == M-1 && y == N-1) {
    if (min_count > count) {
      min_count = count;
    }
    LOG( "GOAL: "<< x << "," << y << " = " << map[y][x] << ", count=" << count );

    return count;
  }

  queue_push(x-1, y, count);
  queue_push(x+1, y, count);
  queue_push(x, y-1, count);
  queue_push(x, y+1, count);

  int _x, _y, _count;
  while (queue_pop(&_x, &_y, &_count)) {
    bfs(_x, _y, _count);
  }

  // restore map
  map[y][x] = 1;

  return count;
}


void solution() {
  min_count = N*M;
  queue_init();

  bfs(0, 0, 0);
  cout << min_count << endl;
}


int main(int argc, char** argv) {
  read();
  solution();
  return 0;
}


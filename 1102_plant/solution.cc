
#include <iostream>
using namespace std;

//#define DEBUG 1

#ifdef DEBUG
#define LOG(s) std::cerr << s << std::endl
#else
#define LOG(s)
#endif

#define MAX_N_PLANT 16
#define MAX_DPTABLE 65537   // 2^16+1
#define NOT_CALCULATED (-1)

int cost[MAX_N_PLANT][MAX_N_PLANT];
int state[MAX_N_PLANT];

int nPlant;
int minWorkingPlant;
int workingPlant;
int initialKey = 0;

// Stores the cost of k-th turning-on cost of i-th plant in dptable[k][i]
// All running plants have cost 0 (already turnned on)
int dptable[MAX_DPTABLE] = {NOT_CALCULATED, }; // bit-mask key


int
makeKey(int prevKey, int plantIdx) {
  return prevKey | (0x01 << plantIdx);
}

int
nPlantFromKey(int key) {
  int c = 0;
  int b;
  for (int i=0; i<nPlant; i++) {
    b = 0x01 << i;
    if (b & key) c++;
  }
  return c;
}


int
pow(int base, int mul) {
  if (mul == 0) return 1;
  int v = base;
  for (int i=1; i<mul; i++) {
    v *= base;
  }
  return v;
}


void
read() {
  // read data
  cin >> nPlant;
  for (int i=0; i<nPlant; i++) {
    for (int j=0; j<nPlant; j++) {
      cin >> cost[i][j];
    }
  }
  char c;
  initialKey = 0;
  for (int i=0; i<nPlant; i++) {
    cin >> c;
    if (c == 'Y') {
      state[i] = 1;
      workingPlant++;
      initialKey = makeKey(initialKey, i);
    } else {
      state[i] = 0;
    }
  }
  cin >> minWorkingPlant;

  // init dptable
  for (int i=0; i<MAX_DPTABLE; i++) {
    dptable[i] = NOT_CALCULATED;
  }
  LOG("initial key=" << initialKey);
  dptable[initialKey] = 0;  // they are already on; cost=0
}

int
dp() {
  LOG("nPlant=" << nPlant);
  int maxKey = pow(2, nPlant);
  int keys[nPlant];
  unsigned int prevKey;
  int c;

  int minCost = NOT_CALCULATED;


  // search all key
  for (int k = 0; k < maxKey; k++) {
    c = NOT_CALCULATED;

    // i is the index of the plant which is to be on.
    for (int i=0; i<nPlant; i++) {
      // create prev. keys
      prevKey = k & ~(0x01 << i);

      LOG("k=" << k << ", prevKey=" << prevKey);

      if (k == prevKey) continue; // skip same key
      LOG("prev key value: dptable[" << prevKey << "]=" << dptable[prevKey]);
      if (dptable[prevKey] == NOT_CALCULATED) continue;   // skip if the prevKey is invalid

      for (int j=0; j<nPlant; j++) {
        int isRunningPlant = prevKey & (0x01 << j);
        if (isRunningPlant) {
          int newCost = dptable[prevKey] + cost[j][i];
          LOG("newCost("<< j << "," << i << ") = " << newCost );
          if (c == NOT_CALCULATED) c = newCost;
          else c = min(c, newCost);
        }
      }
    }

    if (c != NOT_CALCULATED) dptable[k] = c;


    if (nPlantFromKey(k) >= minWorkingPlant) {
      if (minCost == NOT_CALCULATED) minCost = dptable[k];
      else if (dptable[k] != NOT_CALCULATED) minCost = min(minCost, dptable[k]);
      LOG("minCost=" << minCost << " on key " << k);
    }
  }

  // get an answer
  return minCost;
}


int
main(int argc, char** argv) {
  read();
  cout << dp() << endl;
}

#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

int n;
ll C[20][20];

ll solve(int s = 0, int x = n) {
  if (C[s][x]) return C[s][x];
  if (x == 0) return 1;
  if (s > 0) C[s][x] += solve(s - 1, x);
  C[s][x] += solve(s + 1, x - 1);
  return C[s][x];
}

int main() {
  cin >> n;
  cout << solve() << endl;
  return 0;
}

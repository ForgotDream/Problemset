#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int n;
int _2[] = {1,   2,   4,    8,    16,   32,   64,   128,
            256, 512, 1024, 2048, 4096, 8192, 16384};

void solve(int num = n) {
  if (num == 0) return;
  if (num == 1) {
    cout << "2(0)";
    return;
  }
  if (num == 2) {
    cout << 2;
    return;
  }
  int k = lower_bound(_2, _2 + 15, num) - _2;
  if(_2[k]!=num) k--;
  if (k == 1)
    cout << 2;
  else {
    cout << "2(";
    solve(k);
    cout << ")";
  }
  if (_2[k] != num) {
    cout << "+";
    solve(num - _2[k]);
  }
  return;
}

int main() {
  cin >> n;
  solve();
  return 0;
}
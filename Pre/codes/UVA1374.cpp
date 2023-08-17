#include <cstring>
#include <iostream>

using namespace std;

int n, maxd;
int s[100];

bool solve(int d = 0, int sum = 1) {
  if (d > maxd || sum <= 0 || sum << (maxd - d) < n) return false;
  if (sum == n || sum << (maxd - d) == n) return true;
  s[d] = sum;
  // bool flag = false;
  for (int i = 0; i <= d; i++) {
    if (solve(d + 1, sum + s[i])) return true;
    if (solve(d + 1, sum - s[i])) return true;
  }
  return false;
}

int main() {
  while (cin >> n && n != 0) {
    for (maxd = 0;; maxd++) {
      if (solve()) {
        break;
      };
    }
    cout << maxd << endl;
  }
  return 0;
}
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int n, ans = -1;
int a[(int)1e5 + 50];
int f[32];

void solve() {
  for (int i = 1; i <= n; i++) {
    int tmp = -1;
    for (int j = 0; j <= 31; j++)
      if ((1 << j) & a[i]) tmp = max(f[j] + 1, tmp);
    for (int j = 0; j <= 31; j++)
      if ((1 << j) & a[i]) f[j] = max(f[j], tmp);
    ans = max(ans, tmp);
  }
  cout << ans << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  solve();
  return 0;
}
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int t, n, ans;
int a[105];
int f[25005];

inline int read() {
  int x = 0, t = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') t = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * t;
}

void solve() {
  int maxn = -1;
  for (int i = 1; i <= n; i++) maxn = max(maxn, a[i]);
  f[0] = 1;
  for (int j = 1; j <= n; j++)
    for (int k = a[j]; k <= maxn; k++) f[k] = f[k] + f[k - a[j]];
  for (int i = 1; i <= n; i++)
    if (f[a[i]] == 1) ans++;
  cout << ans << endl;
  ans = 0, memset(f, 0, sizeof(f));
  return;
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(0), cout.tie(0);
  t = read();
  while (t--) {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    solve();
  }
  return 0;
}
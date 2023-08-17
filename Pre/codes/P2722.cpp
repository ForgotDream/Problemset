#include <cstdio>
#include <iostream>

using namespace std;

const int M = (int)1e4 + 50;
int m, n;
int a[M], p[M], t[M];
int f[M];

void solve() {
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++)
      if (j >= t[i]) f[j] = max(f[j], f[j - t[i]] + p[i]);
  cout << f[m] << endl;
  return;
}

int main() {
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i] >> t[i];
  }
  solve();
  return 0;
}
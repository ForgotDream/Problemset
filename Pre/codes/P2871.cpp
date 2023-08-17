#include <cstdio>
#include <iostream>

using namespace std;

int n, m;
int f[13000];
int a[3500], b[3500];

void solve() {
  for (int i = 1; i <= n; i++)
    for (int j = m; j >= 0; j--)
      if (j >= a[i]) f[j] = max(f[j], f[j - a[i]] + b[i]);
  cout << f[m] << endl;
  return;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
  solve();
  return 0;
}
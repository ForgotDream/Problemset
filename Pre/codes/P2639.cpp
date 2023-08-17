#include <cstdio>
#include <iostream>

using namespace std;

int h, n;
int s[505];
int f[505][45050];

void solve() {
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= h; j++)
      if (j >= s[i])
        f[i][j] = max(f[i - 1][j], f[i - 1][j - s[i]] + s[i]);
      else
        f[i][j] = f[i - 1][j];
  cout << f[n][h] << endl;
  return;
}

int main() {
  cin >> h >> n;
  for (int i = 1; i <= n; i++) cin >> s[i];
  solve();
  return 0;
}
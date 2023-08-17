#include <cstdio>
#include <iostream>

using namespace std;

int n, m;
int a[105];
int f[105][10050];

void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      f[i][j] = f[i - 1][j];
      if (j >= a[i]) f[i][j] += f[i - 1][j - a[i]];
      if (j == a[i]) f[i][j]++;
    }
  }
  /*
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) cout << f[i][j] << (j == m ? "\n" : " ");
  }
  */
  cout << f[n][m] << endl;
  return;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  solve();
  return 0;
}
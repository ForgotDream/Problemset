#include <cstdio>
#include <iostream>

using namespace std;

int c, h;
int a[5050];
int f[50050];

void solve() {
  for (int i = 1; i <= h; i++)
    for (int j = c; j >= 0; j--)
      if (j >= a[i]) f[j] = max(f[j], f[j - a[i]] + a[i]);
  cout << f[c] << endl;
  return;
}

int main() {
  cin >> c >> h;
  for (int i = 1; i <= h; i++) cin >> a[i];
  solve();
  return 0;
}
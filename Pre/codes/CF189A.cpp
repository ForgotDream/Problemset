#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int n, l[10];
int f[4050];

void solve() {
  memset(f, 0xc0, sizeof(f));
  f[0] = 0;
  for (int i = 1; i <= 3; i++)
    for (int j = l[i]; j <= n; j++) f[j] = max(f[j], f[j - l[i]] + 1);
  cout << f[n] << endl;
  return;
}

int main() {
  cin >> n >> l[1] >> l[2] >> l[3];
  solve();
  return 0;
}
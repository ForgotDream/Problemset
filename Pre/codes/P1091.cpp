#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int n, ans = -1;
int a[105];
int f1[105], f2[105];

void solve() {
  for (int i = n - 1; i >= 1; i--)
    for (int j = i + 1; j <= n; j++)
      if (a[i] > a[j]) f1[i] = max(f1[i], f1[j] + 1);
  for (int i = 2; i <= n; i++)
    for (int j = 1; j < i; j++)
      if (a[i] > a[j]) f2[i] = max(f2[i], f2[j] + 1);
  for (int i = 1; i <= n; i++) ans = max(ans, f1[i] + f2[i] - 1);
  cout << n - ans << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], f1[i] = 1, f2[i] = 1;
  solve();
  return 0;
}

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int cnt, calc[200];
long long f[(int)1e5 + 50];
int n;

void pre() {
  for (int i = 1; i <= 25; i++) calc[i] = i * i * i * i, cnt++;
  return;
}

void solve() {
  memset(f, 0x3f, sizeof(f));
  f[0] = 0;
  for (int i = 1; i <= 25; i++)
    for (int j = calc[i]; j <= n; j++) f[j] = min(f[j], f[j - calc[i]] + 1);
  cout << f[n];
  return;
}

int main() {
  cin >> n;
  pre();
  solve();
  return 0;
}
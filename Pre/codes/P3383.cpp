#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;
int n, q, k;
bool f[(int)1e8 + 5];
int a[(int)1e7 + 5];

void pre() {
  int cnt = 0;
  for (int i = 2; i * i <= n; i++)
    if (!f[i]) {
      for (ll j = i * i; j <= n; j += i) f[j] = true;
    }
  for (int i = 2; i <= n; i++)
    if (!f[i]) a[++cnt] = i;
  return;
}

void solve() {
  while (q--) cin >> k, cout << a[k] << endl;
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> q;
  pre();
  solve();
  return 0;
}
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50;
int n;
i64 a[N], sum, maxx;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += a[i];
  }

  for (int i = 1; i < n; i++) {
    maxx = max(maxx, a[i] + a[i + 1]);
  }
  maxx = max(maxx, a[1] + a[n]);

  cout << max(maxx, (i64) ceil((double) sum / (n >> 1))) << '\n';

  return 0;
}
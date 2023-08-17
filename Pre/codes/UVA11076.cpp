#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

typedef unsigned long long ll;

int n;
int a[20];
int sum[20];
ll ans, t;
const ll calc[] = {0,          1,           11,          111,      1111,
                   11111,      111111,      1111111,     11111111, 111111111,
                   1111111111, 11111111111, 111111111111};

ll fact(int n) { return n == 0 ? (ll)1 : (ll)n * fact(n - 1); }

void solve() {
  ll f = fact(n);
  for (int i = 0; i <= 9; i++) f /= fact(sum[i]);
  ans = (ll)t * (ll)f * (ll)calc[n] / (ll)n;
  cout << ans << endl;
  t = 0, ans = 0, n = 0;
  memset(a, 0, sizeof(a));
  memset(sum, 0, sizeof(sum));
  return;
}

int main() {
  while (cin >> n && n != 0) {
    for (int i = 1; i <= n; i++) cin >> a[i], t += a[i], sum[a[i]]++;
    solve();
  }
  return 0;
}
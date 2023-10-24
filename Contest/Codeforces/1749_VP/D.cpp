#include <iostream>
#include <numeric>
#include <set>

using i64 = long long;

constexpr int mod = 998244353;
i64 slowMul(i64 a, i64 b, i64 mod) {
  i64 res = 0;
  for (; b; b >>= 1) {
    if (b & 1) (res += a) %= mod;
    (a += a) %= mod;
  }
  return res;
}
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = slowMul(res, base, mod);
    base = slowMul(base, base, mod);
  }
  return res;
}

constexpr int N = 3e5 + 50;
bool isNotPrime[N];
int prime[N], cnt;
void getPrime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}

i64 n, m;
void solve() {
  std::cin >> n >> m;
  getPrime(n);
  i64 ans = 0, lcm = 1, d = 1, pw = 1;
  for (int i = 1; i <= n; i++) pw = slowMul(pw, m, mod), (ans += pw) %= mod;
  std::set<int> s;
  for (int i = 1; i <= n; i++) {
    int cur = isNotPrime[i] ? 1 : i;
    s.insert(i);
    lcm *= cur;
    i64 cnt = m / lcm;
    d = slowMul(d, cnt, mod);
    (ans -= d - mod) %= mod;
    if (lcm > m) break;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
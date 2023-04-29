#include <bits/stdc++.h>

using i64 = long long;
using d80 = long double;

int n, a, b, p, q;
i64 all;
std::vector<std::vector<std::vector<i64>>> f;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  i64 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

i64 inv(i64 num, i64 mod) {
  i64 x, y;
  exgcd(num, mod, x, y);
  return (x % mod + mod) % mod;
}

i64 dfs(int dep = 1, int apos = a, int bpos = b) {
  static const i64 MOD = 998244353;
  static const i64 invp = inv(p, MOD), invq = inv(q, MOD);
  if (f[apos][bpos][dep & 1] != -1) {
    return f[apos][bpos][dep & 1];
  }
  
  i64 res = 0;

  if (dep & 1) {
    for (int i = 1; i <= p; i++) {
      if (apos + i >= n) {
        (res += invp) %= MOD;
      } else {
        (res += invp * dfs(dep + 1, apos + i, bpos) % MOD) %= MOD;
      }
    }
  } else {
    for (int i = 1; i <= q; i++) {
      if (bpos + i >= n) {
        continue;
      } else {
        (res += invq * dfs(dep + 1, apos, bpos + i) % MOD) %= MOD;
      }
    }
  }

  f[apos][bpos][dep & 1] = res;
  
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> n >> a >> b >> p >> q;
  f.resize(n + 50, std::vector<std::vector<i64>>(n + 50, std::vector<i64>(2, -1)));

  std::cout << dfs() << "\n";

  return 0;
}
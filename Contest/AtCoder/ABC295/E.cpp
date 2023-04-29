#include <algorithm>
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  int d = exgcd(a, b, y, x);
  y -= a / b * x;
  return d;
}

i64 fastPow(i64 base, i64 pow, i64 mod) {
  i64 res = 1;
  while (pow) {
    if (pow & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
    pow >>= 1;
  }
  return res;
}

i64 inv(i64 num, i64 mod) {
  i64 x, y;
  exgcd(num, mod, x, y);
  return (x % mod + mod) % mod;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  static const int MOD = 998244353;

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<int> a;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    int u;
    std::cin >> u;
    if (u) {
      a.push_back(u);
    } else {
      cnt++;
    }
  }

  if (!cnt) {
    std::sort(a.begin(), a.end());
    std::cout << a[k - 1] << '\n';
    return 0;
  }

  std::vector<std::vector<int>> c(cnt + 1, std::vector<int>(cnt + 1));
  for (int i = 0; i <= cnt; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      (c[i][j] = c[i - 1][j] + c[i - 1][j - 1]) %= MOD;
    }
  }

  int max = *std::max_element(a.begin(), a.end());
  std::vector<int> bucket(max + 1);
  for (int i = 0; i < a.size(); i++) {
    bucket[a[i]]++;
  }
  for (int i = 1; i <= max; i++) {
    bucket[i] += bucket[i - 1];
  }

  i64 ans = 0;
  for (int i = 1; i <= m; i++) {
    int origin = bucket[i] - bucket[i - 1];
    int smaller = bucket[i - 1];
    if (bucket[i] + cnt < k) {
      continue;
    } else if (smaller > k) {
      continue;
    }
    for (int j = 0; j <= cnt; j++) {
      if (j + bucket[i] >= k) {
        (ans += c[cnt][j] * fastPow(i - 1, j, MOD) * fastPow(m - i + 1, cnt - j, MOD) * i) %= MOD;
      } else {
        (ans += cnt * c[cnt - 1][j] * fastPow(i - 1, j, MOD) * fastPow(m - i + 1, cnt - j - 1, MOD) * i) %= MOD;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}
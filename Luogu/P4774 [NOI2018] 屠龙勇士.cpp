/*
 * @file    P4774 [NOI2018] 屠龙勇士.cpp
 * @author  ForgotDream
 * @brief   excrt
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using i128 = __int128;

constexpr int N = 1e5 + 50;

int n, m;
i64 a[N], b[N], p[N], t[N], mx;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  i64 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

i64 excrt() {
  i64 ans = 0;
  i128 lcm = 1;
  for (int i = 1; i <= n; i++) {
    i64 A = i128(b[i]) * lcm % p[i], B = p[i], 
        C = (a[i] - b[i] * ans % p[i] + p[i]) % p[i], x, y;
    // assert(A >= 0);
    i64 g = exgcd(A, B, x, y);
    x = (x % B + B) % B;
    if (C % g) return -1;
    i128 nxt = lcm * B / g;
    ans = (ans + i128(C / g) * x % (B / g) * lcm % nxt) % nxt;
    lcm = nxt;
  }
  if (ans < mx) ans += ((mx - ans - 1) / lcm + 1) * lcm;
  return ans;
}

void solve() {
  mx = 0;

  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  for (int i = 1; i <= n; i++) std::cin >> t[i];
  std::multiset<i64> s;
  for (int i = 1, u; i <= m; i++) std::cin >> u, s.insert(u);

  for (int i = 1; i <= n; i++) {
    auto it = s.upper_bound(a[i]);
    if (it != s.begin()) it--;
    b[i] = *it, s.erase(it), s.insert(t[i]);
    mx = std::max(mx, (a[i] - 1) / b[i] + 1);
  }

  std::cout << excrt() << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}

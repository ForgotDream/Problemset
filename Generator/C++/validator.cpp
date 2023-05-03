#include <bits/stdc++.h>

using i64 = long long;

constexpr int MOD = 998244353;

signed main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string name = argv[1];

  std::ifstream in("data\\" + name + ".in", std::ios::in);
  // in.tie(0);
  std::ofstream out("data\\" + name + ".out", std::ios::out);
  // out.tie(0);

  if (in.is_open() && out.is_open()) {
    int n;
    in >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
      in >> a[i];
    }

    std::vector<i64> pow(n);
    pow[0] = 1;
    for (int i = 1; i < n; i++) {
      (pow[i] = 10 * pow[i - 1]) %= MOD;
    }
    for (int i = 1; i < n; i++) {
      pow[i] += pow[i - 1];
      pow[i] %= MOD;
    }

    i64 fact = 1;
    for (int i = 1; i < n; i++) {
      (fact *= i) %= MOD;
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
      (ans += (i64) a[i] * pow[n - 1] * fact % MOD) %= MOD;
    }

    out << ans << "\n";

    in.close(), out.close();
  }

  return 0;
}
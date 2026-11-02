#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k, x;
  std::cin >> n >> k >> x;

  std::vector<i64> p(n);
  i64 sum_p = 0;
  for (int i = 0; i < n; ++i) std::cin >> p[i], sum_p += i * p[i];

  i64 mod = (n % 2 == 0) ? (n / 2) : n;
  i64 pp = sum_p % mod;

  // baoli
  if (n <= 10) {
    std::vector<int> rem;
    for (int i = 0; i < n; ++i) {
      if (i != x) rem.push_back(i);
    }
    bool flg = false;
    do {
      i64 cur = 0;
      int idx = 0;
      for (int i = 0; i < n; ++i) {
        if (i == k) cur += 1ll * i * x;
        else cur += 1ll * i * rem[idx++];
      }
      if (cur % mod == pp) {
        idx = 0;
        for (int i = 0; i < n; ++i) {
          if (i == k) std::cout << x << " \n"[i == n - 1];
          else std::cout << rem[idx++] << " \n"[i == n - 1];
        }
        flg = true;
        break;
      }
    } while (std::next_permutation(rem.begin(), rem.end()));
    
    if (!flg) std::cout << "-1\n";
    return;
  }

  std::vector<int> q, v;
  for (int i = 0; i < n; ++i) {
    if (i != k) q.push_back(i);
    if (i != x) v.push_back(i);
  }

  i64 sum_mx = 0;
  for (int i = 0; i < q.size(); ++i) sum_mx += 1ll * q[i] * v[i];
  sum_mx += 1ll * k * x;

  i64 delta = (sum_mx % mod - pp % mod + mod) % mod;

  bool flg = true;
  while (delta > 0 && flg) {
    flg = false;
    
    for (int i = 0; i < v.size() - 1 && delta > 0; ++i) {
      i64 cost = 1ll * (q[i + 1] - q[i]) * (v[i + 1] - v[i]);
      if (cost > 0 && cost <= delta) {
        delta -= cost;
        std::swap(v[i], v[i + 1]);
        flg = true;
      }
    }
    
    for (int i = v.size() - 2; i >= 0 && delta > 0; --i) {
      i64 cost = (q[i + 1] - q[i]) * (v[i + 1] - v[i]);
      if (cost > 0 && cost <= delta) {
        delta -= cost;
        std::swap(v[i], v[i + 1]);
        flg = true;
      }
    }
  }

  if (delta > 0) {
    std::cout << "-1\n";
  } else {
    std::vector<int> ans(n);
    ans[k] = x;
    for (int i = 0; i < q.size(); ++i) ans[q[i]] = v[i];
    for (int i = 0; i < n; ++i) std::cout << ans[i] << " \n"[i == n - 1];
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}

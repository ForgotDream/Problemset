#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

constexpr int base = 233;

void solve() {
  std::string s, l, r;
  int m;
  std::cin >> s >> m >> l >> r;

  int n = s.length();

  std::set<u64> hash;
  u64 cur = 0, pw = 1;
  for (int i = 0; i < m; i++) {
    cur *= base;
    cur += s[i];
    pw *= base;
  }
  hash.insert(cur);
  for (int i = m; i < n; i++) {
    cur -= pw * s[i - m];
    cur *= base;
    cur += s[i];
    hash.insert(cur);
  }

  for (int i = 0; i < (1 << m); i++) {
    u64 cur = 0;
    for (int j = 0; j < m; j++) {
      cur *= base;
      if (i & (1 << j)) {
        cur += l[j];
      } else {
        cur += r[j];
      }
    }
    if (!hash.count(cur)) {
      std::cout << "YES\n";
      return;
    }
  }

  std::cout << "NO\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;

constexpr i64u base = 127;

i64u getHash(const std::string &s) {
  i64u hash = 0, pow = 1;
  int len = s.length();
  for (int i = len - 1; i >= 0; i--) {
    hash += pow * s[i];
    pow *= base;
  }
  return hash;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  if (m == 1) {
    std::vector<int> cnt(26);
    for (int i = 0; i < n; i++) {
      char c;
      std::cin >> c;
      cnt[c - 'a']++;
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) {
      ans += !!(cnt[0]);
    }
    std::cout << ans << "\n";
    return 0;
  }

  std::vector<std::string> a(n);
  std::unordered_map<i64u, std::vector<int>> hash(n);
  int cnt = 0;
  std::vector<int> bln(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    i64 curHash = getHash(a[i]);
    if (!hash.count(curHash)) {
      bln[i] = ++cnt;
    } else {
      bln[i] = bln[hash[curHash][0]];
    }
    hash[curHash].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    i64u curHash = 0, pow = 1;
    for (int j = m - 1; j >= 0; j--) {
      curHash += pow * a[i][j];
      pow *= base;
    }
    for (int j = m; j < 2 * m - 1; j++) {
      curHash = base * (curHash - pow * a[i][j - m]) + a[i][j];
      if (hash.count(curHash)) {
        bln[i] = bln[hash[curHash][0]];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (!bln[i]) {
      cnt++;
    }
  }

  std::cout << cnt << "\n";

  return 0;
}
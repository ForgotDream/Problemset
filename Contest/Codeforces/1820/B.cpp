#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  std::vector<int> a;
  int cnt = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '0') {
      if (cnt) {
        a.push_back(cnt);
        cnt = 0;
      }
    } else {
      cnt++;
    }
  }
  if (cnt) {
    if (cnt != s.length()) {
      if (s[0] == '0') {
        a.push_back(cnt);
      } else {
        a[0] += cnt;
      }
    } else {
      std::cout << (i64) s.length() * s.length() << "\n";
      return;
    }
  }

  if (a.empty()) {
    std::cout << 0 << "\n";
    return;
  }

  int max = *max_element(a.begin(), a.end());
  std::cout << (i64) (max / 2 + max % 2) * (max / 2 + 1) << "\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
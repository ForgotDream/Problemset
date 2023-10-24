#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  int i = 0, l, r;
  while (i < s.length() && (s[i] == '0' || s[i] == '?')) {
    if (s[i] == '?') {
      s[i] = '0';
    }
    i++;
  }
  l = i;
  i = s.length() - 1;
  while (i >= 0 && (s[i] == '1' || s[i] == '?')) {
    if (s[i] == '?') {
      s[i] = '1';
    }
    i--;
  }
  r = i;

  // std::cerr << l << " " << r << "\n";
  for (int i = l; i <= r; i++) {
    if (s[i] == '?') {
      if (s[i - 1] == '1') {
        s[i] = '1';
      } else {
        s[i] = '0';
      }
    }
  }

  std::cout << s << "\n";
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
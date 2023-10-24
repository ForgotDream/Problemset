#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::string s;
  std::cin >> n >> s;

  if (n % 2 || std::count(s.begin(), s.end(), '(') != n / 2) {
    std::cout << -1 << "\n";
    return;
  }

  int p = 0, cnt = 0;
  std::vector<int> ans(n);
  char flg = true;
  for (int i = 0; i < n; i++) {
    if (!p) {
      flg = s[i];
      p = 1;
      ans[i] = ++cnt;
    } else {
      if (s[i] == flg) {
        p++;
      } else {
        p--;
      }
      ans[i] = cnt;
    }
  }

  std::cout << cnt << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << ans[i] << " \n"[i == n - 1];
  }
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
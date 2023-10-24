#include <algorithm>
#include <iostream>
#include <string>

using i64 = long long;

std::string m, s;
void solve() {
  std::cin >> m >> s;
  int la = m.length(), lb = s.length();
  int j = lb - 1;
  std::string ans;
  for (int i = la - 1; i >= 0; i--) {
    if (j < 0) {
      std::cout << -1 << "\n";
      return;
    }
    if (s[j] >= m[i]) {
      ans += s[j] - m[i] + '0';
      j--;
    } else {
      if (j == 0 || s[j - 1] != '1') {
        std::cout << -1 << "\n";
        return;
      }
      ans += 10 + s[j] - m[i] + '0';
      j -= 2;
    }
  }
  while (j >= 0) ans += s[j--];
  std::reverse(ans.begin(), ans.end());
  int p = 0;
  while (p < ans.length() && ans[p] == '0') p++;
  if (p == ans.length()) {
    std::cout << 0 << "\n";
  } else {
    for (int i = p; i < ans.length(); i++) std::cout << ans[i];
    std::cout << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
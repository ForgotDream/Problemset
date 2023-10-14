#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using i64 = long long;

constexpr int N = 5e5 + 50;
int n;
std::string t, s[N];
std::vector<int> ans;
void solve() {
  std::cin >> n >> t;
  for (int i = 1; i <= n; i++) {
    std::cin >> s[i];
    if (s[i] == t) {
      ans.push_back(i);
      continue;
    } else if (std::abs((int)s[i].length() - (int)t.length()) > 1) {
      continue;
    }
    if (s[i].length() == t.length()) {
      int cnt = 0;
      for (int j = 0; j < t.length(); j++) {
        cnt += s[i][j] != t[j];
        if (cnt >= 2) break;
      }
      if (cnt == 1) ans.push_back(i);
    } else if (s[i].length() == t.length() + 1) {
      int l = 0, r = 0, cnt = 0;
      while (l < t.length() && r < s[i].length()) {
        if (t[l] == s[i][r]) l++, r++;
        else cnt++, r++;
        if (cnt >= 2) break;
      }
      if (cnt <= 1) ans.push_back(i);
    } else {
      int l = 0, r = 0, cnt = 0;
      while (l < t.length() && r < s[i].length()) {
        if (t[l] == s[i][r]) l++, r++;
        else cnt++, l++;
        if (cnt >= 2) break;
      }
      if (cnt <= 1) ans.push_back(i);
    }
  }
  std::cout << ans.size() << "\n";
  for (auto i : ans) std::cout << i << " ";
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

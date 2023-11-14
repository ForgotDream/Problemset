#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n;
std::string s[N];
int len[6][100];
int sum(const std::string &s) {
  int res = 0;
  for (auto c : s) res += c - '0';
  return res;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> s[i], len[s[i].length()][sum(s[i])]++;
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    int cur = 0;
    for (int j = 0; j < s[i].length(); j++) {
      cur += s[i][j] - '0';
      // std::cout << cur << " \n"[j == s[i].length() - 1];
      if (2 * cur >= sum(s[i]) && 2 * (j + 1) >= s[i].length()) {
        ans += len[2 * (j + 1) - s[i].length()][2 * cur - sum(s[i])];
      }
    }
    cur = 0;
    for (int j = s[i].length() - 1; j; j--) {
      cur += s[i][j] - '0';
      // std::cout << cur << " \n"[j == s[i].length() - 1];
      if (2 * cur >= sum(s[i]) && 2 * (s[i].length() - j) >= s[i].length()) {
        ans += len[2 * (s[i].length() - j) - s[i].length()][2 * cur - sum(s[i])];
      }
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
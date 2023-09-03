/**
 * @file    CF725C Hidden Word.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-31
 */
#include <iostream>
#include <string>

using i64 = long long;

std::string s;
int cir[30];
char ans[2][30];
void solve() {
  std::cin >> s;
  char c;
  for (int i = 0; i < s.length(); i++) {
    if (i && s[i] == s[i - 1]) {
      std::cout << "Impossible\n";
      return;
    }
    if (cir[s[i] - 'A']) c = s[i];
    cir[s[i] - 'A']++;
  }
  auto l = s.find(c), r = s.rfind(c);
  s += s;
  int len = (r - l + 1) / 2, p = l;
  ans[0][13 - len + 1] = c;
  for (int i = 13 - len + 2; i <= 13; i++) ans[0][i] = s[++p];
  for (int i = 13; i >= 1; i--) {
    p++;
    if (p == r) p++;
    ans[1][i] = s[p];
  }
  for (int i = 1; i <= 13 - len; i++) ans[0][i] = s[++p];
  std::cout << (ans[0] + 1) << "\n";
  std::cout << (ans[1] + 1) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
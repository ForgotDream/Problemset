/**
 * @file    CF113A Grammar Lessons.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-05
 */
#include <iostream>

using i64 = long long;
using pii = std::pair<int, int>;

enum TYPE { INVALID = -1, ADJ, NOUN, VERB };
std::pair<TYPE, int> getType(const std::string &s) {
  int len = s.length();
  if (len < 3) return std::make_pair(INVALID, -1);
  if (len >= 4 && s.substr(len - 4) == "lios") return std::make_pair(ADJ, 0);
  if (len >= 5 && s.substr(len - 5) == "liala") return std::make_pair(ADJ, 1);
  if (len >= 3 && s.substr(len - 3) == "etr") return std::make_pair(NOUN, 0);
  if (len >= 4 && s.substr(len - 4) == "etra") return std::make_pair(NOUN, 1);
  if (len >= 6 && s.substr(len - 6) == "initis") return std::make_pair(VERB, 0);
  if (len >= 6 && s.substr(len - 6) == "inites") return std::make_pair(VERB, 1);
  return std::make_pair(INVALID, -1);
}
std::string s;
void solve() {
  int cur = 0, sex = -1, cnt = 0;
  bool flg = false;
  while (std::cin >> s) {
    auto [typ, se] = getType(s);
    if (typ == INVALID) {
      std::cout << "NO\n";
      return;
    } else if (typ == ADJ) {
      if (cur != 0 || (sex != -1 && se != sex)) {
        std::cout << "NO\n";
        return;
      }
      if (sex == -1) sex = se;
    } else if (typ == NOUN) {
      if (flg || cur != 0 || (sex != -1 && se != sex)) {
        std::cout << "NO\n";
        return;
      }
      cur = 1;
      if (sex == -1) sex = se;
    } else {
      if (flg || (cnt && cur != 1) || (sex != -1 && se != sex)) {
        std::cout << "NO\n";
        return;
      }
      if (!cnt) flg = true;
    }
    ++cnt;
  }
  if (cur == 0 && cnt > 1) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
/**
 * @file    CF138A Literature Lesson.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-05
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 2550;
int n, k;
std::string s[4], suf[4];
int type[N];
enum TYPE { AABB, ABAB, ABBA, AAAA };
bool isVowels(const char &c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
std::string getSuffix(const std::string &s) {
  int cnt = 0;
  for (int i = s.length() - 1; i >= 0; i--) {
    if (isVowels(s[i])) cnt++;
    if (cnt == k) return s.substr(i);
  }
  return std::string();
}
bool check(int i, int j) { return suf[i] == suf[j]; }
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++) {
      std::cin >> s[j], suf[j] = getSuffix(s[j]);
      if (suf[j].empty()) {
        std::cout << "NO\n";
        return;
      }
    }
    if (check(0, 1) && check(2, 3) && !check(0, 2)) {
      type[AABB]++;
    } else if (check(0, 2) && check(1, 3) && !check(0, 1)) {
      type[ABAB]++;
    } else if (check(0, 3) && check(1, 2) && !check(0, 1)) {
      type[ABBA]++;
    } else if (check(0, 1) && check(2, 3) && check(0, 2)) {
      type[AAAA]++;
    } else {
      std::cout << "NO\n";
      return;
    }
    int cnt = 0;
    for (int j = 0; j < 3; j++) cnt += !!type[j];
    if (cnt > 1) {
      std::cout << "NO\n";
      return;
    }
  }
  int p = -1;
  for (int i = 0; i < 4; i++) {
    if (type[i]) {
      p = i;
      break;
    }
  }
  if (p == 0) {
    std::cout << "aabb\n";
  } else if (p == 1) {
    std::cout << "abab\n";
  } else if (p == 2) {
    std::cout << "abba\n";
  } else {
    std::cout << "aaaa\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
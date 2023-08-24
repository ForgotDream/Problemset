/**
 * @file    CF778B Bitwise Formula.cpp
 * @author  ForgotDream
 * @brief   Simulation + Bitmasks
 * @date    2023-08-24
 */
#include <iostream>
#include <map>
#include <string>

using i64 = long long;

constexpr int N = 1e6 + 50;
std::map<std::string, int> mp;
struct Variable {
  bool constant = false;
  int a, op = 0, b, cur;
  std::string s, val;
} var[N];
std::istream& operator>>(std::istream &is, Variable &var) {
  std::string t;
  is >> var.s >> t >> t;
  if (std::isdigit(t[0])) {
    var.constant = true, var.val = t;
  } else {
    var.a = mp[t];
    std::cin >> t;
    if (t[0] == 'A') var.op = 1;
    else if (t[0] == 'O') var.op = 2;
    else var.op = 3;
    std::cin >> t;
    var.b = mp[t];
  }
  return is;
}

int n, m;
std::string ans1, ans2;
int calc(int idx, int d) {
  var[0].cur = d;
  int res = 0;
  for (int i = 1; i <= n; i++) {
    if (var[i].constant) {
      var[i].cur = var[i].val[idx] - '0';
    } else {
      int l = var[var[i].a].cur, r = var[var[i].b].cur;
      if (var[i].op == 1) var[i].cur = l & r;
      else if (var[i].op == 2) var[i].cur = l | r;
      else var[i].cur = l ^ r;
    }
    res += var[i].cur;
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  var[0].s = "?", mp[var[0].s] = 0;
  for (int i = 1; i <= n; i++) std::cin >> var[i], mp[var[i].s] = i;
  for (int i = 0; i < m; i++) {
    int d0 = calc(i, 0), d1 = calc(i, 1);
    if (d0 <= d1) ans1 += '0';
    else ans1 += '1';
    if (d0 >= d1) ans2 += '0';
    else ans2 += '1';
    // std::cerr << d0 << " " << d1 << "\n";
  }
  std::cout << ans1 << "\n" << ans2 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
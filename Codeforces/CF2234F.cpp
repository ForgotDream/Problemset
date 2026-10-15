/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;
using pli = std::pair<i64, int>;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> h(n);
  int piv = 0;

  for (int i = 0; i < n; i++) {
    std::cin >> h[i];
    if (h[i] > h[piv]) piv = i;
  }

  std::vector<int> H(2 * n);
  for (int i = 0; i < 2 * n; i++) H[i] = h[i % n];

  std::vector<i64> lans(n), rans(n);

  std::stack<pli> ls;
  i64 cur = 0;

  for (int i = piv + n - 1; i >= piv + 1; i--) {
    i64 val = H[i], cnt = 1;
    while (!ls.empty() && ls.top().first <= val) {
      cur -= ls.top().first * ls.top().second;
      cnt += ls.top().second;
      ls.pop();
    }
    ls.emplace(val, cnt);
    cur += val * cnt;
    lans[i % n] = cur;
  }

  std::stack<pli> rs;
  cur = 0;

  for (int i = piv + 1; i <= piv + n - 1; i++) {
    i64 val = H[i], cnt = 1;
    while (!rs.empty() && rs.top().first <= val) {
      cur -= rs.top().first * rs.top().second;
      cnt += rs.top().second;
      rs.pop();
    }
    rs.emplace(val, cnt);
    cur += val * cnt;
    rans[(i + 1) % n] = cur;
  }

  for (int i = 0; i < n; i++) {
    std::cout << lans[i] + rans[i] << " \n"[i == n - 1];
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}

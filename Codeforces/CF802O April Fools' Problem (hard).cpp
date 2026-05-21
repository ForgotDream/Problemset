/*
 * @file    CF802O April Fools' Problem (hard).cpp
 * @author  ForgotDream
 * @brief   WQS Binary Search + Regrettable Greddy
 * @date    2024-02-26
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pli = std::pair<i64, int>;

constexpr int N = 5e5 + 50;

int n, k, a[N], b[N];

i64 cur, cnt;

bool check(i64 u) {
  std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
  cur = cnt = 0;
  for (int i = 1; i <= n; i++) {
    pq.emplace(a[i], 1);
    if (pq.top().first + (b[i] + u) < 0) {
      cur += pq.top().first + (b[i] + u), cnt += pq.top().second;
      pq.pop(), pq.emplace(-(b[i] + u), 0);
    }
  }
  return cnt < k;
}

void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];

  i64 lo = -2e9, hi = 2e9, ans = 0;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    std::cerr << mid << "\n";
    if (check(mid)) hi = mid - 1, ans = cur - k * mid;
    else lo = mid + 1;
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

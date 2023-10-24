#include <iostream>
#include <queue>

using i64 = long long;

int n, d, p;
std::priority_queue<i64> pq;
void solve() {
  std::cin >> n >> d >> p;
  i64 ans = 0, sum = 0;
  for (int i = 1, u; i <= n; i++) {
    std::cin >> u;
    sum += u, pq.emplace(u);
  }
  ans = sum;
  int cnt = 0;
  while (!pq.empty()) {
    cnt++;
    int cur = d;
    i64 cpy = sum + 1ll * cnt * p;
    while (!pq.empty() && cur) {
      cur--, cpy -= pq.top(), sum -= pq.top(), pq.pop();
    }
    ans = std::min(ans, cpy);
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
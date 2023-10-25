/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-23
 */
#include <iostream>
#include <queue>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q, a[N];
int blk, bcnt, l[N], r[N], bln[N];
std::priority_queue<int> max[N];
std::priority_queue<int, std::vector<int>, std::greater<>> tag[N];
void rebuild(int u) {
  if (tag[u].empty()) return;
  for (int i = l[u]; i <= r[u]; i++) {
    if (a[i] > tag[u].top()) {
      int pre = a[i];
      a[i] = tag[u].top(), tag[u].pop();
      tag[u].push(pre);
    }
  }
  while (!tag[u].empty()) tag[u].pop();
}
int modify(int u, int l, int r, int val) {
  rebuild(u);
  for (int i = l; i <= r; i++) {
    if (a[i] > val) std::swap(a[i], val);
  }
  while (!max[u].empty()) max[u].pop();
  for (int i = ::l[u]; i <= ::r[u]; i++) max[u].push(a[i]);
  return val;
}
void init() {
  blk = std::sqrt(n), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) l[i] = (i - 1) * blk + 1, r[i] = i * blk;
  r[bcnt] = n;
}
void solve() {
  std::cin >> n >> q;
  init();
  for (int i = 1; i <= n; i++) std::cin >> a[i], pq[bln[i]].push(a[i]);
  for (int i = 1, l, r, val; i <= q; i++) {
    std::cin >> l >> r >> val;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

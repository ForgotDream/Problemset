#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 6e5 + 50;
int n;
i64 m;
std::vector<int> f[N];
struct Node {
  int tim, idx, bln;
  Node() = default;
  Node(int t, int i, int b) : tim(t), idx(i), bln(b) {}
  bool operator<(const Node &rhs) const {
    return tim > rhs.tim || (tim == rhs.tim && idx < rhs.idx);
  }
};
std::priority_queue<Node> pq;
void solve() {
  std::cin >> n >> m;
  for (int i = 1, siz; i <= n; i++) {
    std::cin >> siz, f[i].resize(siz);
    for (auto &j : f[i]) std::cin >> j;
    pq.emplace(f[i][0], 1, i);
  }
  i64 sum = 0, cur = 0, ans = 0;
  while (!pq.empty()) {
    auto [tim, idx, bln] = pq.top();
    std::cerr << "#" << tim << " " << idx << " " << bln << "\n";
    pq.pop();
    if (idx != f[bln].size()) pq.emplace(f[bln][idx], idx + 1, bln);
    cur += tim, ans += tim * sum, sum++;
  }
  std::cout << cur << " " << sum << "\n";
  if (cur < m) ans += (m - cur) * sum;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

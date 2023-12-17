#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n;
std::stack<int> rst[N];
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;
bool f[N];
int idx[N], cnt;
void solve() {
  std::cin >> n;
  for (int i = 1, t, x; i <= n; i++) {
    std::cin >> t >> x;
    if (t == 1) {
      rst[x].push(i);
      idx[i] = ++cnt;
    } else {
      if (rst[x].empty()) {
        std::cout << -1 << "\n";
        return;
      }
      int u = rst[x].top();
      bit.modify(u, 1), bit.modify(i + 1, -1);
      f[idx[u]] = true;
      rst[x].pop();
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) ans = std::max(ans, bit.query(i));
  std::cout << ans << "\n";
  for (int i = 1; i <= cnt; i++) std::cout << f[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 3e5;
int q;
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i < N; i += (i & -i)) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= (i & -i)) res += tree[i];
    return res;
  }
} bl, br;
struct Query {
  char opt;
  int l, r;
} query[N];
std::vector<int> b;
int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1; 
}
void solve() {
  std::cin >> q;
  b.push_back(0), b.push_back(1e9 + 1);
  for (int i = 1, l, r; i <= q; i++) {
    char c;
    std::cin >> c >> l >> r, query[i] = {c, l, r};
    b.push_back(l), b.push_back(r);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int m = b.size();
  i64 cur = 0;
  for (int i = 1; i <= q; i++) {
    auto [opt, l, r] = query[i];
    l = find(l), r = find(r);
    if (opt == '+') {
      cur += br.query(l - 1) + bl.query(m - r);
      // std::cerr << bl.query(m - r) << " " << br.query(l - 1) << "\n";
      bl.modify(m - l + 1, 1), br.modify(r, 1);
    } else {
      bl.modify(m - l + 1, -1), br.modify(r, -1);
      cur -= br.query(l - 1) + bl.query(m - r);
      // std::cerr << bl.query(m - r) << " " << br.query(l - 1) << "\n";
    }
    if (cur > 0) std::cout << "YES\n";
    else std::cout << "NO\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

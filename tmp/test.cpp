#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N = 1e5 + 5;
struct DSU {
  std::stack<std::pair<int, int>, std::vector<std::pair<int, int>>> stk;
  int tree[N * 2], Size[N * 2];
  inline void init(int n) {
    while (stk.size()) stk.pop();
    for (int i = 1; i <= n; i++) tree[i] = i, Size[i] = 1;
  }
  inline int Find(int x) {
    return x == tree[x] ? x : Find(tree[x]);
  }
  inline bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (Size[x] > Size[y]) std::swap(x, y);
    tree[x] = y;
    Size[y] += Size[x];
    stk.push(std::pair<int, int>(x, y));
    return true;
  }
  inline int GetTime() { return stk.size(); }
  inline bool roll() {
    if (stk.empty()) return false;
    auto [x, y] = stk.top();
    stk.pop();
    tree[x] = x;
    tree[y] -= Size[x];
    return true;
  }
  inline bool back(int lim) {
    while (stk.size() > lim)
      if (!roll()) return false;
    return true;
  }
} dsu;
int X[N * 2], Y[N * 2];
int n, m, K;
std::vector<int> tree[N << 2];
inline void modify(int k, int l, int r, int L, int R, int cag) {
  if (L <= l && r <= R) {
    tree[k].push_back(cag);
    return;
  }
  int mid = (l + r) / 2;
  if (L <= mid) modify(k << 1, l, mid, L, R, cag);
  if (mid + 1 <= R) modify(k << 1 | 1, mid + 1, r, L, R, cag);
}
inline void dfs(int k, int l, int r) {
  bool flag = true;
  int lim = dsu.GetTime();
  for (auto e : tree[k]) {
    int x = X[e], y = Y[e];
    int fx = dsu.Find(x), fy = dsu.Find(y);
    if (fx == fy) {
      flag = false;
      for (int i = l; i <= r; i++) std::cout << "No\n";
      break;
    }
    dsu.Merge(x, y + n);
    dsu.Merge(x + n, y);
  }
  if (flag) {
    if (l == r)
      std::cout << "Yes\n";
    else {
      int mid = (l + r) / 2;
      dfs(k << 1, l, mid);
      dfs(k << 1 | 1, mid + 1, r);
    }
  }
  dsu.back(lim);
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> n >> m >> K;
  for (int i = 1; i <= m; i++) {
    int l, r;
    std::cin >> X[i] >> Y[i] >> l >> r;
    l++;
    if (l <= r) modify(1, 1, K, l, r, i);
  }
  dsu.init(n + n);
  dfs(1, 1, K);
  return 0;
}

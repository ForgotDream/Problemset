#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N = 1e6 + 5;
int n, val[N];
int Lmin[N], Rmin[N], Lmax[N], Rmax[N];
int stk[N], top;
void init() {
  top = 0;
  for (int i = 1; i <= n; i++) {
    while (top && val[stk[top]] >= val[i]) top--;
    if (!top)
      Lmin[i] = 0;
    else
      Lmin[i] = stk[top] + 1;
    stk[++top] = i;
  }
  top = 0;
  for (int i = 1; i <= n; i++) {
    while (top && val[stk[top]] <= val[i]) top--;
    if (!top)
      Lmax[i] = 0;
    else
      Lmax[i] = stk[top] + 1;
    stk[++top] = i;
  }
  top = 0;
  for (int i = n; i >= 1; i--) {
    while (top && val[stk[top]] >= val[i]) top--;
    if (!top)
      Rmin[i] = n + 1;
    else
      Rmin[i] = stk[top] - 1;
    stk[++top] = i;
  }
  top = 0;
  for (int i = n; i >= 1; i--) {
    while (top && val[stk[top]] <= val[i]) top--;
    if (!top)
      Rmax[i] = n + 1;
    else
      Rmax[i] = stk[top] - 1;
    stk[++top] = i;
  }
}
struct BIT {
  int tree[N];
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(int u, int val) {
    for (int i = u; i < N; i += (i & -i)) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= (i & -i)) res += tree[i];
    return res;
  }
} bit;
int ans[N];
std::vector<int> S[N], Q;
inline void solve() {
  for (int i = 1; i <= n; i++) ans[i] = i - 1;
  bit.clear();
  for (int i = 1; i <= n; i++) {
    ans[i] -= i - 1 - bit.query(Lmin[i] - 1);
    bit.modify(Rmin[i], 1);
  }
  bit.clear();
  for (int i = 1; i <= n; i++) {
    ans[i] -= i - 1 - bit.query(Lmax[i] - 1);
    bit.modify(Rmax[i], 1);
  }
  Q.resize(n);
  for (int i = 0; i < n; i++) Q[i] = i + 1;
  std::sort(Q.begin(), Q.end(),
            [](auto x, auto y) { return Lmin[x] < Lmin[y]; });
  int l = 1, tot = n;
  bit.clear();
  for (int i = 1; i <= n; i++) bit.modify(Rmax[i], 1);
  for (int i = 1; i <= n; i++) S[i].clear();
  for (int i = 1; i <= n; i++) S[Rmin[i] + 1].push_back(i);
  for (int i = 0; i < n; i++) {
    while (l < Lmin[Q[i]]) {
      for (auto x : S[l]) bit.modify(Rmax[x], -1);
      tot -= S[l].size();
      l++;
    }
    ans[Q[i]] += tot - bit.query(Lmax[Q[i]] - 1) - (n - Q[i] + 1);
  }
}
int main() {
  freopen("interval.in", "r", stdin);
  freopen("interval.out", "w", stdout);
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int id;
  std::cin >> n >> id;
  for (int i = 1; i <= n; i++) std::cin >> val[i];
  std::reverse(val + 1, val + 1 + n);
  init();
  solve();
  std::reverse(ans + 1, ans + 1 + n);
  for (int i = 1; i <= n; i++) std::cout << ans[i] << ' ';
  std::cout << '\n';
  std::reverse(val + 1, val + 1 + n);
  init();
  solve();
  for (int i = 1; i <= n; i++) std::cout << ans[i] << ' ';
  std::cout << '\n';
  return 0;
}

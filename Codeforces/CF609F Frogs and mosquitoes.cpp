/**
 * @file    CF609F Frogs and mosquitoes.cpp
 * @author  ForgotDream
 * @brief   BST
 * @date    2023-10-25
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m;
i64 len[N], cnt[N];
struct Frog {
  i64 x, t;
  int id;
  Frog() = default;
  Frog(i64 x, i64 t, int id) : x(x), t(t), id(id) {}
  bool operator<(const Frog &rhs) const {
    return x < rhs.x || (x == rhs.x && t < rhs.t);
  }
} a[N];
std::vector<Frog> b;
std::multiset<pii> s;
int query(i64 pos) {
  int lo = 0, hi = b.size() - 1, res = -1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (b[mid].x + b[mid].t >= pos) res = mid, hi = mid - 1;
    else lo = mid + 1;
  }
  if (b[res].x <= pos && b[res].x + b[res].t >= pos) return res;
  else return -1;
}
void erase(int u) {
  while (u < b.size() - 1) {
    if (b[u].x + b[u].t >= b[u + 1].x + b[u + 1].t) b.erase(b.begin() + u + 1);
    else break;
  } 
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].x >> a[i].t;
    a[i].id = i, len[i] = a[i].t;
  }
  std::sort(a + 1, a + n + 1);
  for (int i = 1, p = 0; i <= n; i++) {
    if (a[i].x + a[i].t > p) {
      b.emplace_back(a[i]);
      p = a[i].x + a[i].t;
    }
  }
  for (int i = 1; i <= m; i++) {
    i64 pos, val;
    std::cin >> pos >> val;
    int res = query(pos);
    if (res != -1) {
      len[b[res].id] += val, b[res].t += val, cnt[b[res].id]++;
      while (!s.empty()) {
        auto it = s.lower_bound(std::make_pair(b[res].x, 0));
        if (it == s.end() || b[res].x + b[res].t < it->first) break;
        len[b[res].id] += it->second, b[res].t += it->second, cnt[b[res].id]++;
        s.erase(it);
      }
      erase(res);
    } else {
      s.emplace(pos, val);
    }
  }
  for (int i = 1; i <= n; i++) std::cout << cnt[i] << " " << len[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

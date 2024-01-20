#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 6e4 + 50;

int n, k, a[N][2], c[N];

std::vector<int> adj[N];
int bln[N], dfn[N], low[N], clk, cnt;
bool ins[N];
std::stack<int, std::vector<int>> s;

void tarjan(int u) {
  dfn[u] = low[u] = ++clk;
  s.push(u), ins[u] = true;
  for (auto v : adj[u]) {
    if (!dfn[v]) {
      tarjan(v), low[u] = std::min(low[u], low[v]);
    } else if (ins[v]) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    int p;
    ++cnt;
    do {
      p = s.top(), s.pop();
      bln[p] = cnt, ins[p] = false;
    } while (p != u);
  }
}

bool check(int u) {
  clk = cnt = 0;
  for (int i = 1; i <= 4 * n; i++) adj[i].clear(), bln[i] = dfn[i] = low[i] = 0;

  for (int i = 1; i <= n; i++) {
    adj[i + 2 * n].push_back(i + n);
    adj[i + n].push_back(i + 2 * n);
    adj[i + 3 * n].push_back(i);
    adj[i].push_back(i + 3 * n);

    for (int j = 1; j <= n; j++) {
      if (c[i] == c[j]) continue;
      if (std::abs(a[i][0] - a[j][0]) < u) {
        if (std::abs(a[i][0] - a[j][1]) < u) {
          adj[i + 2 * n].push_back(j);
          adj[i + 2 * n].push_back(j + n);
        } else {
          adj[i + 2 * n].push_back(j + 3 * n);
        }
      } else if (std::abs(a[i][0] - a[j][0]) >= u) {
        if (std::abs(a[i][0] - a[j][1]) < u) {
          adj[i + 2 * n].push_back(j + 2 * n);
        }
      }
      if (std::abs(a[i][1] - a[j][0]) < u) {
        if (std::abs(a[i][1] - a[j][1]) < u) {
          adj[i + 3 * n].push_back(j);
          adj[i + 3 * n].push_back(j + n);
        } else
          adj[i + 3 * n].push_back(i + 3 * n);
      } else if (std::abs(a[i][1] - a[j][0]) >= u) {
        if (std::abs(a[i][1] - a[j][1]) < u) {
          adj[i + 3 * n].push_back(j + 2 * n);
          adj[i + 3 * n].push_back(j + n);
        }
      }
    }
  }

  for (int i = 1; i <= 4 * n; i++) if (!dfn[i]) tarjan(i);
  for (int i = 1; i <= 2 * n; i++) if (bln[i] == bln[i + n * 2]) return false;
  return true;
}

void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i][0] >> a[i][1] >> c[i];

  int lo = 0, hi = 2e9, ans = 0;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) lo = mid + 1, ans = mid;
    else hi = mid - 1;
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

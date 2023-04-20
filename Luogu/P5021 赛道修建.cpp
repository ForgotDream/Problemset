/**
 * @file    P5021 赛道修建.cpp
 * @author  ForgotDream
 * @brief   二分
 * @date    2023-02-24
 */
#include <bits/stdc++.h>
#include <set>

using namespace std;
using i64 = long long;

static const int N = 5e4 + 50, M = 65, INF = 0x3f3f3f3f;
int n, m;
vector<pair<int, int>> e[N];
int sharedLen, ans;

inline void add(int u, int v, int w) {
  return (void) (e[u].emplace_back(v, w));
}

int dfs(int u, int from) {
  multiset<int> s;
  multiset<int>::iterator it;

  for (auto i : e[u]) {
    int v = i.first, w = i.second;
    if (v != from) {
      int tmp = dfs(v, u) + w;
      if (tmp >= sharedLen) {
        ans++;
      } else {
        s.insert(tmp);
      }
    }
  }

  int maxx = 0;
  while (!s.empty()) {
    it = s.begin();
    int cur = *it;
    
    s.erase(it);

    it = s.lower_bound(sharedLen - cur);
    if (it == s.end()) {
      maxx = cur;
    } else {
      s.erase(it);
      ans++;
    }
  }

  return maxx;
}

bool check(int mid) {
  sharedLen = mid;
  // cerr << mid << '\n';
  ans = 0;
  dfs(1, 0);
  return ans >= m;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1, u, v, w; i < n; i++) {
    cin >> u >> v >> w;
    add(u, v, w);
    add(v, u, w);
  }

  int l = 0, r = INF;
  while (l < r) {
    int mid = (l + r + 1) >> 1;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }

  cout << l << '\n';

  return 0;
}
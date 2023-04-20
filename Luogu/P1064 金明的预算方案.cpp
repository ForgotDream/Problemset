/**
 * @file    P1064 金明的预算方案.cpp
 * @author  ForgotDream
 * @brief   01背包
 * @date    2023-02-24
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 3.2e4 + 50, M = 65, INF = 0x3f3f3f3f;
int n, m;
int f[N], v[M], p[M], q[M];
vector<int> belong[M];

void update(int u, int v, int w) {
  if (u >= v) {
    f[u] = max(f[u], f[u - v] + w);
  }
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> v[i] >> p[i] >> q[i];
    if (q[i]) {
      belong[q[i]].push_back(i);
    }
  }

  for (int i = 1; i <= m; i++) {
    for (int j = n; j >= v[i] && !q[i]; j--) {
      update(j, v[i], v[i] * p[i]);

      if (belong[i].size() == 1) {
        int first = belong[i][0];

        update(j, v[i] + v[first], v[i] * p[i] + v[first] * p[first]);
      } else if (belong[i].size() == 2) {
        int first = belong[i][0], second = belong[i][1];

        update(j, v[i] + v[first], v[i] * p[i] + v[first] * p[first]);
        update(j, v[i] + v[second], v[i] * p[i] + v[second] * p[second]);
        update(j, v[i] + v[first] + v[second], v[i] * p[i] + v[first] * p[first] + v[second] * p[second]);
      }
    }
  }

  cout << f[n] << '\n';

  return 0;
}
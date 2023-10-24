/**
 * @file    CF438D The Child and Sequence.cpp
 * @author  ForgotDream
 * @brief   势能线段树
 * @date    2023-02-25
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, INF = 0x3f3f3f3f, MOD = 998244353;
int n, m;
i64 sum[N << 2], maxx[N << 2];
int a[N];

void pushup(int u) {
  return (void) (
    sum[u] = sum[u << 1] + sum[u << 1 | 1],
    maxx[u] = max(maxx[u << 1], maxx[u << 1 | 1])
  );
}

void build(int l, int r, int u) {
  if (l == r) {
    sum[u] = a[l];
    maxx[u] = a[l];
    return;
  }
  int lc = u << 1, rc = u << 1 | 1, mid = (l + r) >> 1;
  build(l, mid, lc);
  build(mid + 1, r, rc);
  pushup(u);
  return;
}

void update(int l, int r, int s, int t, int u, int val) {
  if (s == t) {
    sum[u] %= val;
    maxx[u] %= val;
    return;
  }
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  if (l <= mid && maxx[lc] >= val) {
    update(l, r, s, mid, lc, val);
  }
  if (r > mid && maxx[rc] >= val) {
    update(l, r, mid + 1, t, rc, val);
  }
  pushup(u);
  return;
}

void modify(int target, int s, int t, int u, int val) {
  if (s == target && t == target) {
    sum[u] = val;
    maxx[u] = val;
    return;
  }
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  if (target <= mid) {
    modify(target, s, mid, lc, val);
  } else {
    modify(target, mid + 1, t, rc, val);
  }
  pushup(u);
  return;
}

i64 query(int l, int r, int s, int t, int u) {
  if (l <= s && t <= r) {
    return sum[u];
  }
  i64 res = 0;
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  if (l <= mid) {
    res += query(l, r, s, mid, lc);
  }
  if (r > mid) {
    res += query(l, r, mid + 1, t, rc);
  }
  return res;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  build(1, n, 1);

  for (int i = 1; i <= m; i++) {
    int type, x, y, val;
    cin >> type;
    if (type == 1) {
      cin >> x >> y;
      cout << query(x, y, 1, n, 1) << '\n';
    } else if (type == 2) {
      cin >> x >> y >> val;
      update(x, y, 1, n, 1, val);
    } else {
      cin >> x >> val;
      modify(x, 1, n, 1, val);
    }
  }

  return 0;
}
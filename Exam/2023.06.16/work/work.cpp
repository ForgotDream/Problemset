#include <bits/stdc++.h>

using i64 = long long;

int main() {
  freopen("work.in", "r", stdin);
  freopen("work.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<i64> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  if (k >= n) {
    std::cout << std::accumulate(a.begin(), a.end(), 0ll) << "\n";
    return 0;
  }

  std::partial_sum(a.begin(), a.end(), a.begin());

  /* f[i][0] -> 不选, f[i][1] -> 选 */
  std::vector<std::vector<i64>> f(n, std::vector<i64>(2));

  std::deque<int> dq;
  f[0][0] = 0, f[0][1] = a[0], dq.push_back(0);
  for (int i = 1; i < k; i++) {
    f[i][0] = a[i - 1], f[i][1] = a[i];
    while (!dq.empty() && f[dq.back()][0] - a[dq.back()] < f[i][0] - a[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
  }

  for (int i = k; i < n; i++) {
    /* 若不选，则取上一个最大值 */
    f[i][0] = std::max(f[i - 1][0], f[i - 1][1]);
    /* 弹出 k 以外的，这是为了保证下边取的区间长度不超过 k */
    while (!dq.empty() && dq.front() < i - k) { dq.pop_front(); }
    /* 断言一下总不会错的 */
    assert(!dq.empty());
    f[i][1] = f[dq.front()][0] + a[i] - a[dq.front()];
    /* 使 f[i][0] - sum[i] 保持单调 */
    while (!dq.empty() && f[dq.back()][0] - a[dq.back()] < f[i][0] - a[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
  }

  std::cout << std::max(f[n - 1][0], f[n - 1][1]) << "\n";

  return 0;
}

/**
 * 不难发现，f[i][1] 是由前边的一段 f[j][0] 与 a[j + 1] ~ a[i] 的和构成
 * 于是我们可以使用单调队列来维护 f[i][0] - sum[i] 的值，sum 是前缀和
 */
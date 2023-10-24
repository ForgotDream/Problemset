#include <iostream>
#include <algorithm>

using i64 = long long;

constexpr int N = 3e5 + 50;
int N, f[N], s[N];
int max[N], semi[N], cpy[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; i++) {
    std::cin >> f[i] >> s[i];
    if (max[f[i]] < s[i]) semi[f[i]] = max[f[i]], max[f[i]] = s[i];
    else if (semi[f[i]] < s[i]) semi[f[i]] = s[i];
  }

  for (int i = 1; i <= N; i++) cpy[i] = max[i];
  std::sort(cpy + 1, cpy + N + 1);
  int ans = cpy[N] + cpy[N - 1];
  for (int i = 1; i <= N; i++) {
    ans = std::max(ans, max[i] + semi[i] / 2);
  }
  std::cout << ans << "\n";

  return 0;
}
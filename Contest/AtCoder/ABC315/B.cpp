#include <iostream>

using i64 = long long;

constexpr int N = 105;
int N, A[N], sum[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; i++) std::cin >> A[i], sum[i] = A[i] + sum[i - 1];

  int d = (sum[N] + 1) / 2;
  auto it = std::lower_bound(sum + 1, sum + N + 1, d);

  std::cout << it - sum << " " << d - *std::prev(it) << "\n";

  return 0;
}
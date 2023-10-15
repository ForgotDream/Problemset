#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, p[N];
std::vector<std::vector<int>> s;
bool vis[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    s.emplace_back(std::vector<int>());
    int pivot = p[i];
    while (pivot != i)
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}

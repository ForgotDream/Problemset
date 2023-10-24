#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;
  std::map<int, int> mp;
  for (int i = 0; i < n; i++) {
    int u;
    std::cin >> u;
    mp[u]++;
  }
  int pre = -1, prec = 0;
  for (auto i : mp) {
    int val = i.first, cnt = i.second;
    if (pre != -1) {
      if (val != pre + 1 || cnt > prec) {
        std::cout << "No\n";
        return;
      }
    } else if (val != 0) {
      std::cout << "No\n";
      return;
    }
    pre = val, prec = cnt;
  }
  std::cout << "Yes\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}

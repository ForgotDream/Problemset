#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::priority_queue<int> a, b;
  for (int i = 0; i < n; i++) {
    int cur;
    std::cin >> cur;
    a.push(cur);
  }
  for (int i = 0; i < m; i++) {
    int cur;
    std::cin >> cur;
    b.push(cur);
  }

  int cnt = 0;
  while (true) {
    if (a.empty() && b.empty()) {
      std::cout << "Draw\n";
      return;
    } else if (a.empty()) {
      std::cout << "Tenzing\n";
      return;
    } else if (b.empty()) {
      std::cout << "Tsondu\n";
      return;
    }
    int l = a.top(), r = b.top();
    if (cnt & 1) {
      std::swap(l, r);
    }
    a.pop(), b.pop();
    int tl = l, tr = r;
    l = tl - tr, r = tr - tl;
    if (l > 0) {
      (cnt & 1 ? b : a).push(l);
    }
    if (r > 0) {
      (cnt & 1 ? a : b).push(r);
    }
    cnt++;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;

struct Trie {
  std::vector<std::vector<int>> nxt;
  std::vector<int> a;

  Trie() {
    nxt.emplace_back(2);
    a.push_back(0);
    return;
  }

  void add(i64u num) {
    int pivot = 0;
    for (int i = 63; i >= 0; i--) {
      int d = !!(num & (1ll << i));
      if (!nxt[pivot][d]) {
        nxt.emplace_back(2);
        a.push_back(0);
        nxt[pivot][d] = nxt.size() - 1;
      }
      pivot = nxt[pivot][d];
      a[pivot]++;
    }
    a[pivot]++;
    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<i64u> a(n), b(n), c;
  Trie t1, t2;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    t1.add(a[i]);
  }
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
    t2.add(b[i]);
  }

  auto get = [&]() -> i64u {
    i64u res = 0;
    int p1 = 0, p2 = 0;
    for (int i = 63; i >= 0; i--) {
      if (t1.nxt[p1][0] && t2.nxt[p2][0] && t1.a[t1.nxt[p1][0]] && t2.a[t2.nxt[p2][0]]) {
        p1 = t1.nxt[p1][0], p2 = t2.nxt[p2][0];
      } else if (t1.nxt[p1][1] && t2.nxt[p2][1] && t1.a[t1.nxt[p1][1]] && t2.a[t2.nxt[p2][1]]) {
        p1 = t1.nxt[p1][1], p2 = t2.nxt[p2][1];
      } else if (t1.nxt[p1][0] && t2.nxt[p2][1] && t1.a[t1.nxt[p1][0]] && t2.a[t2.nxt[p2][1]]) {
        res += (1ll << i);
        p1 = t1.nxt[p1][0], p2 = t2.nxt[p2][1];
      } else {
        res += (1ll << i);
        p1 = t1.nxt[p1][1], p2 = t2.nxt[p2][0];
      }
      t1.a[p1]--, t2.a[p2]--;
    }
    t1.a[p1]--, t2.a[p2]--;
    return res;
  };

  for (int i = 0; i < n; i++) {
    c.push_back(get());
  }

  std::sort(c.begin(), c.end());

  for (int i = 0; i < n; i++) {
    std::cout << c[i] << " \n"[i == n - 1];
  }

  return 0;
}
/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-04-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}
}

struct ACAM {
  std::vector<std::vector<int>> tree;
  std::vector<int> end, fail;

  ACAM() {
    tree.emplace_back(26, 0);
    end.push_back(0), fail.push_back(0);
    return;
  }

  void insert(const std::string &s, const int &val) {
    int pivot = 0;

    for (int i = 0; i < s.length(); i++) {
      int d = s[i] - 'a';
      if (!tree[pivot][d]) {
        tree[pivot][d] = tree.size();
        tree.emplace_back(26, 0);
        end.push_back(0), fail.push_back(0);
      }
      pivot = tree[pivot][d];
    }
    end[pivot] += val;

    return;
  }

  void build() {
    static std::queue<int> q;
    for (int i = 0; i < 26; i++) {
      if (tree[0][i]) {
        q.push(tree[0][i]);
      }
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        int &v = tree[u][i];
        if (v) {
          if (u) {
            fail[v] = tree[fail[u]][i];
          }
          q.push(v);
        } else {
          v = tree[fail[u]][i];
        }
      }
    }
    return;
  }

  void solve(const int &l) {
    std::vector f(2, std::vector<int>(tree.size(), INT_MIN));
    f[0][0] = 0;
    int cur = 0;
    for (int i = 0; i < l; i++) {
      for (int j = 0; j < 26; j++) {
        for (int k = 0; k < tree.size(); k++) {
          int tmp = 0;
          for (int pivot = k; pivot; pivot = fail[pivot]) {
            tmp += end[pivot];
          }
          f[cur ^ 1][tree[k][j]] = std::max(f[cur ^ 1][tree[k][j]], f[cur][k] + tmp);
        }
      }
      for (int i = 0; i < tree.size(); i++) {
        f[cur][i] = INT_MIN;
      }
      cur ^= 1;
    }

    int ans = INT_MIN;
    for (int i = 0; i < tree.size(); i++) {
      ans = std::max(ans, f[cur][i]);
    }

    std::cout << ans << "\n";

    return;
  }

};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, l;
  std::cin >> n >> l;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  ACAM acam;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    acam.insert(s, a[i]);
  }

  acam.build();
  acam.solve(l + 1);

  return 0;
}
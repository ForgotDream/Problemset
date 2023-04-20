/**
 * @file    P2730 Magic Squares.cpp
 * @author  ForgotDream
 * @brief   康托展开 + BFS
 * @date    2023-03-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int cantor(std::vector<int> a) {
  int res = 0;
  static std::vector<int> fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
  
  for (int i = 0; i < 8; i++) {
    int cnt = 0;
    for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) {
        cnt++;
      }
    }
    res += fact[8 - i] * (a[i] - cnt - 1);
  }

  return res;
}

std::vector<int> sub(int rnk) {
  std::vector<int> ans, rest(8);
  static std::vector<int> fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
  std::iota(rest.begin(), rest.end(), 1);

  for (int i = 0; i < 8; i++) {
    int tmp = rnk / fact[8 - i];
    ans.push_back(rest[tmp]);
    rest.erase(rest.begin() + tmp);
    rnk -= tmp * fact[8 - i];
  }

  return ans;
}

int convert(int cur, int opt) {
  auto s = sub(cur);
  
  if (opt == 0) {
    for (int i = 0; i < 4; i++) {
      std::swap(s[i], s[i + 4]);
    }
  } else if (opt == 1) {
    int t1 = s[3], t2 = s[7];
    for (int i = 8; i > 0; i--) {
      s[i] = s[i - 1];
    }
    s[0] = t1, s[4] = t2;
  } else {
    int t = s[5];
    s[5] = s[6], s[6] = s[2], s[2] = s[1], s[1] = t;
  }

  return cantor(s);
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::queue<int> q;
  int s = cantor({1, 2, 3, 4, 8, 7, 6, 5});
  
  std::vector<int> tmp(8);
  for (int i = 0; i < 4; i++) {
    std::cin >> tmp[i];
  }
  for (int i = 7;i >= 4; i--) {
    std::cin >> tmp[i];
  }
  int t = cantor(tmp);

  if (s == t) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::unordered_map<int, int> dis;
  std::unordered_map<int, std::pair<int, int>> pre;
  dis[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 3; i++) {
      int v = convert(u, i);
      if (dis.count(v)) {
        continue;
      }
      
      dis[v] = dis[u] + 1;
      pre[v] = std::make_pair(u, 'A' + i);
      
      if (v == t) {
        int pivot = v;
        std::stack<char> st;

        while (pivot != s) {
          st.push(pre[pivot].second);
          pivot = pre[pivot].first;
        }

        std::cout << dis[v] << "\n";
        while (!st.empty()) {
          std::cout << st.top();
          st.pop();
        }
        std::cout << "\n";

        return 0;
      }

      q.push(v);
    }
  }

  return 0;
}
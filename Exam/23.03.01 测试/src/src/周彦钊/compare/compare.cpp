#include <bits/stdc++.h>

using i64 = long long;
using vdb = std::vector<long double>;

static const long double INF = 1e18;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(0);
  
  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<vdb> e(n + 1, vdb(n + 1, INF));
  for (int i = 1; i <= n; i++) {
    e[i][i] = 0;
  }
  
  for (int i = 1; i <= m; i++) {
    int u, v;
    long double w;
    // read(u);
    // read(v);
    // scanf("%llf", &w);
    std::cin >> u >> v >> w;
    e[u][v] = std::min(e[u][v], w);
    e[v][u] = e[u][v];
  }
  
  std::cin.get();
  
  long double ans = INF;
  for (int i = 1; i <= k; i++) {
    std::vector<int> path;
    std::string s;
    
    std::getline(std::cin, s);
    
    if (s[s.length() - 1] == ' ') {
      s = s.substr(0, s.length() - 1);
    }
    
    int cnt = 0, len = s.length();
    bool isBad = false;
    for (int i = 0; i <= len; i++) {
      if (i != len && !isdigit(s[i]) && s[i] != ' ') {
        isBad = true;
        break;
      }
      if (i == len || s[i] == ' ') {
        if (path.empty() || cnt != *(path.end() - 1)) {
          path.push_back(cnt);
        }
        cnt = 0;
      } else {
        cnt = cnt * 10 + s[i] - '0';
      }
    }
    
    if (isBad) {
      continue;
    } 
    
    if (path[0] != 1 || *(path.end() - 1) != n) {
      continue;
    }
    
    int lst = path[0], cur = 0;
    long double curAns = 0;
    bool flg = true;
    for (int i = 1; i < path.size(); i++) {
      cur = path[i];
      if (cur > n || cur < 1 || e[lst][cur] == INF) {
        flg = false;
        break;
      }
      curAns += e[lst][cur];
      lst = cur;
    }
    
    if (!flg) {
      continue;
    }
    
    ans = std::min(curAns, ans);
  }
  
  if (ans == INF) {
    std::cout << "Wrong" << "\n";
  } else {
    std::cout << std::fixed << std::setprecision(4) << ans << "\n";
  }
  return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using i64 = long long;

constexpr i64 mod = 1e9 + 7;
int n;
std::string s;
int ans = 0;
std::vector<int> p;
namespace N_LESS_THAN_20 {
void bfs(const std::string &s) {
  std::queue<std::string> q;
  std::map<std::string, bool> used;
  used[s] = true;
  q.push(s);
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    ans++;
    std::string nxt;
    for (int i = 1; i + 1 < n; i++) {
      if (p[i - 1] == '0' && p[i] == '1' && p[i + 1] == '1') {
        nxt = p;
        std::swap(nxt[i - 1], nxt[i + 1]);
        if (used[nxt]) continue;
        used[nxt] = true, q.push(nxt);
      }
      if (p[i - 1] == '1' && p[i] == '1' && p[i + 1] == '0') {
        nxt = p;
        std::swap(nxt[i - 1], nxt[i + 1]);
        if (used[nxt]) continue;
        used[nxt] = true, q.push(nxt);
      }
    }
  }
}
void solve() {
  for (int i = 0; i < (1 << p.size()); i++) {
    std::string cur = s;
    for (int j = 0; j < p.size(); j++) {
      if (i & (1 << j)) cur[p[j]] = '1';
      else cur[p[j]] = '0';
    }
    bfs(cur);
  }
  std::cout << ans;
}
}
void solve() {
  std::cin >> n >> s;
  for (int i = 0; i < n; i++) {
    if (s[i] == '?') p.push_back(i);
  }
  int len = p.size();
  if (n <= 20 && len <= 5) N_LESS_THAN_20::solve();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
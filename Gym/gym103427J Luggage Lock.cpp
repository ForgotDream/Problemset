/**
 * @file    gym103427J Luggage Lock.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-10-07
 */
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 1e4;
bool vis[N];
short dis[N];
int a, b;
int encode(const std::vector<int> &code) {
  int res = 0;
  for (int i = 0; i < 4; i++) res = res * 10 + code[i];
  return res;
}
std::vector<int> decode(int code) {
  std::vector<int> res(4);
  for (int i = 3; i >= 0; i--) res[i] = code % 10, code /= 10;
  return res;
}
void init() {
  std::queue<int> q;
  q.push(0), vis[0] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    auto cur = decode(u);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j <= i; j++) {
        for (int k : {1, -1}) {
          auto tmp = cur;
          for (int l = j; l <= i; l++) tmp[l] = (tmp[l] + k + 10) % 10;
          int nxt = encode(tmp);
          if (vis[nxt]) continue;
          q.push(nxt), vis[nxt] = true;
          dis[nxt] = dis[u] + 1;
        }
      }
    }
  }
}
void solve() {
  std::cin >> a >> b;
  auto va = decode(a), vb = decode(b);
  decltype(va) vc(4);
  for (int i = 0; i < 4; i++) vc[i] = (va[i] - vb[i] + 10) % 10;
  std::cout << dis[encode(vc)] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  init();
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}

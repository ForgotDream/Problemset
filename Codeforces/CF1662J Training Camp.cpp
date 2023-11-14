/**
 * @file    CF1662J Training Camp.cpp
 * @author  ForgotDream
 * @brief   Maximum Flow + Minimum Cut
 * @date    2023-11-05
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

#pragma region
struct FastIO {
  static constexpr signed bufsize = 1 << 18;
  char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
  char outbuf[bufsize], *pp = outbuf;
  ~FastIO() { flush(); }
  inline char gc() {
    if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
    return p1 == p2 ? EOF : *p1++;
  }
  template <typename T>
  inline void read(T &x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (c < '0' || c > '9') f = ( c == '-' ? -f : f), c = gc();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
    x *= f;
  }
  inline void read(char *s) {
    char c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
    while (c != ' ' && c != '\n' && c != '\r') *s++ = c, c = gc();
  }
  inline void read(char &c) {
    c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
  }
  inline void read(std::string &s) {
    std::string().swap(s);
    char c = gc();
    while (c == ' ' || c == '\n' || c == '\r') c = gc();
    while (c != ' ' && c != '\n' && c != '\r') s += c, c = gc();
  }
  template <typename T = int>
  inline T read() {
    T res;
    read(res);
    return res;
  }
  inline void pc(const char &c) {
    if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
    *pp++ = c;
  }
  template <typename T>
  inline void print(T x) {
    if (x < 0) x = -x, pc('-');
    static T sta[35];
    T top = 0;
    do sta[top++] = x % 10, x /= 10; while (x);
    while (top) pc(sta[--top] + '0');
  }
  inline void print(const char *s) { for (; *s; ++s) pc(*s); }
  inline void print(char *s) { for (; *s; ++s) pc(*s); }
  inline void print(const std::string &s) { for (const auto &c : s) pc(c); }
  inline void print(const char &c) { pc(c); }
  inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
  template <typename T>
  FastIO &operator>>(T &rhs) { return read(rhs), *this; }
  FastIO &operator>>(char *rhs) { return read(rhs), *this; }
  template <typename T>
  FastIO &operator<<(const T &rhs) { return print(rhs), *this; }
} fin, fout;
#pragma endregion

using i64 = long long;

constexpr int N = 1e5 + 50, M = 250;
int n, a[M][M], p[M][M], r[M][M], c[M][M];
struct Dinic {
  struct Edge {
    int u, v, flow, cap;
    Edge(int _u = 0, int _v = 0, int _c = 0) {
      u = _u, v = _v, cap = _c, flow = 0;
    }
  };
  int s, t;
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int dis[N], cur[N];
  bool vis[N];
  Dinic() = default;
  void addEdge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }
  bool bfs() {
    std::memset(vis, 0, sizeof(vis));
    std::memset(cur, 0, sizeof(cur));
    std::queue<int> q;
    dis[s] = 0, vis[s] = true, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, flow, cap] = edges[i];
        if (!vis[v] && cap > flow) {
          vis[v] = true, dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }
    return vis[t];
  }
  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;
    int res = 0;
    for (int &i = cur[u], f; i < adj[u].size(); i++) {
      auto &[_, v, flow, cap] = edges[adj[u][i]];
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        res += f, lim -= f;
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }
    return res;
  }
  int maxFlow(int s, int t) {
    this->s = s, this->t = t;
    int res = 0;
    while (bfs()) res += dfs(s, 0x3f3f3f3f);
    return res;
  }
} solver;
inline int enc(int i, int j) { return (i - 1) * n + j; }
void solve() {
  fin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      fin >> a[i][j];
      r[i][a[i][j]] = j, c[j][a[i][j]] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) fin >> p[i][j];
  }
  int s = 0, t = 2 * n * n + 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      solver.addEdge(enc(i, j) + n * n, enc(i, j), 2 * n + 1 - p[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (a[i][j] == 1) solver.addEdge(s, enc(i, j) + n * n, 1e9);
      if (a[i][j] < n) {
        solver.addEdge(enc(i, j), enc(i, r[i][a[i][j] + 1] + n * n), 1e9);
        solver.addEdge(enc(i, j), enc(c[j][a[i][j] + 1], j + n * n), 1e9);
      } else {
        solver.addEdge(enc(i, j), t, 1e9);
      }
    }
  }
  fout << 2 * n * n + n - solver.maxFlow(s, t) << "\n";
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

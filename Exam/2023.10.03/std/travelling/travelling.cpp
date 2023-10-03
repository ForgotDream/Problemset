#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 5;
struct Edge {
  int to, id, next;
  bool f;
} edges[maxn << 4];
int tot, head[maxn], cnt;
bool vis[maxn];
vector<int> res[maxn];
int deg[maxn];

void init() {
  tot = 0;
  cnt = 0;
  memset(deg, 0, sizeof(deg));
  memset(vis, 0, sizeof(vis));
  memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, int id) {
  edges[tot].f = 0;
  edges[tot].to = v;
  edges[tot].id = id;
  edges[tot].next = head[u];
  head[u] = tot++;
}

void dfs(int u) {
  vis[u] = true;
  for (int i = head[u]; ~i; i = edges[i].next) {
    int v = edges[i].to, id = edges[i].id;
    if (!edges[i].f) {
      edges[i].f = edges[i ^ 1].f = true;  // 将边和反向边标记
      dfs(v);
      if (id)
        res[cnt].push_back(-id);  // 退栈记录边的id
      else
        cnt++;  // 扫到虚边，那么路径加1
    }
  }
}

void Print() {
  printf("%d\n", cnt - 1);
  for (int i = 1; i <= cnt; ++i) {
    printf("%d", res[i].size());
    int k = res[i].size();
    for (int j = 0; j < k; ++j) printf(" %d", res[i][j]);
    printf("\n");
    res[i].clear();
  }
}

int main() {
  freopen("travelling.in", "r", stdin);
  freopen("travelling.out", "w", stdout);
  int T, N, M, u, v, tmp;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);
    init();
    for (int i = 1; i <= M; ++i) {
      scanf("%d%d", &u, &v);
      deg[u]++, deg[v]++;
      AddEdge(u, v, i);
      AddEdge(v, u, -i);
    }
    u = 0;
    for (int i = 1; i <= N; ++i) {
      if (deg[i] & 1) {
        if (u) {
          AddEdge(u, i, 0);
          AddEdge(i, u, 0);
          u = 0;
        }  // 将奇度数点两两连边
        else
          u = i;
      }
    }
    for (int i = 1; i <= N; ++i) {
      if (!vis[i] && (deg[i] & 1)) {
        cnt++;
        dfs(i);
        cnt--;
      }
    }
    for (int i = 1; i <= N; ++i) {
      if (!vis[i] && deg[i]) {
        cnt++;
        dfs(i);
      }
    }
    Print();
  }
  return 0;
}

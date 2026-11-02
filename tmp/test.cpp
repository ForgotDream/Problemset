#include <bits/stdc++.h>
// #include "thief.h"
using namespace std;

struct ThiefSolver {
  int n, m, timer = 0;
  vector<int> U, V, stamp, par, sub, treeEdges;
  vector<char> isTree;
  vector<vector<pair<int, int>>> tree;

  // group[d][e]: 第 d 层中边 e 所属的组
  // inward[d][e]: 边 e 指向当前重心时的方向
  vector<vector<signed char>> group, inward;

  void split(const vector<int> &edges, int depth) {
    if (edges.empty())
      return;

    // 单边子问题无需继续分解
    if (edges.size() == 1 && depth > 0)
      return;

    if ((int)group.size() <= depth) {
      group.emplace_back(m, -1);
      inward.emplace_back(m, -1);
    }

    if (edges.size() == 1) {
      int e = edges[0];
      group[depth][e] = 0;
      inward[depth][e] = 1;
      return;
    }

    int mark = ++timer;
    for (int e : edges)
      stamp[e] = mark;

    // 遍历当前子树
    vector<int> order;
    int root = U[edges[0]];
    par[root] = -1;
    order.push_back(root);

    for (int k = 0; k < (int)order.size(); ++k) {
      int v = order[k];
      for (auto [w, e] : tree[v]) {
        if (stamp[e] == mark && w != par[v]) {
          par[w] = v;
          order.push_back(w);
        }
      }
    }

    // 计算子树大小
    for (int v : order)
      sub[v] = 1;
    for (int k = (int)order.size() - 1; k >= 0; --k) {
      int v = order[k];
      if (par[v] != -1)
        sub[par[v]] += sub[v];
    }

    // 寻找重心
    int c = -1, best = INT_MAX;
    for (int v : order) {
      int worst = (int)order.size() - sub[v];

      for (auto [w, e] : tree[v])
        if (stamp[e] == mark && par[w] == v)
          worst = max(worst, sub[w]);

      if (worst < best) {
        best = worst;
        c = v;
      }
    }

    // 从重心出发，收集所有分支
    vector<vector<int>> branches;

    for (auto [w, e] : tree[c]) {
      if (stamp[e] != mark)
        continue;

      vector<int> br;
      vector<array<int, 3>> st;
      st.push_back({w, c, e});

      while (!st.empty()) {
        auto [v, p, ei] = st.back();
        st.pop_back();

        br.push_back(ei);

        // 从 v 指向父节点 p
        inward[depth][ei] = (U[ei] == v ? 0 : 1);

        for (auto [to, ej] : tree[v]) {
          if (stamp[ej] == mark && to != p)
            st.push_back({to, v, ej});
        }
      }
      branches.push_back(move(br));
    }

    // 把分支划分成至多三组
    vector<vector<int>> child(3);
    int half = ((int)edges.size() + 1) / 2;
    int sum = 0, stage = 0;

    for (auto &br : branches) {
      int g;

      if (stage == 0 && sum + (int)br.size() <= half) {
        g = 0;
        sum += br.size();
      } else if (stage == 0) {
        g = 1;
        stage = 2;
      } else {
        g = 2;
      }

      for (int e : br) {
        group[depth][e] = g;
        child[g].push_back(e);
      }
    }

    // 所有子问题并行进入下一层
    for (auto &g : child)
      if (!g.empty())
        split(g, depth + 1);
  }

  // 构造一次完整图的 DAG 定向及其拓扑序
  pair<vector<int>, vector<int>> make_query(int depth, int t) {
    vector<int> x(m, 0), indeg(n), topo, pos(n);

    // 先给生成树定向
    for (int e : treeEdges) {
      if (group[depth][e] >= 0) {
        x[e] = (group[depth][e] == t ? inward[depth][e] : 1 - inward[depth][e]);
      }
    }

    // 计算生成树定向后的拓扑序
    for (int e : treeEdges) {
      int to = x[e] ? U[e] : V[e];
      ++indeg[to];
    }

    queue<int> q;
    for (int v = 0; v < n; ++v)
      if (!indeg[v])
        q.push(v);

    while (!q.empty()) {
      int v = q.front();
      q.pop();

      pos[v] = topo.size();
      topo.push_back(v);

      for (auto [w, e] : tree[v]) {
        if ((!x[e] && U[e] == v) || (x[e] && V[e] == v)) {
          if (--indeg[w] == 0)
            q.push(w);
        }
      }
    }

    // 非树边一律沿拓扑序正向连接
    for (int e = 0; e < m; ++e) {
      if (!isTree[e])
        x[e] = (pos[U[e]] > pos[V[e]]);
    }

    return {move(x), move(topo)};
  }

  void run(int N, int M, vector<int> a, vector<int> b) {
    n = N;
    m = M;
    U = move(a);
    V = move(b);

    isTree.assign(m, 0);
    stamp.assign(m, 0);
    par.resize(n);
    sub.resize(n);
    tree.resize(n);

    // 构造任意生成树
    vector<vector<pair<int, int>>> g(n);
    for (int e = 0; e < m; ++e) {
      g[U[e]].push_back({V[e], e});
      g[V[e]].push_back({U[e], e});
    }

    vector<char> seen(n, 0);
    vector<int> q{0};
    seen[0] = 1;

    for (int i = 0; i < (int)q.size(); ++i) {
      int v = q[i];
      for (auto [w, e] : g[v]) {
        if (seen[w])
          continue;

        seen[w] = 1;
        q.push_back(w);
        isTree[e] = 1;
        treeEdges.push_back(e);

        tree[v].push_back({w, e});
        tree[w].push_back({v, e});
      }
    }

    // 预处理分治
    split(treeEdges, 0);

    // 第一阶段：寻找一次返回 1 的询问
    vector<int> base, topo;
    bool ok = false;

    for (int d = 0; d < (int)group.size() && !ok; ++d) {
      for (int t = 0; t < 3; ++t) {
        auto [x, p] = make_query(d, t);

        if (query(x)) {
          base = move(x);
          topo = move(p);
          ok = true;
          break;
        }
      }
    }

    assert(ok);

    // 第二阶段：在成功定向的拓扑序上二分
    vector<int> pos(n);
    for (int i = 0; i < n; ++i)
      pos[topo[i]] = i;

    auto check = [&](int l, int r) {
      vector<int> x = base;

      for (int e = 0; e < m; ++e) {
        bool inside = l <= pos[U[e]] && pos[U[e]] <= r && l <= pos[V[e]] &&
                      pos[V[e]] <= r;

        if (!inside)
          x[e] ^= 1;
      }

      return query(move(x));
    };

    // 后缀询问：确定 A
    int l = 0, r = n - 1;
    while (l < r) {
      int mid = (l + r + 1) / 2;

      if (check(mid, n - 1))
        l = mid;
      else
        r = mid - 1;
    }
    int A = topo[l];

    // 前缀询问：确定 B
    l = 0;
    r = n - 1;
    while (l < r) {
      int mid = (l + r) / 2;

      if (check(0, mid))
        r = mid;
      else
        l = mid + 1;
    }
    int B = topo[l];

    answer(A, B);
  }
};

void solve(int n, int m, vector<int> u, vector<int> v) {
  ThiefSolver solver;
  solver.run(n, m, move(u), move(v));
}

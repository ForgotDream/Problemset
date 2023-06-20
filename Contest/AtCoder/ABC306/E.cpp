#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 6e5;
struct Treap {
  int val[N], prm[N], ch[N][2], size[N];
  i64 sum[N];
  int cnt, root;
  Treap() { root = 0; };
  void init(int u) {
    val[++cnt] = u, prm[cnt] = rand(), sum[cnt] = u;
    ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1;
    return;
  }
  void update(int u) {
    size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
    sum[u] = sum[ch[u][0]] + sum[ch[u][1]] + val[u];
    return;
  }
  void rotate(int &u, int d) {
    int k = ch[u][d];
    ch[u][d] = ch[k][d ^ 1];
    ch[k][d ^ 1] = u;
    size[k] = size[u];
    update(u), u = k;
    return;
  }
  void insert(int &u, int x) {
    if (!u) return (void)(init(x), u = cnt);
    size[u]++;
    if (x >= val[u]) insert(ch[u][1], x);
    else insert(ch[u][0], x);
    if (ch[u][0] && prm[u] > prm[ch[u][0]]) rotate(u, 0);
    if (ch[u][1] && prm[u] > prm[ch[u][1]]) rotate(u, 1);
    update(u);
    return;
  }
  void del(int &u, int x) {
    size[u]--;
    if (val[u] == x) {
      if (!ch[u][0] && !ch[u][1]) 
        return (void)(u = 0);
      if (!ch[u][0] || !ch[u][1]) 
        return (void)(u = ch[u][0] + ch[u][1]);
      if (prm[ch[u][0]] < prm[ch[u][1]]) 
        return (void)(rotate(u, 0), del(ch[u][1], x));
      else (void)(rotate(u, 1), del(ch[u][0], x));
    } else {
      if (val[u] >= x) del(ch[u][0], x);
      else del(ch[u][1], x);
      update(u);
      return;
    }
  }
  int getNumByRank(int u, int x, i64 &sum) {
    if (x == size[ch[u][0]] + 1) 
      return val[u];
    if (x > size[ch[u][0]] + 1) {
      return getNumByRank(ch[u][1], x - size[ch[u][0]] - 1, sum);
    }
    return getNumByRank(ch[u][0], x, sum);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k, q;
  std::cin >> n >> k >> q;
  int d = n - k + 1;

  std::vector<int> a(n);
  FHQTreap<i64> fhq;
  for (int i = 0; i < n; i++) { fhq.insert(0); }

  for (int i = 0; i < q; i++) {
    int opt, val;
    std::cin >> opt >> val;
    opt--;
    fhq.erase(a[opt]);
    a[opt] = val;
    fhq.insert(a[opt]);
    i64 sum = 0;
    fhq.getNumByRank(fhq.root, d, sum);
    std::cerr << sum << "\n";
    std::cout << fhq.tree[fhq.root].sum - sum << "\n";
  }

  return 0;
}
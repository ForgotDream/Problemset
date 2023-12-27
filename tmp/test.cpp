#include <bits/stdc++.h>
using namespace std;
const int mod = 201314;

int n, m;
vector<int> to[50005];
int deep[50005];

const int siz = 500;
int belong[50005];
int query[105][50005];
int block[105];

int first[100005];
int st[200005][18];
int lg2[100005];
int cnt = 0;

void dfs_init(int now) {
  st[++cnt][0] = deep[now];
  first[now] = cnt;
  for (auto next : to[now]) {
    deep[next] = deep[now] + 1;
    dfs_init(next);
    st[++cnt][0] = deep[now];
  }
}

int bin[50005];
void dfs1(int now) {
  for (auto next : to[now]) dfs1(next), bin[now] += bin[next];
}
void dfs2(int now, int dist) {
  for (auto next : to[now]) dfs2(next, dist + bin[now]);
  bin[now] += dist;
}

void init() {
  dfs_init(1);
  for (int i = 1; i <= n; i++) {
    belong[i] = i / siz + 1;
    if (belong[i] - belong[i - 1]) block[belong[i]] = i;
  }
  for (int i = 2; i <= (n << 1); i++) lg2[i] = lg2[i >> 1] + 1;
  for (int t = 1; t <= 17; t++)
    for (int i = 1; i <= (n << 1) - (1 << t); i++)
      st[i][t] = min(st[i][t - 1], st[i + (1 << (t - 1))][t - 1]);
}

int LCA(int A, int B) {
  A = first[A];
  B = first[B];
  if (A > B) swap(A, B);
  int ln = lg2[B - A + 1];
  return min(st[A][ln], st[B - (1 << ln) + 1][ln]);
}

int main() {
  cin >> n >> m;
  deep[1] = 1;
  for (int i = 2; i <= n; i++) {
    int v;
    cin >> v;
    v++;
    to[v].push_back(i);
  }
  init();
  belong[0] = 0;
  belong[n + 1] = belong[n] + 1;
  block[0] = 0;
  block[belong[n + 1]] = n + 1;
  for (int i = 1; i <= belong[n]; i++) {
    memset(bin, 0, sizeof(bin));
    for (int j = block[i]; belong[j] == i; j++) bin[j]++;
    dfs1(1);
    dfs2(1, 0);
    for (int j = 1; j <= n; j++) query[i][j] = bin[j];
  }
  while (m--) {
    int l, r, x;
    cin >> l >> r >> x;
    l++;
    r++;
    x++;
    int bl = belong[l - 1] + 1;
    int br = belong[r + 1] - 1;
    long long ans = 0;
    for (; belong[l] != bl and l <= r; l++) ans += LCA(l, x);
    for (; belong[r] != br and r >= l; r--) ans += LCA(r, x);
    for (int i = bl; i <= br; i++) ans += query[i][x];
    cout << ans % mod << "\n";
  }
  return 0;
}
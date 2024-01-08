/*
 * Author: Kewth

 * Date:
  2021.01.11

 * Solution:

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
  inline operator int() {
    int x;
    return scanf("%d", &x), x;
  }
  template <class T> inline void operator()(T &x) { x = *this; }
} read;

const int maxn = 3005, mod = 1000000007;
std::vector<int> G[maxn];
ll tmp[maxn], Mod = 1ll * mod * mod;

inline ll power(ll x, int k) {
  if (k < 0)
    k += mod - 1;
  ll res = 1;
  while (k) {
    if (k & 1)
      (res *= x) %= mod;
    (x *= x) %= mod;
    k >>= 1;
  }
  return res;
}

struct Bag {
  int w[maxn], sz;
};
void operator*=(Bag &a, const Bag &b) {
  for (int i = 0; i <= a.sz + b.sz; i++)
    tmp[i] = 0;
  for (int i = 0; i <= a.sz; i++)
    for (int j = 0; j <= b.sz; j++)
      if ((tmp[i + j] += 1ll * a.w[i] * b.w[j]) >= Mod)
        tmp[i + j] %= Mod;
  a.sz += b.sz;
  for (int i = 0; i <= a.sz; i++)
    a.w[i] = tmp[i] % mod;
}
void operator/=(Bag &a, const Bag &b) {
  for (int i = 0; i <= a.sz; i++)
    tmp[i] = a.w[i], a.w[i] = 0;
  a.sz -= b.sz;
  ll inv = power(b.w[b.sz], -1);
  for (int i = a.sz; i >= 0; i--) {
    a.w[i] = inv * tmp[i + b.sz] % mod;
    for (int j = 0; j <= b.sz; j++)
      (tmp[i + j] += 1ll * (mod - a.w[i]) * b.w[j]) %= mod;
  }
}
void operator+=(Bag &a, const Bag &b) {
  for (int i = 0; i <= b.sz; i++)
    if ((a.w[i] += b.w[i]) >= mod)
      a.w[i] -= mod;
  if (b.sz > a.sz)
    a.sz = b.sz;
}
void operator-=(Bag &a, const Bag &b) {
  for (int i = 0; i <= b.sz; i++)
    if ((a.w[i] -= b.w[i]) < 0)
      a.w[i] += mod;
  while (a.sz and a.w[a.sz] == 0)
    --a.sz;
}

Bag mul[maxn], sum[maxn], f[maxn];
int val[maxn];

void dp(int u, int fa) {
  mul[u].w[1] = val[u];
  mul[u].sz = 1;
  for (int v : G[u])
    if (v != fa) {
      dp(v, u);
      mul[u] *= f[v];
      sum[u] += f[v];
    }
  for (int i = 0; i <= mul[u].sz; i++) std::cerr << mul[u].w[i] << " \n"[i == mul[u].sz];
  (f[u] = mul[u]) += sum[u], f[u].w[0] = 1;
  /* for (int i = 1; i <= f[u].sz; i ++) */
  /* 	debug(" %d", f[u].w[i]); */
  /* debug(" -> %d\n", u); */
}

int ans[maxn][maxn];
void rdp(int u, int fa) {
  mul[u] *= f[fa];
  sum[u] += f[fa];
  (f[u] = mul[u]) += sum[u], f[u].w[0] = 1;
  ll ans0 = 0;
  for (int i = 1; i <= f[u].sz; i++)
    ans0 += (ans[u][i] = f[u].w[i]);
  ans[u][0] = ans0 % mod;
  /* for (int i = 0; i <= f[u].sz; i ++) */
  /* 	debug(" %d", ans[u][i]); */
  /* debug(" -> %d\n", u); */
  Bag _mul = mul[u], _sum = sum[u];
  for (int v : G[u])
    if (v != fa) {
      mul[u] = _mul, sum[u] = _sum;
      mul[u] /= f[v];
      sum[u] -= f[v];
      (f[u] = mul[u]) += sum[u], f[u].w[0] = 1;
      rdp(v, u);
    }
}

int main() {
  int n = read;
  for (int i = 1; i <= n; i++)
    read(val[i]);
  for (int i = 1; i < n; i++) {
    int u = read, v = read;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  f[0].w[0] = 1;
  dp(1, 0);
  /* debug("---\n"); */
  rdp(1, 0);
  int q = read;
  while (q--) {
    int u = read, x = read;
    printf("%d\n", ans[u][x]);
  }
}

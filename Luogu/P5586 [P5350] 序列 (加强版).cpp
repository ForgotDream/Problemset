/*
 * @file    P5586 [P5350] 序列 (加强版).cpp
 * @author  ForgotDream
 * @brief   FHQ
 * @date    2023-12-20
 */
#include <bits/stdc++.h>

#pragma region
namespace FastIO {
static constexpr signed bufsize = 1 << 20;
struct is {
  char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
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
  template <typename T>
  is &operator>>(T &rhs) { return read(rhs), *this; }
  is &operator>>(char *rhs) { return read(rhs), *this; }
};
struct os {
  char outbuf[bufsize], *pp = outbuf;
  ~os() { flush(); }
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
  os &operator<<(const T &rhs) { return print(rhs), *this; }
};
}  // namespace FastIO
FastIO::is fin;
FastIO::os fout;
#pragma endregion

using i64 = long long;

constexpr int N = 8e6 + 50, mod = 1e9 + 7;
int n, m;

struct FHQ {
  std::random_device rd;
  std::mt19937 rng;
  int lc[N], rc[N], prm[N], siz[N];
  int val[N], sum[N], add[N], ass[N];
  bool rev[N];
  FHQ() : rng(std::mt19937(rd())) { ass[0] = -1; }
  int cnt, rt;
  int stk[N], top;
  inline int init(int v) {
    cnt++, lc[cnt] = rc[cnt] = 0, prm[cnt] = rng(), siz[cnt] = 1;
    val[cnt] = sum[cnt] = v;
    ass[cnt] = -1, add[cnt] = 0, rev[cnt] = false;
    return cnt;
  }
  inline int clone(int u) {
    cnt++, lc[cnt] = lc[u], rc[cnt] = rc[u], prm[cnt] = prm[u], siz[cnt] = siz[u];
    val[cnt] = val[u], sum[cnt] = sum[u];
    ass[cnt] = ass[u], add[cnt] = add[u], rev[cnt] = rev[u];
    return cnt;
  }
  inline void tagAss(int u, int v) {
    if (!u) return;
    val[u] = v, sum[u] = 1ll * siz[u] * v % mod, ass[u] = v, add[u] = 0;
  }
  inline void tagAdd(int u, int v) {
    if (!u) return;
    val[u] = (val[u] + v) % mod, sum[u] = (sum[u] + 1ll * siz[u] * v % mod) % mod;
    add[u] = (add[u] + v) % mod;
  }
  inline void tagRev(int u) { 
    if (!u) return;
    std::swap(lc[u], rc[u]), rev[u] ^= true; 
  }
  inline void pushup(int u) {
    siz[u] = siz[lc[u]] + siz[rc[u]] + 1;
    sum[u] = (1ll * sum[lc[u]] + sum[rc[u]] + val[u]) % mod;
  }
  inline void pushdown(int u) {
    if (rev[u] || add[u] || ~ass[u]) {
      if (lc[u]) lc[u] = clone(lc[u]);
      if (rc[u]) rc[u] = clone(rc[u]);
    }
    if (~ass[u]) tagAss(lc[u], ass[u]), tagAss(rc[u], ass[u]), ass[u] = -1;
    if (add[u]) tagAdd(lc[u], add[u]), tagAdd(rc[u], add[u]), add[u] = 0;
    if (rev[u]) tagRev(lc[u]), tagRev(rc[u]), rev[u] = false;
  }
  void split(int u, int idx, int &l, int &r) {
    // ferr << u << " " << idx << " " << l << " " << r << " ";
    // ferr << siz[lc[u]] << " " << lc[u] << " " << rc[u] << "\n";
    if (!u) return l = r = 0, void();
    pushdown(u);
    if (siz[lc[u]] < idx) {
      l = clone(u), split(rc[l], idx - siz[lc[u]] - 1, rc[l], r);
      pushup(l);
    } else {
      r = clone(u), split(lc[r], idx, l, lc[r]);
      pushup(r);
    }
  }
  int merge(int l, int r) {
    // ferr << l << " " << r << "\n";
    if (!l || !r) return l + r;
    if (prm[l] > prm[r]) {
      pushdown(l), l = clone(l), rc[l] = merge(rc[l], r), pushup(l);
      return l;
    } else {
      pushdown(r), r = clone(r), lc[r] = merge(l, lc[r]), pushup(r);
      return r;
    }
  }
  inline void copy(int l1, int r1, int l2, int r2) {
    bool flg = false;
    if (l1 > l2) std::swap(l1, l2), std::swap(r1, r2), flg = true;
    int p0, p1, p2, p3, p4;
    split(rt, r2, p3, p4);
    split(p3, l2 - 1, p2, p3);
    split(p2, r1, p1, p2);
    split(p1, l1 - 1, p0, p1);
    // ferr << siz[p1] << " " << sum[p1] << " " << siz[p3] << " " << sum[p3] << "\n";
    // ferr << p1 << " " << p3 << " " << cnt << "\n";
    if (!flg) p3 = clone(p1);
    else p1 = clone(p3);
    rt = merge(p0, merge(p1, merge(p2, merge(p3, p4))));
  }
  inline void swap(int l1, int r1, int l2, int r2) {
    if (l1 > l2) std::swap(l1, l2), std::swap(r1, r2);
    int p0, p1, p2, p3, p4;
    split(rt, r2, p3, p4);
    split(p3, l2 - 1, p2, p3);
    split(p2, r1, p1, p2);
    split(p1, l1 - 1, p0, p1);
    rt = merge(p0, merge(p3, merge(p2, merge(p1, p4))));
  }
  inline void assign(int l, int r, int v) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    p1 = clone(p1), tagAss(p1, v);
    rt = merge(p0, merge(p1, p2));
  }
  inline void modify(int l, int r, int v) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    p1 = clone(p1), tagAdd(p1, v);
    rt = merge(p0, merge(p1, p2));
  }
  inline void reverse(int l, int r) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    p1 = clone(p1), tagRev(p1);
    rt = merge(p0, merge(p1, p2));
  }
  inline int query(int l, int r) {
    int p0, p1, p2;
    split(rt, r, p1, p2);
    split(p1, l - 1, p0, p1);
    int res = sum[p1];
    rt = merge(p0, merge(p1, p2));
    return res;
  }
  void traverse(int u) {
    if (!u) return;
    pushdown(u);
    traverse(lc[u]), stk[++top] = val[u], traverse(rc[u]);
  }
  void build(int s, int t, int &u) {
    if (s > t) return;
    int mid = (s + t) >> 1;
    u = init(stk[mid]);
    build(s, mid - 1, lc[u]), build(mid + 1, t, rc[u]);
    pushup(u);
  }
} fhq;

void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> fhq.stk[i];
  fhq.build(1, n, fhq.rt);

  int lst = 0;
  for (int opt, l1, r1, l2, r2, v; m; m--) {
    fin >> opt >> l1 >> r1, l1 ^= lst, r1 ^= lst;

    if (opt == 1) {
      fout << (lst = fhq.query(l1, r1)) << "\n";
    } else if (opt == 2) {
      fin >> v, v ^= lst;
      fhq.assign(l1, r1, v);
    } else if (opt == 3) {
      fin >> v, v ^= lst;
      fhq.modify(l1, r1, v);
    } else if (opt == 4) {
      fin >> l2 >> r2, l2 ^= lst, r2 ^= lst;
      fhq.copy(l1, r1, l2, r2);
    } else if (opt == 5) {
      fin >> l2 >> r2, l2 ^= lst, r2 ^= lst;
      fhq.swap(l1, r1, l2, r2);
    } else {
      fhq.reverse(l1, r1);
    }

    if (fhq.cnt >= 7.0e6) {
      fhq.top = 0, fhq.traverse(fhq.rt), fhq.cnt = 0;
      fhq.build(1, fhq.top, fhq.rt);
    }
  }

  fhq.top = 0, fhq.traverse(fhq.rt);
  for (int i = 1; i <= n; i++) fout << fhq.stk[i] << " \n"[i == n];
}

int main() {
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}

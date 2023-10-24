/**
 * @file    CF718C Sasha and Array.cpp
 * @author  ForgotDream
 * @brief   SegTree + Matrix
 * @date    2023-10-16
 */
#include <cassert>
#include <cstring>
#include <iostream>

using i64 = long long;

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

constexpr int N = 1e5 + 50, mod = 1e9 + 7;
int n, m, a[N];
struct Matrix {
  i64 a[2][2];
  int row, col;
  Matrix() { init(); };
  Matrix(int r, int c) : row(r), col(c) { init(); }
  inline void init() { memset(a, 0, sizeof(a)); }
  inline void normalize() {
    // assert(row == col);
    init();
    for (int i = 0; i < row; i++) a[i][i] = 1;
  }
  static void print(const Matrix &mat) {
    for (int i = 0; i < mat.row; i++) {
      for (int j = 0; j < mat.col; j++) {
        std::cout << mat.a[i][j] << " \n"[j == mat.col - 1];
      }
    }
    std::cout << "\n";
  }
  static bool isNorm(const Matrix &val) {
    if (val.row != val.col) return false;
    for (int i = 0; i < val.row; i++) {
      for (int j = 0; j < val.col; j++) {
        if (i == j) continue;
        if (val.a[i][j] != 0) return false; 
      }
    }
    return true;
  }
  Matrix operator+(const Matrix &rhs) const {
    // assert(row == rhs.row && col == rhs.col);
    Matrix res(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        res.a[i][j] = (a[i][j] + rhs.a[i][j]) % mod;
      }
    }
    return res;
  }
  Matrix operator*(const Matrix &rhs) const {
    // assert(col == rhs.row);
    Matrix res(row, rhs.col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < rhs.col; j++) {
        for (int k = 0; k < col; k++) {
          res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j] % mod) % mod;
        }
      }
    }
    return res;
  }
};
Matrix fastPow(Matrix base, i64 exp) {
  // assert(base.row == base.col);
  Matrix res(base.row, base.col);
  res.normalize();
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}
Matrix base(2, 2), coef(1, 2);
struct SegTree {
  Matrix tree[N << 2], tag[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  inline void tagging(int u, const Matrix &val) {
    tree[u] = val * tree[u], tag[u] = val * tag[u];
  }
  inline void pushdown(int u) {
    if (Matrix::isNorm(tag[u])) return;
    // Matrix::print(tag[u]);
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u].normalize();
  }
  void build(int s, int t, int u) {
    tag[u] = Matrix(2, 2), tag[u].normalize();
    if (s == t) return tree[u] = fastPow(base, a[s] - 1), void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  void modify(int l, int r, int s, int t, int u, const Matrix &val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  Matrix query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    else return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;
void solve() {
  base.a[0][0] = 0, base.a[0][1] = 1;
  base.a[1][0] = 1, base.a[1][1] = 1;
  coef.a[0][0] = 0, coef.a[0][1] = 1;
  // Matrix::print(fastPow(base, 2));
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> a[i];
  seg.build(1, n, 1);
  for (int opt, l, r, v; m; m--) {
    fin >> opt >> l >> r;
    if (opt == 1) {
      fin >> v;
      seg.modify(l, r, 1, n, 1, fastPow(base, v));
      // Matrix::print(fastPow(base, v));
    } else {
      fout << (coef * seg.query(l, r, 1, n, 1)).a[0][1] << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}

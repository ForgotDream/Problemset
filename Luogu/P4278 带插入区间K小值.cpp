/**
 * @file    P4278 带插入区间K小值.cpp
 * @author  ForgotDream
 * @brief   块状链表 + 值域分块
 * @date    2023-09-11
 */
#include <iostream>

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

constexpr int N = 35050, M = 70050, K = 405, alpha = 2, lim = 350;
int n, m, a[N];
namespace SQRT {
int s, cnt;
struct Node {
  int pre, nxt, size;
  int bln[K], sum[M], val[alpha * K];
} blk[2 * K];
int bln[M];
void rebuild(int cur) {
  int nxt = ++cnt;
  blk[nxt].nxt = blk[cur].nxt;
  blk[blk[cur].nxt].pre = nxt;
  blk[nxt].pre = cur, blk[cur].nxt = nxt;
  blk[nxt].size = blk[cur].size / 2;
  int newsize = blk[cur].size - blk[nxt].size;
  std::copy(blk[cur].sum, blk[cur].sum + M, blk[nxt].sum);
  std::copy(blk[cur].bln, blk[cur].bln + K, blk[nxt].bln);
  for (int i = newsize + 1; i <= blk[cur].size; i++) {
    int &tmp = blk[cur].val[i];
    blk[nxt].val[i - newsize] = tmp;
    blk[cur].bln[bln[tmp]]--, blk[cur].sum[tmp]--;
    tmp = 0;
  }
  blk[cur].size = newsize;
}
void insert(int idx, int val) {
  int cur = s;
  while (blk[cur].size < idx) {
    if (blk[cur].nxt) idx -= blk[cur].size, cur = blk[cur].nxt;
    else break;
  }
  for (int i = blk[cur].size; i >= idx; i--) {
    blk[cur].val[i + 1] = blk[cur].val[i];
  }
  blk[cur].val[idx] = val, blk[cur].size++;
  int cpy = cur;
  while (cur) {
    blk[cur].bln[bln[val]]++;
    blk[cur].sum[val]++;
    cur = blk[cur].nxt;
  }
  if (blk[cpy].size > alpha * lim) rebuild(cpy);
}
void modify(int idx, int val) {
  int cur = s;
  while (blk[cur].size < idx) idx -= blk[cur].size, cur = blk[cur].nxt;
  int bfr = blk[cur].val[idx], aft = val;
  if (bfr == aft) return;
  blk[cur].val[idx] = aft;
  while (cur) {
    blk[cur].bln[bln[bfr]]--, blk[cur].bln[bln[aft]]++;
    blk[cur].sum[bfr]--, blk[cur].sum[aft]++;
    cur = blk[cur].nxt;
  }
}
void print() {
  for (int i = s; i; i = blk[i].nxt) {
    std::cerr << i << "[" << blk[i].size << "]: ";
    for (int j = 1; j <= blk[i].size; j++) std::cerr << blk[i].val[j] << " ";
    std::cerr << "\n";
  }
}
int tmpsum[M], tmpbln[K];
int kth(int l, int r, int k) {
  int p = s;
  while (blk[p].size < l) l -= blk[p].size, r -= blk[p].size, p = blk[p].nxt;
  int q = p;
  while (blk[q].size < r) r -= blk[q].size, q = blk[q].nxt;
  if (p == q) {
    for (int i = l; i <= r; i++) {
      tmpsum[blk[p].val[i]]++, tmpbln[bln[blk[p].val[i]]]++;
    }
    int cur = 1;
    while (tmpbln[cur] < k) k -= tmpbln[cur], cur++;
    cur = (cur - 1) * lim;
    while (tmpsum[cur] < k) k -= tmpsum[cur], cur++;
    for (int i = l; i <= r; i++) {
      tmpsum[blk[p].val[i]]--, tmpbln[bln[blk[p].val[i]]]--;
    }
    return cur;
  } else {
    // print();
    for (int i = l; i <= blk[p].size; i++) {
      tmpsum[blk[p].val[i]]++, tmpbln[bln[blk[p].val[i]]]++;
    }
    for (int i = 1; i <= r; i++) {
      tmpsum[blk[q].val[i]]++, tmpbln[bln[blk[q].val[i]]]++;
    }
    int cur = 1;
    while (tmpbln[cur] + blk[blk[q].pre].bln[cur] - blk[p].bln[cur] < k) {
      k -= tmpbln[cur] + blk[blk[q].pre].bln[cur] - blk[p].bln[cur], cur++;
    }
    cur = (cur - 1) * lim;
    while (tmpsum[cur] + blk[blk[q].pre].sum[cur] - blk[p].sum[cur] < k) {
      k -= tmpsum[cur] + blk[blk[q].pre].sum[cur] - blk[p].sum[cur], cur++;
    }
    for (int i = l; i <= blk[p].size; i++) {
      tmpsum[blk[p].val[i]]--, tmpbln[bln[blk[p].val[i]]]--;
    }
    for (int i = 1; i <= r; i++) {
      tmpsum[blk[q].val[i]]--, tmpbln[bln[blk[q].val[i]]]--;
    }
    return cur;
  }
}
void init() {
  for (int i = 0; i <= 7e4; i++) bln[i] = i / lim + 1;
  s = ++cnt;
  for (int i = 1; i <= n; i++) insert(i, a[i]);
}
}
void solve() {
  fin >> n;
  for (int i = 1; i <= n; i++) fin >> a[i];
  SQRT::init();
  fin >> m;
  int lst = 0;
  for (int i = 1; i <= m; i++) {
    char opt;
    int u, l, r, val;
    fin >> opt;
    if (opt == 'I') {
      fin >> u >> val;
      u ^= lst, val ^= lst;
      SQRT::insert(u, val);
    } else if (opt == 'M') {
      fin >> u >> val;
      u ^= lst, val ^= lst;
      SQRT::modify(u, val);
    } else {
      fin >> l >> r >> val;
      l ^= lst, r ^= lst, val ^= lst;
      fout << (lst = SQRT::kth(l, r, val)) << "\n";
    }
  }
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
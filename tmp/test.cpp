#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
const int N = 3 * 1e5 + 10;
const int Md = (1 << 25) - 1;
int ans[N];
int n;
int m;
int q;
struct hsh_map  // 用来离散化的哈希表
{
  int f[N];
  int x[N];
  int v[N];
  int ct;
  int al[Md];
  int lsh[N];
  int hd;
  int rk[N];
  inline void add(int u, int V) {
    v[++ct] = V;
    x[ct] = al[u];
    al[u] = ct;
  }
  inline int& operator[](int va)  // 重载寻址运算符
  {
    for (int i = al[va & Md]; i; i = x[i])
      if (v[i] == va) {
        return f[i];
      }
    add(va & Md, va);
    return f[ct];
  }
  inline int find(int x)  // 二分
  {
    int* p = lower_bound(lsh + 1, lsh + hd + 1, x);
    if (p != lsh + hd + 1) return this->operator[](*p);
    return n + 1;
  }
  inline void ins(int x) { lsh[++hd] = x; }
  inline void build()  // 暴力离散化
  {
    sort(lsh + 1, lsh + hd + 1);
    rk[1] = 1;
    for (int i = 1; i <= hd; i++) rk[i] = lsh[i] == lsh[i - 1] ? rk[i - 1] : i;
    for (int i = 1; i <= hd; i++) this->operator[](lsh[i]) = rk[i];
  }
} mp;
inline void ers(multiset<int>& s, const int& val)  // multiset的erase
{
  multiset<int>::iterator it = s.find(val);
  if (it != s.end()) s.erase(it);
}
struct opt  // 扫描线
{
  int ti;
  int tp;
  int k;
  int pos;
  friend bool operator<(opt a, opt b) {
    return (a.ti == b.ti) ? (a.tp < b.tp) : (a.ti < b.ti);
  }
} op[3 * N];
int hd;
struct linetree {
  multiset<int> s[4 * N];
  int v[4 * N];
  multiset<int> til;
  inline void build(int p, int l, int r) {
    int mid = (l + r) / 2;
    v[p] = 0x3f3f3f3f;
    if (r - l == 1) return;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid, r);
  }
  inline void ins(int p, int l, int r, const int& pos, const int& val)  // 插入
  {
    if (r - l == 1) {
      s[p].insert(val);
      v[p] = *(s[p].begin());
      return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
      ins(p << 1, l, mid, pos, val);
    else
      ins(p << 1 | 1, mid, r, pos, val);
    v[p] = min(v[p << 1], v[p << 1 | 1]);
  }
  inline void del(int p, int l, int r, const int& pos, const int& val)  // 删除
  {
    if (r - l == 1) {
      ers(s[p], val);
      v[p] = s[p].empty() ? 0x3f3f3f3f : *(s[p].begin());
      return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
      del(p << 1, l, mid, pos, val);
    else
      del(p << 1 | 1, mid, r, pos, val);
    v[p] = min(v[p << 1], v[p << 1 | 1]);
  }
  inline void modify(int p, int l, int r, const int& pos, const int& val1,
                     const int& val2)  // 修改
  {
    if (r - l == 1) {
      ers(s[p], val1);
      s[p].insert(val2);
      v[p] = *(s[p].begin());
      return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
      modify(p << 1, l, mid, pos, val1, val2);
    else
      modify(p << 1 | 1, mid, r, pos, val1, val2);
    v[p] = min(v[p << 1], v[p << 1 | 1]);
  }
  inline int query(int p, int l, int r, int dl, int dr)  // 区间最小值
  {
    if (dl == l && dr == r) {
      return v[p];
    }
    int ret = 0x3f3f3f3f;
    int mid = (l + r) / 2;
    if (dl < mid) ret = min(ret, query(p << 1, l, mid, dl, min(dr, mid)));
    if (mid < dr) ret = min(ret, query(p << 1 | 1, mid, r, max(dl, mid), dr));
    return ret;
  }
  inline void imd(const int& v) { til.insert(v); }  // 单开的set的操作
  inline void pmd(const int& v) { ers(til, v); }
  inline int cquery(int r) {
    if (r == n + 1) return *(til.begin());  // 判一下是否越界
    return min(*(til.begin()), query(1, 0, n, r - 1, n));
  }
} lt;
multiset<int> col[N];
int cnt;
inline void ins(int pos, int k)  // 更改pre值的插入，分4种情况讨论有无前驱后继
{
  multiset<int>::iterator it, it1, it2;
  if (col[k].empty()) cnt++;
  it = col[k].insert(pos);
  if (it != --col[k].end()) {
    int pre = -0x3f3f3f3f;
    it2 = it;
    ++it2;
    if (it != col[k].begin()) {
      it1 = it;
      --it1;
      pre = *it1;
    }
    lt.modify(1, 0, n, mp[*it2], pre, *it);
    lt.ins(1, 0, n, mp[*it], pre);
  } else {
    int pre = -0x3f3f3f3f;
    if (it != col[k].begin()) {
      it1 = it;
      --it1;
      pre = *it1;
    }
    lt.ins(1, 0, n, mp[*it], pre);
    lt.pmd(pre);
    lt.imd(*it);
  }
}
inline void del(int pos, int k)  // 同理删除的时候，分4种情况讨论有无前驱后继
{
  multiset<int>::iterator it, it1, it2;
  it = col[k].find(pos);
  if (it != --col[k].end()) {
    int pre = -0x3f3f3f3f;
    it2 = it;
    ++it2;
    if (it != col[k].begin()) {
      it1 = it;
      --it1;
      pre = *it1;
    }
    lt.modify(1, 0, n, mp[*it2], *it, pre);
    lt.del(1, 0, n, mp[*it], pre);
  } else {
    int pre = -0x3f3f3f3f;
    if (it != col[k].begin()) {
      it1 = it;
      --it1;
      pre = *it1;
    }
    lt.del(1, 0, n, mp[*it], pre);
    lt.pmd(*it);
    lt.imd(pre);
  }
  ers(col[k], pos);
  if (col[k].empty()) cnt--;
}
inline int query(int pos)  // 二分答案
{
  if (cnt != m) return -1;
  int l = 0;
  int r = 1e8 + 10;
  while (l != r) {
    int mid = (l + r) / 2;
    int mi = lt.cquery(mp.find(pos + mid + 1));
    if (mi < pos - mid)
      l = mid + 1;
    else
      r = mid;
  }
  return l;
}
int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1, ti1, ti3, pos, col; i <= n; i++) {
    scanf("%d%d%d%d", &pos, &col, &ti1, &ti3);
    mp.ins(pos);
    op[++hd] = (opt){ti1, 1, col, pos};
    op[++hd] = (opt){ti3, 3, col, pos};
  }
  mp.build();
  for (int i = 1, ti, pos; i <= q; i++) {
    scanf("%d%d", &pos, &ti);
    op[++hd] = (opt){ti, 2, i, pos};
  }
  sort(op + 1, op + hd + 1);
  lt.build(1, 0, n);
  for (int i = 1; i <= hd; i++) {
    switch (op[i].tp) {
      case 1: {
        ins(op[i].pos, op[i].k);
        break;
      }
      case 2: {
        ans[op[i].k] = query(op[i].pos);
        break;
      }
      case 3: {
        del(op[i].pos, op[i].k);
        break;
      }
    }
  }
  for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
  return 0;  // 拜拜程序~
}

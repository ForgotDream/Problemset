#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 6e5 + 50;
constexpr int mod = 998244353;

inline i64 norm(i64 x) { return (x % mod + mod) % mod; }

constexpr int M = 4e6 + 50;
int rt[N], lc[M], rc[M], sum[M];
int cnt = 0;

void insert(int &u, int l, int r, int pos) {
  if (!u) {
    u = ++cnt;
    lc[u] = rc[u] = sum[u] = 0;
  }
  if (l == r) {
    sum[u] = 1;
    return;
  }
  int mid = l + (r - l) / 2;
  if (pos <= mid) insert(lc[u], l, mid, pos);
  else insert(rc[u], mid + 1, r, pos);
  sum[u] = sum[lc[u]] + sum[rc[u]];
}

int merge(int u, int v, int l, int r) {
  if (!u || !v) return u ? u : v;
  if (l == r) {
    sum[u] |= sum[v];
    return u;
  }
  int mid = l + (r - l) / 2;
  lc[u] = merge(lc[u], lc[v], l, mid);
  rc[u] = merge(rc[u], rc[v], mid + 1, r);
  sum[u] = sum[lc[u]] + sum[rc[u]];
  return u;
}

void extract(int u, int l, int r, std::vector<int> &res) {
  if (!u || !sum[u]) return;
  if (l == r) {
    res.push_back(l);
    return;
  }
  int mid = l + (r - l) / 2;
  extract(lc[u], l, mid, res);
  extract(rc[u], mid + 1, r, res);
}

struct SAM {
  int ch[N][26], link[N], len[N], cnt, lst;

  void init() {
    link[0] = -1, len[0] = 0, cnt = 0, lst = 0;
  }

  void expand(char c, int pos, int n) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1;
    insert(rt[cur], 1, n, pos);

    int p = lst;
    for (; ~p && !ch[p][c - 'a']; p = link[p]) ch[p][c - 'a'] = cur;
    if (p == -1) return link[cur] = 0, lst = cur, void();
    int q = ch[p][c - 'a'];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
    } else {
      int tmp = ++cnt;
      len[tmp] = len[p] + 1, link[tmp] = link[q];
      std::memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
      for (; ~p && ch[p][c - 'a'] == q; p = link[p]) ch[p][c - 'a'] = tmp;
      link[q] = link[cur] = tmp;
    }
    lst = cur;
  }

  void build(const std::string_view &s) {
    init();
    for (int i = 0; i < s.length(); i++) expand(s[i], i + 1, s.length());
  }
} sam;

struct Info {
  int len;
  std::vector<int> ids;
};

void solve() {
  int n, q;
  std::cin >> n >> q;

  std::string s;
  std::cin >> s;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) std::cin >> a[i];

  std::vector<i64> pref(n + 1, 0);
  for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

  std::vector<i64> suf_max(n + 2, -4e18);
  for (int i = n; i >= 1; i--) suf_max[i] = std::max(pref[i], suf_max[i + 1]);

  std::vector<i64> pref_mod(n + 1, 0), sum_pref_mod(n + 1, 0);
  for (int i = 0; i <= n; i++) {
    pref_mod[i] = norm(pref[i]);
    sum_pref_mod[i] = norm((i > 0 ? sum_pref_mod[i - 1] : 0) + pref_mod[i]);
  }

  // sparse table
  std::vector st(20, std::vector<i64>(n + 1));
  for (int i = 0; i <= n; i++) st[0][i] = pref[i];
  for (int j = 1; (1 << j) <= n + 1; j++) {
    for (int i = 0; i + (1 << j) - 1 <= n; i++) {
      st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
  }
  auto query_min = [&](int L, int R) -> i64 {
    int j = std::__lg(R - L + 1);
    return std::min(st[j][L], st[j][R - (1 << j) + 1]);
  };

  sam.build(s);

  std::map<std::string, std::vector<int>> queries;
  for (int i = 0; i < q; i++) {
    std::string t;
    std::cin >> t;
    queries[t].push_back(i);
  }

  std::vector<std::vector<Info>> info(sam.cnt + 1);

  for (auto &[t, ids] : queries) {
    int u = 0;
    bool ok = true;
    for (char c : t) {
      if (!sam.ch[u][c - 'a']) { ok = false; break; }
      u = sam.ch[u][c - 'a'];
    }
    if (ok) info[u].push_back({int(t.length()), ids});
  }

  std::vector<int> idx(sam.cnt + 1);
  std::iota(idx.begin(), idx.end(), 0);
  std::sort(idx.begin(), idx.end(), [](int u, int v) {
    return sam.len[u] > sam.len[v];
  }); // topo sort

  std::vector<i64> ans_max(q, -4e18);
  std::vector<i64> ans_sum(q, 0);

  for (int u : idx) {
    if (!info[u].empty()) {
      std::vector<int> endpos;
      extract(rt[u], 1, n, endpos);

      for (auto &qi : info[u]) {
        int len = qi.len;
        i64 cur_max = -4e18;
        i64 cur_sum = 0;
        int prev_p = 0;

        for (int e : endpos) {
          int l = prev_p + 1, r = e - len + 1;

          i64 min_v = query_min(l - 1, r - 1);
          cur_max = std::max(cur_max, suf_max[e] - min_v);

          i64 sr = norm(sum_pref_mod[n] - sum_pref_mod[e - 1]);
          i64 sl = norm(sum_pref_mod[r - 1] - (l - 2 >= 0 ? sum_pref_mod[l - 2] : 0));

          i64 cnt1 = norm(r - l + 1);
          i64 cnt2 = norm(n - e + 1);

          i64 term1 = norm(cnt1 * sr);
          i64 term2 = norm(cnt2 * sl);

          cur_sum = norm(cur_sum + term1 - term2);

          prev_p = e - len + 1;
        }

        for (int id : qi.ids) ans_max[id] = cur_max, ans_sum[id] = cur_sum;
      }
    }
    
    if (sam.link[u] != -1) rt[sam.link[u]] = merge(rt[sam.link[u]], rt[u], 1, n);
  }

  for (int i = 0; i < q; i++) std::cout << ans_max[i] << " " << ans_sum[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}

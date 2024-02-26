#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

typedef struct Line_tag {
  int k;
  pair<ll, int> pr;

  Line_tag() {}

  Line_tag(int k_, pair<ll, int> pr_) {
    k = k_;
    pr = pr_;
  }

  inline pair<ll, int> calc(ll x) {
    return make_pair(k * x + pr.first, pr.second);
  }
} Line;

inline bool check(Line a, Line b, Line c) {
  return (b.pr.first - a.pr.first) * (c.k - b.k) >=
         (c.pr.first - b.pr.first) * (b.k - a.k);
}

typedef struct {
  int head;
  int tail;
  Line q[100007];

  inline void init() {
    head = 1;
    tail = 0;
  }

  inline int size() { return tail - head + 1; }

  inline void insert(Line line) {
    while (size() >= 1 && ((q[tail].k == line.k && q[tail].pr >= line.pr) ||
                           (size() >= 2 && check(line, q[tail], q[tail - 1]))))
      tail--;
    q[++tail] = line;
  }

  inline pair<ll, int> query(ll x) {
    if (head > tail) return make_pair(0x7fffffffffffffffll, 0);
    while (size() >= 2 && q[head].calc(x) >= q[head + 1].calc(x)) head++;
    return q[head].calc(x);
  }
} ConvexHull;

typedef struct {
  int cnt;
  vector<int> v;
} Node;

int id = 0;
ConvexHull conv;
int sum[100007], _log2[100007], st[17][100007], cnt[100007];
ll complete[100007], inside[100007];
char s[100007];
Node tree[100007];
pair<ll, int> pr1[100007], pr2[100007];
vector<int> v[200007];

pair<ll, int> operator+(const pair<ll, int> a, const pair<ll, int> b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

void operator+=(pair<ll, int> &a, const pair<ll, int> b) { a = a + b; }

inline void init(int n) {
  int ni = n + 1, m;
  for (int i = 2; i <= ni; i++) {
    _log2[i] = _log2[i / 2] + 1;
  }
  m = _log2[ni];
  for (int i = 0; i <= n; i++) {
    st[0][i] = sum[i];
  }
  for (int i = 1; i <= m; i++) {
    int id = i - 1, t1 = n - (1 << i) + 1, t2 = 1 << id;
    for (int j = 0; j <= t1; j++) {
      st[i][j] = min(st[id][j], st[id][j + t2]);
    }
  }
}

inline int get_min(int l, int r) {
  int t = _log2[r - l + 1];
  return min(st[t][l], st[t][r - (1 << t) + 1]);
}

int build(int l, int r, int n) {
  int min_val = get_min(l, r), lst = l, ans = ++id;
  for (vector<int>::iterator i =
           lower_bound(v[min_val + n].begin(), v[min_val + n].end(), l);
       i != v[min_val + n].end() && *i <= r; i++) {
    if (lst <= *i - 1) tree[ans].v.push_back(build(lst, *i - 1, n));
    tree[ans].cnt++;
    tree[ans].v.push_back(-*i);
    lst = *i + 1;
  }
  if (lst <= r) tree[ans].v.push_back(build(lst, r, n));
  return ans;
}

inline ll comb_2(int n) { return (ll)n * (n - 1) / 2; }

inline pair<ll, int> check(ll k) {
  for (int i = id; i >= 1; i--) {
    int size = tree[i].v.size();
    pr1[i] = make_pair(0x7fffffffffffffffll, 0);
    for (int j = 0; j < size; j++) {
      if (tree[i].v[j] > 0) {
        cnt[j] = 0;
        inside[j] = complete[tree[i].v[j]];
      } else {
        cnt[j] = 1;
        inside[j] = 0;
      }
      if (j > 0) {
        cnt[j] += cnt[j - 1];
        inside[j] += inside[j - 1];
      }
    }
    conv.init();
    for (int j = 0; j < size; j++) {
      pair<ll, int> temp = conv.query(cnt[j] * 2 - 1);
      pr2[j] = min(make_pair(j > 0 ? comb_2(cnt[j]) : 0, 0),
                   make_pair(temp.first / 2 + comb_2(cnt[j]), temp.second));
      if (tree[i].v[j] > 0) {
        pr2[j] += pr1[tree[i].v[j]];
      } else {
        pr2[j].second++;
        pr2[j].first -= k;
      }
      if (j > 0) pr2[j].first += inside[j - 1];
      pr1[i] =
          min(pr1[i], make_pair(pr2[j].first + (inside[size - 1] - inside[j]) +
                                    comb_2(tree[i].cnt - cnt[j]),
                                pr2[j].second));
      conv.insert(Line(-cnt[j], make_pair((pr2[j].first - inside[j]) * 2 +
                                              (ll)cnt[j] * cnt[j],
                                          pr2[j].second)));
    }
  }
  return min(pr1[1], make_pair(complete[1], 0));
}

int main() {
  int n, k;
  ll l, r = 0, ans;
  cin >> n >> k;
  cin >> (char (&)[100007])s[1];
  k--;
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + (s[i] == '(' ? 1 : -1);
  }
  init(n);
  for (int i = 0; i <= n; i++) {
    v[sum[i] + n].push_back(i);
  }
  build(0, n, n);
  for (int i = id; i >= 1; i--) {
    complete[i] = comb_2(tree[i].cnt);
    for (int j : tree[i].v) {
      if (j > 0) complete[i] += complete[j];
    }
  }
  l = -complete[1];
  while (l <= r) {
    ll mid = (l + r) >> 1;
    pair<ll, int> pr = check(mid);
    if (pr.second <= k) {
      l = mid + 1;
      ans = pr.first + mid * k;
    } else {
      r = mid - 1;
    }
  }
  cout << ans;
  return 0;
}

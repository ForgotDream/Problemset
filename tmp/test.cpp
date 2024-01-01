#include <bits/stdc++.h>
#define I inline
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define ll long long
#define db double
#define lb long db
#define N (12000 + 5)
#define M (10000 + 5)
#define K (20 + 5)
#define mod 1000000007
#define Mod (mod - 1)
#define eps (1e-9)
#define U unsigned int
#define it iterator
#define Gc() getchar()
#define Me(x, y) memset(x, y, sizeof(x))
#define Mc(x, y) memcpy(x, y, sizeof(x))
#define d(x, y) (n * (x - 1) + (y))
#define R(n) (rand() * rand() % (n) + 1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define PB push_back
using namespace std;
struct IO {
  static const int S = 1 << 21;
  char buf[S], *p1, *p2;
  int st[105], Top;
  ~IO() { clear(); }
  inline void clear() {
    fwrite(buf, 1, Top, stdout);
    Top = 0;
  }
  inline void pc(const char c) {
    Top == S && (clear(), 0);
    buf[Top++] = c;
  }
  inline char gc() {
    return p1 == p2 &&
                   (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)
               ? EOF
               : *p1++;
  }
  inline IO& operator>>(char& x) {
    while (x = gc(), x == ' ' || x == '\n' || x == '\r')
      ;
    return *this;
  }
  template <typename T>
  inline IO& operator>>(T& x) {
    x = 0;
    bool f = 0;
    char ch = gc();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f ^= 1;
      ch = gc();
    }
    while (ch >= '0' && ch <= '9')
      x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    f ? x = -x : 0;
    return *this;
  }
  inline IO& operator<<(const char c) {
    pc(c);
    return *this;
  }
  template <typename T>
  inline IO& operator<<(T x) {
    if (x < 0) pc('-'), x = -x;
    do {
      st[++st[0]] = x % 10, x /= 10;
    } while (x);
    while (st[0]) pc('0' + st[st[0]--]);
    return *this;
  }
} fin, fout;
int n, Q, k, x, y, Fr, En, R, H, Lh, Ans[M], X[N], Y[N], Id[N], Ph, l, r, mid;
struct Ques {
  ll x, y;
  int id;
} S[M];
I bool C1(Ques x, Ques y) { return x.x < y.x; }
struct Line {
  ll k, b;
  int id;
  I ll calc(ll x) { return x * k + b; }
} L[N];
I bool C3(Line x, Line y) { return x.k ^ y.k ? x.k > y.k : x.b < y.b; }
struct Node {
  db w;
  int x, y;
} P[M];
I bool C2(Node x, Node y) {
  return x.w != y.w ? x.w < y.w
                    : (L[x.x].k ^ L[y.x].k ? L[x.x].k > L[y.x].k
                                           : L[x.y].k > L[y.y].k);
}
int main() {
  int i, j, h;
  fin >> n >> Q;
  for (i = 1; i <= n; i++) fin >> X[i] >> Y[i];
  for (i = 1; i <= Q; i++)
    fin >> x >> y, S[i] = (Ques){x, 1ll * y * y - 1ll * x * x, i};
  sort(S + 1, S + Q + 1, C1);
  k = sqrt(Q);
  for (i = 0; i <= n / k; i++) {
    Fr = max(i * k, 1);
    En = min(i * k + k - 1, n);
    H = Lh = Ph = 0;
    for (j = Fr; j <= En; j++)
      L[++Lh] =
          (Line){-2 * Y[j], 1ll * X[j] * X[j] + 1ll * Y[j] * Y[j], j - Fr + 1};
    for (j = 1; j <= Lh; j++) {
      for (h = j + 1; h <= Lh; h++)
        L[j].k ^ L[h].k &&
            (P[++Ph] = (Node){(L[h].b - L[j].b) * 1.0 / (L[j].k - L[h].k),
                              L[j].k > L[h].k ? j : h, L[j].k < L[h].k ? j : h},
             0);
    }
    // std::cerr << Ph << "\n";
    // for (j = 1; j <= Ph; j++) std::cerr << P[j].x << " " << P[j].y << "\n";
    sort(P + 1, P + Ph + 1, C2);
    sort(L + 1, L + Lh + 1, C3);
    for (j = 1; j <= Lh; j++) Id[L[j].id] = j;
    R = 1;
    for (j = 1; j <= Q; j++) {
      while (R <= Ph && P[R].w <= S[j].x)
        // Id[P[R].x] < Id[P[R].y] && (swap(L[Id[P[R].x]], L[Id[P[R].y]]),
        //                             swap(Id[P[R].x], Id[P[R].y]), 0),
        (true) && (swap(L[Id[P[R].x]], L[Id[P[R].y]]),
                   swap(Id[P[R].x], Id[P[R].y]), 0),
            R++;
      l = 0;
      r = Lh + 1;
      while (l + 1 < r)
        mid = l + r >> 1, (L[mid].calc(S[j].x) <= S[j].y ? l : r) = mid;
      Ans[S[j].id] += l;
      // for(h=2;h<=Lh;h++) if(L[h].calc(S[j].x)<L[h-1].calc(S[j].x))
      // cerr<<L[h].calc(S[j].x)<<' '<<L[h-1].calc(S[j].x)<<'\n',assert(0);
    }
  }
  for (i = 1; i <= Q; i++) fout << Ans[i] << '\n';
}

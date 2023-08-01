<<<<<<< Updated upstream
#include <stdio.h>

#define H_MAX 2000
#define W_MAX 2000

<<<<<<< Updated upstream
int main() {
  std::vector<int> a = { 5, 4, 3, 2, 1 };
  return 0;
=======
const int Mod = 998244353;

int solve(int H, int W, char S[][W_MAX + 2])
{
	int i, j, rect_sum[H_MAX + 2][W_MAX + 2];
	for (j = 0; j <= W; j++) rect_sum[0][j] = 0;
	for (i = 1; i <= H; i++) {
		rect_sum[i][0] = 0;
		for (j = 1; j <= W; j++) {
			rect_sum[i][j] = rect_sum[i-1][j] + rect_sum[i][j-1] - rect_sum[i-1][j-1] + ((S[i][j] == 'Y')? 1: 0);
		}
	}
	if (rect_sum[H][W] % 2 != 0) return 0;
	
	int h, w, y = rect_sum[H][W] / 2, k, l, h_fence[H_MAX + 2], w_fence[W_MAX + 2], next_sum;
	long long ans = 0, deg_free;
	for (h = 0; h < H; h++) {
		if (y % (h + 1) != 0) continue;
		w = y / (h + 1) - 1;
		if (w < 0 || w >= W) continue;
		
		deg_free = 1;
		for (i = 1, k = 0, h_fence[0] = 0, next_sum = (w + 1) * 2; k < h; i++) {
			if (rect_sum[i][W] > next_sum) break;
			else if (rect_sum[i][W] == next_sum) {
				h_fence[++k] = i;
				next_sum += (w + 1) * 2;
				
				for (i++, l = 1; rect_sum[i][W] == rect_sum[i-1][W]; i++, l++);
				deg_free = deg_free * l % Mod;
				i--;
			}
		}
		if (k < h) continue;
		h_fence[h+1] = H;
		
		for (j = 1, k = 0, w_fence[0] = 0, next_sum = (h + 1) * 2; k < w; j++) {
			if (rect_sum[H][j] > next_sum) break;
			else if (rect_sum[H][j] == next_sum) {
				w_fence[++k] = j;
				next_sum += (h + 1) * 2;

				for (j++, l = 1; rect_sum[H][j] == rect_sum[H][j-1]; j++, l++);
				deg_free = deg_free * l % Mod;
				j--;
			}
		}
		if (k < w) continue;
		w_fence[w+1] = W;
		
		for (i = 1; i <= h + 1; i++) {
			for (j = 1; j <= w + 1; j++) {
				if (rect_sum[h_fence[i]][w_fence[j]] - rect_sum[h_fence[i-1]][w_fence[j]] - rect_sum[h_fence[i]][w_fence[j-1]] + rect_sum[h_fence[i-1]][w_fence[j-1]] != 2) break;
			}
			if (j <= w + 1) break;
		}
		if (i <= h + 1) continue;
		
		ans += deg_free;
	}
	return ans % Mod;
}

int main()
{
	int i, H, W;
	char S[H_MAX + 2][W_MAX + 2] = {};
	scanf("%d %d", &H, &W);
	for (i = 1; i <= H; i++) scanf("%s", &(S[i][1]));
	printf("%d\n", solve(H, W, S));
	fflush(stdout);
	return 0;
>>>>>>> Stashed changes
=======
#include <bits/stdc++.h>
#define rep(i,a,b) for (int i = (a); i <= b; i++)

namespace FastIO {
char buf[1 << 23], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) p1 = buf, p2 = buf + fread(buf, 1, 1 << 23, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T> inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) f = (c == '-' ? -f : f), c = gc();
  while (isdigit(c)) x = x * 10 + c - '0', c = gc();
  x *= f;
}
template <typename T, typename... args> inline void read(T &x, args &...tmp) {
  read(x), read(tmp...);
}
template <typename T> inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x / 10) print(x / 10);
  putchar(x % 10 + '0');
}
template <typename T> inline void print(T x, char c) { print(x), putchar(c); }
inline void readString(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
} // namespace FastIO


using namespace std;
using namespace FastIO;

const int N = 1e5 + 5;
const int S = N << 2;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int h,w,n,L[N],R[N],T[S];

struct barrier{ int u,l,r,s; } B[N];
using node = pair<int,int>;

priority_queue<node> Q[N];

#define lc (i << 1)
#define rc (i << 1 | 1)
#define mid ((L + R) >> 1)
#define ls lc,L,mid
#define rs rc,mid + 1,R
#define id int i = 1,int L = 1,int R = w
#define psu T[i] = min(T[lc],T[rc])

void build(id){
    if(L == R) return Q[L].emplace(-(T[i] = h + 1),-1);
    build(ls); build(rs); psu;
}

void upd(int p,int h,int v,id){
    if(L == R){
        Q[L].emplace(-h,-v);
        return void(T[i] = -Q[L].top().first);
    }
    p <= mid ? upd(p,h,v,ls) : upd(p,h,v,rs); psu;
}

int qry(int l,int r,int x,id){
    if(T[i] > x) return 0;
    int sum = 0;
    if(L == R){
        while(Q[L].size() && -Q[L].top().first <= x)
            (sum += -Q[L].top().second) %= mod,Q[L].pop();
        T[i] = Q[L].size() ? -Q[L].top().first : inf;
        return sum;
    }
    if(l <= mid) sum += qry(l,r,x,ls);
    if(r > mid) (sum += qry(l,r,x,rs)) %= mod;
    psu; return sum;
}

int main(){
    read(h,w,n);
    rep(i,1,n) read(B[i].u,B[i].l,B[i].r,B[i].s);
    sort(B + 1,B + n + 1,[](auto a,auto b){return a.u > b.u;});
    build();
    rep(i,1,n){
        int x = qry(B[i].l,B[i].r,min(h + 1,B[i].s + B[i].u));
        std::cerr << x << "\n";
        if(B[i].l != 1) upd(B[i].l - 1,B[i].u,x * ((B[i].r == w) + 1) % mod);
        if(B[i].r != w) upd(B[i].r + 1,B[i].u,x * ((B[i].l == 1) + 1) % mod);
    }
    print(qry(1,w,inf));
    return 0;
>>>>>>> Stashed changes
}
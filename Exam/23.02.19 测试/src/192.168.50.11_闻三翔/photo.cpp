# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
using namespace std;
const int N = 1e5 + 50;
template <class T>inline
void Read(T &x)
{
	char ch; x = 0; int base = 1;
	while((ch = getchar())<'0' || ch > '9') if(ch == '-') base = -1;
	x += ch - '0';
	while((ch = getchar())>='0' && ch <='9') x = (x << 1) + (x << 3) + ch - '0';
	x *= base; return;
} 
template <typename T>inline
void print(T x)
{
	if(x < 0) putchar('-'), x = -x;
	x >= 10 ? (print(x / 10), putchar(x % 10 + '0')) : putchar(x + '0');
	return;
} 
int n, k;
int E[N], C[N];
struct person {
	int id, W;
	bool operator <(const person &tmp) const {
		if(W == tmp.W) return id < tmp.id;
		return W > tmp.W;
	}
}p[N];
int main()
{
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	Read(n); Read(k);
	for(int i = 1; i <= 10; i ++) Read(E[i]);
	for(int i = 1; i <= n; i ++) Read(p[i].W), p[i].id = i;
	sort(p + 1, p + 1 + n);
	for(int i = 1; i <= n; i ++) {
		int tmp = (i - 1) % 10 + 1;
		p[i].W += E[tmp];
	}
	sort(p + 1, p + 1 + n);
	for(int i = 1; i <= k; i ++) print(p[i].id), putchar(' ');
	return 0;
}

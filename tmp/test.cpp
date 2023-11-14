#include "bits/stdc++.h"
using namespace std;
const int Len = 2.5e5 + 5;
#define ull unsigned long long
ull n,q;
inline ull read() {
    char ch = getchar();
    ull x = 0, f = 1;
    while (ch < '0' || ch > '9') ch = getchar();
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void write(ull x) {
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
struct info
{
	ull s,sx,sy,sxy;
	info(){s = sx = sy = sxy = 0;}
	info(ull S,ull SX,ull SY,ull SXY){s = S , sx = SX , sy = SY , sxy = SXY;}
	inline void clr(){s = sx = sy = sxy = 0;}
	inline void output(){printf("%llu %llu %llu %llu\n",s,sx,sy,sxy);}
}inf[Len << 2];
struct tag
{
	ull cx,cy,ax,ay,axy,c;
	tag(){cx = cy = ax = ay = axy = c = 0;}
	tag(ull CX,ull CY,ull AX,ull AY,ull AXY,ull C){cx = CX , cy = CY , ax = AX , ay = AY , axy = AXY , c = C;}
	inline void clr(){cx = cy = ax = ay = axy = c = 0;}
	inline bool empty(){return !(cx || cy || ax || ay || axy || c);}
	inline void output(){printf("%llu %llu %llu %llu %llu %llu\n",cx,cy,ax,ay,axy,c);}
}tg[Len << 2];
//需要实现 O + T -> O,T + T -> T,O + O -> O
//重点在于 T + T -> T 
//若 c_x,c_y 都存在，则当前的标记维护的是 cx,cy 的信息，只需要将信息叠加到 c 上即可
//若 c_x 存在，则当前 ay,c 会被影响， 
//若 c_y 存在，则当前 ax,c 会被影响，
//若都不存在，含义就是暴力更新 
//每次结束后下传一个 axy = 1 的 tag
//emmmm。
inline info merge(info x,info y){return info(x.s + y.s , x.sx + y.sx , x.sy + y.sy , x.sxy + y.sxy);}	
inline tag merge(tag x,tag y)//x -> y
{ 
	if(y.cx && y.cy) y.c += x.axy * y.cx * y.cy + x.ax * y.cx + x.ay * y.cy + x.c;
	else if(y.cx) 
	{
		y.ay += x.axy * y.cx + x.ay;
		y.c += x.c + x.ax * y.cx;
	}
	else if(y.cy)
	{
		y.ax += x.axy * y.cy + x.ax;
		y.c += x.c + x.ay * y.cy;
	}
	else 
	{
		y.axy += x.axy;
		y.ax += x.ax;
		y.ay += x.ay;
		y.c += x.c;
	}
	if(x.cx) y.cx = x.cx;
	if(x.cy) y.cy = x.cy;
	return y;
}
inline info merge(info x,tag y,int len)
{
	x.s += y.axy * x.sxy + y.ax * x.sx + y.ay * x.sy + y.c * len;
	if(y.cx && y.cy)
	{
		x.sxy = len * y.cx * y.cy;
		x.sx = len * y.cx;
		x.sy = len * y.cy;
	}
	else if(y.cx)
	{
		x.sxy = x.sy * y.cx;
		x.sx = len * y.cx;
	}
	else if(y.cy)
	{
		x.sxy = x.sx * y.cy;
		x.sy = len * y.cy;
	}
	return x;
}
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
inline void push_up(int p){inf[p] = merge(inf[ls(p)] , inf[rs(p)]);}
inline void push_down(int p,int l,int r)
{
	if(!tg[p].empty())
	{
		int mid = (l + r) >> 1;int l1 = (mid - l + 1) , l2 = (r - mid);
		tg[ls(p)] = merge(tg[p] , tg[ls(p)]) , tg[rs(p)] = merge(tg[p] , tg[rs(p)]);
		inf[ls(p)] = merge(inf[ls(p)] , tg[p] , l1) , inf[rs(p)] = merge(inf[rs(p)] , tg[p] , l2);
		tg[p].clr();
		return;
	}
}
void update(int p,int l,int r,int nl,int nr,tag t)
{
	if(nl <= l && nr >= r) 
	{
		tg[p] = merge(t , tg[p]);
		inf[p] = merge(inf[p] , t , r - l + 1);
		//printf("#%d %d:\n",l,r);
		//tg[p].output();
		//inf[p].output();
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , t);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , t);
	push_up(p);
}
ull query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) 
	{
		/*if(l == 2 && r == 2)
		{
			printf("?%d %d:\n",l,r);
			tg[p].output();
			inf[p].output();
		}*/
		return inf[p].s;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;ull res = 0;
	if(nl <= mid) res += query(ls(p) , l , mid , nl , nr);
	if(nr > mid) res += query(rs(p) , mid + 1 , r , nl , nr);
	return res;
}
ull a[Len],b[Len],stk[Len][2],top[2];
struct Node
{
	ull l,id;
	Node(){l = id = 0;}
	Node(ull L,ull ID){l = L , id = ID;}
}Qs[Len];
vector<Node> vec[Len];
ull Pt[Len];ull sz[Len];
signed main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	int TP = read();
	n = read();
	for(int i = 1 ; i <= n ; i ++) a[i] = read();
	for(int i = 1 ; i <= n ; i ++) b[i] = read();
	q = read();
	for(int i = 1 ; i <= q ; i ++)
	{
		Qs[i].l = read() , Qs[i].id = read();
		sz[Qs[i].id] ++;
	}
	for(int i = 1 ; i <= n ; i ++) vec[i].reserve(sz[i]);
	for(int i = 1 ; i <= q ; i ++) vec[Qs[i].id].push_back(Node(Qs[i].l , i));
	for(int i = 1 ; i <= n ; i ++)
	{
		while(top[0] > 0 && a[stk[top[0]][0]] < a[i]) top[0] --;
		update(1 , 1 , n , stk[top[0]][0] + 1 , i , tag(a[i] , 0 , 0 , 0 , 0 , 0));
		stk[++ top[0]][0] = i;
		while(top[1] > 0 && b[stk[top[1]][1]] < b[i]) top[1] --;
		update(1 , 1 , n , stk[top[1]][1] + 1 , i , tag(0 , b[i] , 0 , 0 , 0 , 0));
		stk[++ top[1]][1] = i;
		update(1 , 1 , n , 1 , i , tag(0 , 0 , 0 , 0 , 1 , 0));
		int Sz = (int)vec[i].size();for(int j = 0 ; j < Sz ; j ++) Pt[vec[i][j].id] = query(1 , 1 , n , vec[i][j].l , i);	
	} 
	for(int i = 1 ; i <= q ; i ++) write(Pt[i]) , putchar('\n');
	return 0;
}

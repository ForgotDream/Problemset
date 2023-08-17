#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;
const int MaxN = 100000 + 10;
const int MaxNodes = MaxN << 1;
int tree[MaxNodes][2], root, ql, qr, sl, arr[MaxN], qv;
long long az[MaxNodes];

void update(int t){az[t] = az[tree[t][0]] + az[tree[t][1]];}
void build(int &t,int st,int en)
{
	t = ++sl;
	if(st == en) {az[t] = arr[st];return;}
	int mid = (st + en) >> 1;
	build(tree[t][0], st, mid);
	build(tree[t][1], mid + 1, en);
	update(t);
}
void set(int t,int st,int en)
{
	if(qr < st || ql > en) return;
	if(st == en){az[t] %= qv;return;}
	int mid = (st + en) >> 1;
	if(az[tree[t][0]]) set(tree[t][0], st, mid);
	if(az[tree[t][1]]) set(tree[t][1], mid + 1, en);
	update(t);
}
long long qry(int t,int st,int en)
{
	if(ql <= st && en <= qr) return az[t];
	int mid = (st + en) >> 1;
   long long	ret = 0;
	if(ql <= mid) ret += qry(tree[t][0], st, mid);
	if(qr > mid) ret += qry(tree[t][1], mid + 1, en);
	return ret;
}
void change(int t,int st,int en)
{
	if(st == en) {az[t] = qv;return;}
	int mid = (st + en) >> 1;
	if(ql <= mid) change(tree[t][0], st, mid);
	else change(tree[t][1], mid + 1, en);
	update(t);
}
int n, Q;

void init()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
	scanf("%d", &Q);
	build(root, 1, n);
}

void solve()
{
	int t;
	for(int i = 1; i <= Q; ++i)
	{
		scanf("%d", &t);
		if(t == 1)
		{
			scanf("%d%d%d", &ql, &qr, &qv);
			set(root, 1, n);
		}
		else if(t == 2)
		{
			scanf("%d%d", &ql, &qv);
			change(root, 1, n);
		}
		else
		{
			scanf("%d%d", &ql, &qr);
			cout<< qry(root, 1, n)<<endl;
		}
	}
//	while(clock() < 950);
}

int main()
{
	freopen("review.in", "r", stdin);
	freopen("review.out", "w", stdout);
	init();
	solve();
	return 0;
}

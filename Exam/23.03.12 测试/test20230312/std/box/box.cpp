#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int max_n = 5e3 + 10;
int n, a[max_n], p[max_n], tot = 0;

inline int get_num()
{
	int ans = 0;
	bool flag = false;
	char c;
	while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
	if (isdigit(c)) ans = c - '0';
	else flag = true;
	while (isdigit(c = getchar())) ans = ans * 10 + c - '0';
	return (flag ? -1 : 1) * ans;
}

inline void solve()
{
	for (int i = 1; i <= n; i++)
		if (!tot) 
			p[++tot] = 1;
		else
		{
			int wh = 0, maxx = 0;
			for (int j = 1; j <= tot; j++)
				if (a[i] >= p[j] && p[j] > maxx) maxx = p[j], wh = j;
			if (!wh)
				p[++tot] = 1;
			else
				p[wh]++;
		}
	cout << tot << endl; 
}

int main()
{
	freopen("box.in", "r", stdin);
	freopen("box.out", "w", stdout);
	n = get_num();
	for (int i = 1; i <= n; i++) a[i] = get_num();
	sort(a + 1, a + 1 + n);
	
	solve();
}

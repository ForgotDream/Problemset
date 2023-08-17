#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5005;

int n;
int a[N];

void init()
{
	string input;
	cin >> input;

	n = input.size();
	for(int i = 0; i < n; ++ i)
		a[i] = input[i] == '(' ? 1 : -1;
}

int f[2][N][3];

// 0 : Not Reversed yet
// 1 : Reversing
// 2 : Reversed already

void solve()
{
	for(int j = 0; j < n; ++ j)
		for(int k = 0; k < 3; ++ k)
			f[0][j][k] = 0;
		
	f[0][0][0] = 1;

	int prev = 0, next = 1;

	for(int i = 0; i < n; ++ i)
	{
		for(int j = 0; j < n; ++ j)
			for(int k = 0; k < 3; ++ k)
				f[next][j][k] = 0;

		for(int j = 0; j <= i && i + j <= n; ++ j)
		{
			// k == 0 : Not Reversed yet
			if(f[prev][j][0])
			{
				if(a[i] < 0 && j > 0) f[next][j-1][0] = 1;
				else if(a[i] > 0) f[next][j+1][0] = 1;

				// Turn into Reversed
				if(a[i] > 0 && j > 0) f[next][j-1][1] = 1;
				else if(a[i] < 0) f[next][j+1][1] = 1;
			}

			// k == 1 :
			if(f[prev][j][1])
			{
				if(a[i] > 0 && j > 0) f[next][j-1][1] = 1;
				else if(a[i] < 0) f[next][j+1][1] = 1;

				if(a[i] < 0 && j > 0) f[next][j-1][2] = 1;
				else if(a[i] > 0) f[next][j+1][2] = 1;
			}

			// k == 2:
			if(f[prev][j][2])
			{
				if(a[i] < 0 && j > 0) f[next][j-1][2] = 1;
				else if(a[i] > 0) f[next][j+1][2] = 1;
			}
		}

		swap(prev, next);
	}

	int ok = f[prev][0][0] | f[prev][0][1] | f[prev][0][2];
	if(ok) cout << "possible" << endl;
	else cout << "impossible" << endl;
}

int main()
{
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);

	int T;

	cin >> T;

	for(int i = 0; i < T; ++ i)
	{
		init();
		solve();		
	}

	return 0;
}

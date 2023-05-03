# include <cstdio>
# include <algorithm>
# include <cstring>
# include <iostream>
# include <cmath>
# include <queue>
using namespace std;
const int N = 1e5 + 50;
int sx, sy, tx, ty, ans;
int main()
{
	freopen("horse.in", "r", stdin);
	freopen("horse.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>sx >>sy >>tx >>ty;
	if(sx > tx) {
		swap(sx, tx);
		swap(sx, ty);
	}
	if(ty < sy) {
		ty = sy + (sy - ty);
	} 
	int x = abs(sx - tx), y = abs(sy - ty);
	if(y <= 2 && x <= 2) {
		if(x + y == 1) cout <<"3" <<endl;
		else if(x + y == 2) cout <<"2" <<endl;
		else if(x + y == 3) cout <<"1" <<endl;
		else if(x + y == 4) cout <<"4" <<endl;
		else cout <<"0" <<endl;
		return 0;   
	} 
	if(y > x) {
		ans += y / 2;
		ty -= (y / 2) * 2;
		if(x >= y / 2) {
			tx -= y / 2;
			x = abs(sx - tx);
			ans += x / 2;
			int tmp = x / 2;
			tx -= tmp * 2;
			if(x == 1) ans ++;
			else if(x == 2) ans += ((ty - sy) % 2 == 0);
			else if((x - 2) % 4 <= 1) ans ++;
			else if((x - 2) % 4 == 2) ans += 2;
		}
	}
	else {
		ans += x / 2;
		tx -= (x / 2) * 2;
		if(y >= x / 2) {
			ty -= x / 2;
			y = abs(ty - sy);
			ans += y / 2;
			int tmp = y / 2;
			ty -= tmp * 2;
			
			if(y == 1) ans ++;
			else if(y == 2) ans += ((tx - sx) % 2 == 0);
			else if((y - 2) % 4 <= 1) ans ++;
			else if((y - 2) % 4 == 2) ans += 2;
		}
		
	}
	cout <<ans <<endl;
	return 0;
}

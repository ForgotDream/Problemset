#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 1000;

struct bign {
	int d[maxn], len;

	void clean() { while (len > 1 && !d[len - 1]) len--; }

	bign()          { memset(d, 0, sizeof(d)); len = 1; }
	bign(int num)   { *this = num; }
	bign(char* num) { *this = num; }
	bign operator = (const char* num) {
		memset(d, 0, sizeof(d)); len = strlen(num);
		for (int i = 0; i < len; i++) d[i] = num[len - 1 - i] - '0';
		clean();
		return *this;
	}
	bign operator = (int num) {
		char s[20]; sprintf(s, "%d", num);
		*this = s;
		return *this;
	}

	bign operator + (const bign& b) {
		bign c = *this; int i;
		for (i = 0; i < b.len; i++) {
			c.d[i] += b.d[i];
			if (c.d[i] > 9) c.d[i] %= 10, c.d[i + 1]++;
		}
		while (c.d[i] > 9) c.d[i++] %= 10, c.d[i]++;
		c.len = max(len, b.len);
		if (c.d[i] && c.len <= i) c.len = i + 1;
		return c;
	}
	bign operator - (const bign& b) {
		bign c = *this; int i;
		for (i = 0; i < b.len; i++) {
			c.d[i] -= b.d[i];
			if (c.d[i] < 0) c.d[i] += 10, c.d[i + 1]--;
		}
		while (c.d[i] < 0) c.d[i++] += 10, c.d[i]--;
		c.clean();
		return c;
	}
	bign operator * (const bign& b)const {
		int i, j; bign c; c.len = len + b.len;
		for (j = 0; j < b.len; j++) for (i = 0; i < len; i++)
				c.d[i + j] += d[i] * b.d[j];
		for (i = 0; i < c.len - 1; i++)
			c.d[i + 1] += c.d[i] / 10, c.d[i] %= 10;
		c.clean();
		return c;
	}
	bign operator / (const bign& b) {
		int i, j;
		bign c = *this, a = 0;
		for (i = len - 1; i >= 0; i--)
		{
			a = a * 10 + d[i];
			for (j = 0; j < 10; j++) if (a < b * (j + 1)) break;
			c.d[i] = j;
			a = a - b * j;
		}
		c.clean();
		return c;
	}
	bign operator % (const bign& b) {
		int i, j;
		bign a = 0;
		for (i = len - 1; i >= 0; i--)
		{
			a = a * 10 + d[i];
			for (j = 0; j < 10; j++) if (a < b * (j + 1)) break;
			a = a - b * j;
		}
		return a;
	}
	bign operator += (const bign& b) {
		*this = *this + b;
		return *this;
	}

	bool operator <(const bign& b) const {
		if (len != b.len) return len < b.len;
		for (int i = len - 1; i >= 0; i--)
			if (d[i] != b.d[i]) return d[i] < b.d[i];
		return false;
	}
	bool operator >(const bign& b) const {return b < *this;}
	bool operator<=(const bign& b) const {return !(b < *this);}
	bool operator>=(const bign& b) const {return !(*this < b);}
	bool operator!=(const bign& b) const {return b < *this || *this < b;}
	bool operator==(const bign& b) const {return !(b < *this) && !(b > *this);}

	string str() const {
		char s[maxn] = {};
		for (int i = 0; i < len; i++) s[len - 1 - i] = d[i] + '0';
		return s;
	}
};

istream& operator >> (istream& in, bign& x)
{
	string s;
	in >> s;
	x = s.c_str();
	return in;
}

ostream& operator << (ostream& out, const bign& x)
{
	out << x.str();
	return out;
}

int n, m;
bign num;
bign f[100][100], val[100][100];
bign pow_10[50], sum[100];

void pre() {
	pow_10[0] = "1";
	for (int i = 1; i <= 50; i++) pow_10[i] = pow_10[i - 1] * (bign)10;
	for (int i = 0; i < num.len; i++) sum[i + 1] = sum[i] + (bign)num.d[i] * pow_10[i];
	for (int i = 1; i <= 50; i++)
		for (int j = i; j <= 50; j++)
			val[i][j] = /*sum[j] - sum[i - 1] * pow_10[j - i + 1]*/ sum[j] / pow_10[i - 1];
	// cout << sum[4] << " " << sum[1] << " " << pow_10[4 - 2 + 1] << endl;
	// cout << val[2][4] << endl;
	for (int i = 1; i <= n; i++) f[i][0] = val[1][i];
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) 
			for (int k = j; k < i; k++) 
				if (f[i][j] < f[k][j - 1] * val[k + 1][i]) f[i][j] = f[k][j - 1] * val[k + 1][i];
	cout << f[n][m] << endl;
	return;
}

int main() {
	cin >> n >> m;
	cin >> num;
	pre();
	solve();
	return 0;
}
/**
 * @file    P2437 蜜蜂路线.cpp
 * @author  ForgotDream
 * @brief   递推 + 高精
 * @date    2023-02-11
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 10050;

struct BigInt {
	int d[N], len;

	void clean() { while (len > 1 && !d[len - 1]) len--; }

	BigInt()          { memset(d, 0, sizeof(d)); len = 1; }
	BigInt(int num)   { *this = num; }
	BigInt(char* num) { *this = num; }
	BigInt operator = (const char* num) {
		memset(d, 0, sizeof(d)); len = strlen(num);
		for (int i = 0; i < len; i++) d[i] = num[len - 1 - i] - '0';
		clean();
		return *this;
	}
	BigInt operator = (int num) {
		char s[20]; sprintf(s, "%d", num);
		*this = s;
		return *this;
	}

	BigInt operator + (const BigInt& b) {
		BigInt c = *this; int i;
		for (i = 0; i < b.len; i++) {
			c.d[i] += b.d[i];
			if (c.d[i] > 9) c.d[i] %= 10, c.d[i + 1]++;
		}
		while (c.d[i] > 9) c.d[i++] %= 10, c.d[i]++;
		c.len = max(len, b.len);
		if (c.d[i] && c.len <= i) c.len = i + 1;
		return c;
	}
	BigInt operator - (const BigInt& b) {
		BigInt c = *this; int i;
		for (i = 0; i < b.len; i++) {
			c.d[i] -= b.d[i];
			if (c.d[i] < 0) c.d[i] += 10, c.d[i + 1]--;
		}
		while (c.d[i] < 0) c.d[i++] += 10, c.d[i]--;
		c.clean();
		return c;
	}
	BigInt operator * (const BigInt& b)const {
		int i, j; BigInt c; c.len = len + b.len;
		for (j = 0; j < b.len; j++) for (i = 0; i < len; i++)
				c.d[i + j] += d[i] * b.d[j];
		for (i = 0; i < c.len - 1; i++)
			c.d[i + 1] += c.d[i] / 10, c.d[i] %= 10;
		c.clean();
		return c;
	}
	BigInt operator / (const BigInt& b) {
		int i, j;
		BigInt c = *this, a = 0;
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
	BigInt operator % (const BigInt& b) {
		int i, j;
		BigInt a = 0;
		for (i = len - 1; i >= 0; i--)
		{
			a = a * 10 + d[i];
			for (j = 0; j < 10; j++) if (a < b * (j + 1)) break;
			a = a - b * j;
		}
		return a;
	}
	BigInt operator += (const BigInt& b) {
		*this = *this + b;
		return *this;
	}

	bool operator <(const BigInt& b) const {
		if (len != b.len) return len < b.len;
		for (int i = len - 1; i >= 0; i--)
			if (d[i] != b.d[i]) return d[i] < b.d[i];
		return false;
	}
	bool operator >(const BigInt& b) const {return b < *this;}
	bool operator<=(const BigInt& b) const {return !(b < *this);}
	bool operator>=(const BigInt& b) const {return !(*this < b);}
	bool operator!=(const BigInt& b) const {return b < *this || *this < b;}
	bool operator==(const BigInt& b) const {return !(b < *this) 
												&& !(b > *this);}

	string str() const {
		char s[N] = {};
		for (int i = 0; i < len; i++) s[len - 1 - i] = d[i] + '0';
		return s;
	}
};

istream& operator >> (istream& in, BigInt& x) {
	string s;
	in >> s;
	x = s.c_str();
	return in;
}

ostream& operator << (ostream& out, const BigInt& x) {
	out << x.str();
	return out;
}

BigInt f[1050];
int m, n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> m >> n;

	f[1] = 1, f[2] = 1;
	for (int i = 3; i <= n - m + 1; i++) f[i] = f[i - 1] + f[i - 2];

	cout << f[n - m + 1] << '\n';

	return 0;
}
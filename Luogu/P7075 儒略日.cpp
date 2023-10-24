/**
 * @file    P7075 儒略日.cpp
 * @author  ForgotDream
 * @brief   模拟
 * @date    2023-02-05
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int FourYear = 366 + 365 * 3, FourHundredYear = 100 * FourYear - 3;
static const int G = 4712 / 4 * FourYear + 365, M = 2299161;
int Q;
int days[] = {365, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Note：-4713 是闰年

bool isLeap(int year) {
	if (year < 0) {
		year = 3 - year;
		return year % 4 == 0;
	}
	if (year % 400 == 0) return true;
	if (year % 4 == 0) {
		if (year <= 1582) return true;
		else {
			if (year % 100 == 0) return false;
			return true;
		} 
	}
	return false;
}

void calcBC(i64 day) {
	++day;	
	int curY = -4713;
	int rst = day % FourYear, four = day / FourYear;

	curY += 4 * four;

	while (rst > 0) {
		rst -= days[0] + isLeap(curY);
		curY++;
	}
	curY--, rst += days[0] + isLeap(curY);
	
	int curM = 1;
	while (rst > 0) {
		rst -= days[curM] + (isLeap(curY) && curM == 2);
		curM++;
	}
	curM--, rst += days[curM] + (isLeap(curY) && curM == 2);

	cout << rst << ' ' << curM << ' ' << -curY << " BC\n";
	return;
}

void calcBefore1582(i64 day) {
	// cerr << G << '\n';
	day -= G;
	int curY = 1;
	int rst = day % FourYear, four = day / FourYear;

	curY += 4 * four;

	while (rst > 0) {
		rst -= days[0] + isLeap(curY);
		curY++;
	}
	curY--, rst += days[0] + isLeap(curY);
	
	int curM = 1;
	while (rst > 0) {
		rst -= days[curM] + (isLeap(curY) && curM == 2);
		curM++;
	}
	curM--, rst += days[curM] + (isLeap(curY) && curM == 2);

	cout << rst << ' ' << curM << ' ' << curY << '\n';
	return;
}

void calcAfter1582(i64 day) {
	day -= M;
	int curY = 1582;
	
	if (day <= 77) {
		int curM = 10, curD = 15;
		cerr << day << '\n';
		for (int i = 1; i <= day; i++) {
			curD++;
			// cerr << curD << ' ' << curM << ' ' << i << '\n';
			if (curD == days[curM]) curM++, curD = 0;
		}
		if (curD == 0) curM--, curD = days[curM];
		cout << curD << ' ' << curM << ' ' << curY << '\n';
		return;
	}

	day -= 77, curY = 1583;
	int rst = day % FourHundredYear, four = day / FourHundredYear;
	curY += 400 * four;

	// cerr << curY << ' ' << rst << '\n';

	while (rst > 0) {
		rst -= days[0] + isLeap(curY);
		curY++;
	}
	curY--, rst += days[0] + isLeap(curY);

	// cerr << rst << '\n';

	int curD = 0, curM = 1;
	for (int i = 1; i <= rst; i++) {
		curD++;
		if (curD == days[curM] + (curM == 2 && isLeap(curY))) curM++, curD = 0;
	}
	if (curD == 0) curM--, curD = days[curM] + (curM == 2 && isLeap(curY));

	cout << curD << ' ' << curM << ' ' << curY << '\n';
	return;
}

void debug() {
	i64 res = 0;
	// for (int i = 1; i <= 1582; i++) res += 365 + isLeap(i);
	for (int i = 1; i <= 9; i++) res += days[i] + (i == 2 && isLeap(1582));
	res += 4;
	// cerr << res + 4712 / 4 * FourYear << '\n';
	cerr << (1721423 == G) << ' ' << G << '\n';
	// cerr << res << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> Q;

	// debug();

	while (Q--) {
		i64 day;
		cin >> day;
		if (day <= G) calcBC(day);
		else if (day < M) calcBefore1582(day);
		else calcAfter1582(day);
	}

	return 0;
}
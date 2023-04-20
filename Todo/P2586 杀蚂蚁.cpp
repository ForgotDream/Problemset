/**
 * @file    P2586 杀蚂蚁.cpp
 * @author  ForgotDream
 * @brief   模拟
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 10, T = 2e5 + 50, S = 25;
int n, m;
int clk;
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
/**
 * Meanings of Index:
 * 	0 stands for S (South)
 * 	1 stands for N (North)
 * 	2 stands for E (East)
 * 	3 stands for W (West)
 */
int target;
int val[N][N];

struct Ant {
	static short antCnt;
	int x, y;
	int level, hp;
} ant[T];

struct Turrent {
	int x, y;
	int curTarget;
	int damage, radius;
} turrent[S];

/**
 * @brief 			模拟蚂蚁的移动行为
 * 
 * @param id 		移动的蚂蚁的 ID
 */
void move(int id) {
	
	return;
}

/**
 * @brief 			判断蚂蚁是否在激光塔的攻击路径上，
 *					即能否被攻击到
 * 
 * @param dst 		激光塔当前攻击的蚂蚁 ID
 * @param tgt 		激光塔尝试攻击的蚂蚁 ID
 * @param tur 		激光塔 ID
 * @return true   	可以攻击到
 * @return false 	不能攻击到
 */
bool canAtk(int dst, int tgt, int tur) {
	// int ddx = 
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;

	return 0;
}
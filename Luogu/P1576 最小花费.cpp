#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

template<class T>
void read(T& x) {
	int flag = 1;
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			flag = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	x *= flag;
	return;
}

struct Edge{
	int to;
	double w;
};
struct Node {
	double dis;
	int u;
	bool operator> (const Node& x) const {
		return dis > x.dis;
	}
	bool operator< (const Node& x) const {
		return dis > x.dis;
	}
};

const int M = 10050;
vector<Edge> e[M];
priority_queue<Node, vector<Node>, greater<Node> > pq;
// priority_queue<Node> pq;
double f[M];
bool vis[M];
int n, m, a, b;

void dijkstra(int s) {
	memset(f, 0x50, sizeof f);
	// printf("%.8lf\n", 100 * f[1]);
	f[s] = 1;
	pq.push({1, s});
	while(!pq.empty()) {
		auto h = pq.top().u;
		pq.pop();
		if (vis[h]) continue;
		vis[h] = true;
		for (auto i : e[h]) {
			// cout << 1 << endl;
			int to = i.to; 
			double w = i.w;
			if (f[to] > f[h] * w) {
				f[to] = f[h] * w;
				// cout << to << ' ' << f[to] << endl;
				pq.push({f[to], to});
			}
		}
	}
	return;
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		int u, v, tmp;
		read(u), read(v), read(tmp);
		e[v].push_back({u, 1 / (1 - tmp * (double)0.01)});
		e[u].push_back({v, 1 / (1 - tmp * (double)0.01)});
		// cout << 1 / (1 - tmp * (double)0.01) << endl;
	}
	read(a), read(b);
	// cout << e[b].size() << endl;
	dijkstra(b);
	printf("%.8lf\n", 100 * f[a]);
	return 0;
}
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

struct Node {
	string str;
	Node *pre, *suc;
};
int n;
string tmp;

int main() {
	Node *head, *tail, *cur;
	head = tail = nullptr;
	while (getline(cin, tmp) && tmp != "end") {
		cur = new Node;
		cur->str = tmp;
		if (head == nullptr) head = tail = cur;
		else tail->suc = cur, cur->pre = tail, tail = cur;
	}
	cur = tail;
	while (true) {
		cout << cur->str << endl;
		if (cur == head) break;
		cur = cur->pre;
	}
	return 0;
}
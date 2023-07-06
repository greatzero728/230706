#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
#endif
	
	int s, d, t; scanf("%d %d %d", &s, &d, &t);
	int n; scanf("%d", &n);
	vector<int> vec;
	vec.push_back(0), vec.push_back(d);
	vec.push_back(s - d), vec.push_back(s);
	
	return 0;
}

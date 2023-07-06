#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 1010101;

int num[NN];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
#endif
	
	for(int d = 1; d < NN; d++) {
		for(int i = d; i < NN; i += d) num[i] += d;
	}
	
	int t; scanf("%d", &t);
	while(t--) {
		int x; scanf("%d", &x);
		if(num[x] > x) puts("abundant");
		else if(num[x] < x) puts("deficient");
		else puts("perfect");
	}
	return 0;
}

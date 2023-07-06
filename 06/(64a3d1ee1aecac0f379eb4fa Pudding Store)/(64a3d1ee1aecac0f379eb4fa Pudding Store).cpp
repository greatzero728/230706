#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int mod = 998244353;

int power(int a, int b) {
	int ans = 1;
	for(; b; b >>= 1, a = (INT)a * a % mod) {
		if(b & 1) ans = (INT)ans * a % mod;
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
#endif
	
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		if(n <= 3) {
			int ans = 1;
			for(int i = 1; i <= n; i++) ans *= i;1
			printf("%d\n", ans);
			continue;
		}
		printf("%d\n", 6LL * power(2, n - 3) % mod);
	}
	return 0;
}

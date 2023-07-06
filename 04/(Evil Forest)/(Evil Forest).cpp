#include<bits/stdc++.h>

using namespace std;

int a[1010];

int calc() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += a[i] + (a[i] + 9) / 10;
	}
	return ans;
}

int main() {
	int t; scanf("%d", &t);
	for(int i = 1; i <= t; i++) {
		printf("Case #%d: ", i);
		printf("%d\n", calc());
	}
	return 0;
}
#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 505050, MM = NN << 1, inf = 0x3f3f3f3f;

vector<int> adj[NN];
int n, m, s, t;
int a[NN], b[NN], c[NN];
int vst[NN], runs;

bool can_go(int mn) {
	for(int i = 1; i <= n; i++) adj[i].clear();
	for(int i = m; i--; ) if(c[i] >= mn) {
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}
	queue<int> q; q.push(s);
	vst[s] = ++runs;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(u == t) return 1;
		for(int v : adj[u]) if(vst[v] ^ runs) {
			vst[v] = runs, q.push(v);
		}
	}
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
#endif
	
	scanf("%d %d", &n, &m);
	for(int i = m; i--; ) {
		scanf("%d %d %d", a + i, b + i, c + i);
	}
	scanf("%d %d", &s, &t);
	
	int st = 1, ed = 1e9 + 1;
	while(ed - st > 1) {
		int md = st + ed >> 1;
		if(can_go(md)) st = md;
		else ed = md;
	}
	if(can_go(st)) printf("%d\n", st);
	else puts("-1");
	return 0;
}
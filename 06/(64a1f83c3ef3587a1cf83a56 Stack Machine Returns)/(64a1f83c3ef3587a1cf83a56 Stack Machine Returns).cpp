#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 555;

struct Int {
	static const int len = NN, all = 1e8; // max_len = 8 * len
	int a[len], n, t;
	void c() {
		while(n && !a[n - 1]) n--;
		if(!n) t = 1;
		return;
	}
	void resize(int N) {
		n = N; while(N--) a[N] = 0;
		return;
	}
	Int(INT x) {
		n = 0, t = 1; if(x < 0) x = -x, t = -1;
		while(x) a[n++] = x % all, x /= all;
		c();
	}
	Int() : t(1) {n = 0;}
	Int(string s) {
		n = 0, t = 1;
		int L = 0, x = 0, b = 1, i = s.size();
		if(!s.empty() && s[0] == 45) L = 1, t = -1;
		while(i-- > L) {
			x += (s[i] - 48) * b, b *= 10;
			if(b >= all) a[n++] = x, x = 0, b = 1;
		}
		if(x) a[n++] = x;
		else c();
	}
	void pt() const {
		if(!n) {printf("0 "); return;}
		if(!~t) putchar(45);
		printf("%d", a[n - 1]);
		for(int i = n - 1; i--; ) printf("%.8d", a[i]);
		putchar(' ');
		return;
	}
	int cp(const Int &b) const {
		if(t ^ b.t) return t - b.t;
		if(!~t) return -(-*this).cp(-b);
		if(n ^ b.n) return n - b.n;
		for(int i = n; i--; ) if(a[i] ^ b.a[i]) {
			return a[i] - b.a[i];
		}
		return 0;
	}
	bool operator < (const Int &b) const {return cp(b) < 0;}
	bool operator > (const Int &b) const {return cp(b) > 0;}
	bool operator <= (const Int &b) const {return cp(b) <= 0;}
	bool operator >= (const Int &b) const {return cp(b) >= 0;}
	bool operator == (const Int &b) const {return !cp(b);}
	bool operator != (const Int &b) const {return cp(b);}
	Int operator - () const {
		Int r = *this; if(r.n) r.t = -r.t;
		return r;
	}
	Int operator + (const Int &b) const {
		if(!~t) return -(-*this + -b);
		if(!~b.t) return *this - -b;
		int N = max(n, b.n); Int r; r.resize(N + 1);
		for(int i = 0; i < N; i++) {
			if(i < n) r.a[i] += a[i];
			if(i < b.n) r.a[i] += b.a[i];
			if(r.a[i] >= all) r.a[i] -= all, r.a[i + 1]++;
		}
		return r.c(), r;
	}
	Int operator - (const Int &b) const {
		if(!~t) return -(-*this - -b);
		if(!~b.t) return *this + -b;
		if(*this < b) return -(b - *this);
		Int r; r.resize(n);
		for(int i = 0; i < n; i++) {
			r.a[i] += a[i];
			if(i < b.n) r.a[i] -= b.a[i];
			if(r.a[i] < 0) r.a[i] += all, r.a[i + 1]--;
		}
		return r.c(), r;
	}
	Int operator * (const Int &b) {
		Int r; INT c, up = 0; r.resize(n + b.n + 1);
		for(int i = 0, j; i < r.n; i++) {
			c = up, up = 0, j = max(0, i - b.n + 1);
			for(; j < n && j <= i; j++) {
				c += (INT)a[j] * b.a[i - j];
				if(c > 9999999999999999) up += c / all, c %= all;
			}
			up += c / all, r.a[i] = c %= all;
		}
		return r.t = t * b.t, r.c(), r;
	}
	Int operator / (const Int &b) {
		if(n < b.n) return 0;
		Int r, x = b; r.resize(n - b.n + 1);
		int f = t, i = r.n, d, m, u;
		for(t = x.t = 1; i--; ) {
			for(d = 0, u = all - 1; d < u; ) {
				m = r.a[i] = d + u + 1 >> 1;
				if(r * x > *this) u = m - 1;
				else d = m;
			}
			r.a[i] = d;
		}
		return t = f, r.t = t * b.t, r.c(), r;
	}
	Int operator % (const Int &b) {
		return *this - *this / b * b;
	}
};

int t, flag = 0;
stack<Int> s;
vector<int> a;

void RTE() {
	puts("Runtime error"), exit(0);
	return;
}
void TL() {
	puts("Time limit exceeded"), exit(0);
	return;
}
void CPE() {
	puts("Compilation error"), exit(0);
	return;
}

void solve(int L, int R) {
	if(L > R) return;
	stack<int> arr;
	for(int i = L; i <= R; i++) {
		if(arr.empty()) {
			if(a[i] == 1) {//ADD
				if(s.size() < 2) RTE();
				Int x = s.top(); s.pop();
				Int y = s.top(); s.pop();
				s.push(x + y);
				if(--t < 0) TL();
			}
			else if(a[i] == 3) {//COPY
				if(s.size() == 0) RTE();
				Int x = s.top(); s.push(x);
				if(--t < 0) TL();
			}
			else if(a[i] == 4) {//DEC
				if(s.size() == 0) RTE();
				Int x = s.top(); s.pop();
				s.push(x - Int(1));
				if(--t < 0) TL();
			}
			else if(a[i] == 10) {//INC
				if(s.size() == 0) RTE();
				Int x = s.top(); s.pop();
				s.push(x + Int(1));
				if(--t < 0) TL();
			}
			else if(a[i] == 11) {//POP
				if(s.size() == 0) RTE();
				s.pop();
				if(--t < 0) TL();
			}
			else if(a[i] == 12) {//PUSHZ
				s.push(0);
				if(--t < 0) TL();
			}
			else if(a[i] == 13) {//SUB
				if(s.size() < 2) RTE();
				Int x = s.top(); s.pop();
				Int y = s.top(); s.pop();
				s.push(x - y);
				if(--t < 0) TL();
			}
			else if(a[i] == 14) {//SWAP2
				if(s.size() < 2) RTE();
				Int x = s.top(); s.pop();
				Int y = s.top(); s.pop();
				s.push(x), s.push(y);
				if(--t < 0) TL();
			}
			else if(a[i] == 15) {//SWAP3
				if(s.size() < 3) RTE();
				Int x = s.top(); s.pop();
				Int y = s.top(); s.pop();
				Int z = s.top(); s.pop();
				s.push(y), s.push(x), s.push(z);
				if(--t < 0) TL();
			}
		}
		
		if(a[i] == 2) {//BEGIN
			arr.push(i);
		}
		else if(a[i] == 5) {//END
			int st = arr.top(); arr.pop();
			
			if(arr.empty()) {
				if(a[st - 1] == 6) {//IF EZ THEN
					if(s.size() == 0) RTE();
					if(--t < 0) TL();
					if(s.top() == 0) solve(st + 1, i - 1);
				}
				else if(a[st - 1] == 7) {//IF GZ THEN
					if(s.size() == 0) RTE();
					if(--t < 0) TL();
					if(s.top() > 0) solve(st + 1, i - 1);
				}
				else if(a[st - 1] == 8) {//IF HAVE1 THEN
					if(--t < 0) TL();
					if(s.size() >= 1) solve(st + 1, i - 1);
				}
				else if(a[st - 1] == 9) {//IF HAVE2 THEN
					if(--t < 0) TL();
					if(s.size() >= 2) solve(st + 1, i - 1);
				}
				else if(a[st - 1] == 16) {//WHILE EZ DO
					while(1) {
						if(s.size() == 0) RTE();
						if(--t < 0) TL();
						if(s.top() == 0) solve(st + 1, i - 1);
						else break;
					}
				}
				else if(a[st - 1] == 17) {//WHILE GZ DO
					while(1) {
						if(s.size() == 0) RTE();
						if(--t < 0) TL();
						if(s.top() > 0) solve(st + 1, i - 1);
						else break;
					}
				}
				else if(a[st - 1] == 18) {//WHILE HAVE1 DO
					while(1) {
						if(--t < 0) TL();
						if(s.size() >= 1) solve(st + 1, i - 1);
						else break;
					}
				}
				else if(a[st - 1] == 19) {//WHILE HAVE2 DO
					while(1) {
						if(--t < 0) TL();
						if(s.size() >= 2) solve(st + 1, i - 1);
						else break;
					}
				}
			}
		}
	}
	return;
}

char str[10101010] = " ";

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
#endif
	
	int n; scanf("%d %d", &n, &t);
	while(n--) {
		int x; scanf("%d", &x);
		s.push(x);
	}
	
	int f = 0;
	scanf(" ");
	while(gets(str + 1)) {
		int c = -1, n = 0;
		for(int i = 1; str[i]; i++) {
			if(isspace(str[i])) {
				str[i] = ' ';
				if(str[n] == ' ') continue;
			}
			str[++n] = str[i];
		}
		if(n && str[n] == ' ') n--;
		str[n + 1] = 0;
		
		if(!strcmp(str + 1, "ADD")) c = 1;
		else if(!strcmp(str + 1, "BEGIN")) {
			if(a.size() == 0 || a.back() % 10 < 6) CPE();
			f++, c = 2;
		}
		else if(!strcmp(str + 1, "COPY")) c = 3;
		else if(!strcmp(str + 1, "DEC")) c = 4;
		else if(!strcmp(str + 1, "END")) {
			if(!f--) CPE();
			c = 5;
		}
		else if(!strcmp(str + 1, "IF EZ THEN")) c = 6;
		else if(!strcmp(str + 1, "IF GZ THEN")) c = 7;
		else if(!strcmp(str + 1, "IF HAVE1 THEN")) c = 8;
		else if(!strcmp(str + 1, "IF HAVE2 THEN")) c = 9;
		else if(!strcmp(str + 1, "INC")) c = 10;
		else if(!strcmp(str + 1, "POP")) c = 11;
		else if(!strcmp(str + 1, "PUSHZ")) c = 12;
		else if(!strcmp(str + 1, "SUB")) c = 13;
		else if(!strcmp(str + 1, "SWAP2")) c = 14;
		else if(!strcmp(str + 1, "SWAP3")) c = 15;
		else if(!strcmp(str + 1, "WHILE EZ DO")) c = 16;
		else if(!strcmp(str + 1, "WHILE GZ DO")) c = 17;
		else if(!strcmp(str + 1, "WHILE HAVE1 DO")) c = 18;
		else if(!strcmp(str + 1, "WHILE HAVE2 DO")) c = 19;
		else if(n) CPE();
		
		if(~c) a.push_back(c);
	}
	if(f) CPE();
	
	solve(0, a.size() - 1);
	if(t < 0) puts("Time limit exceeded"), exit(0);
	
	vector<Int> vec;
	while(!s.empty()) vec.push_back(s.top()), s.pop();
	
	puts("Accepted");
	printf("%d\n", vec.size());
	for(int i = vec.size(); i--; ) vec[i].pt();
	return 0;
}
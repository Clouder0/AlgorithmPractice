#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN = 2e5 + 5;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
int n, x, p[MAXN];
ll goal, b[MAXN], l[MAXN], r[MAXN], s[MAXN];
bool cmp(int x, int y) {
	return s[x] > s[y];
}
ll calc(int pos, ll t) {
	if (t <= b[pos]) return t * l[pos];
	else return b[pos] * l[pos] + (t - b[pos]) * r[pos];
}
ll check(ll t) {
	ll ans = 0, sum = 0;
	int lft = t % x;
	if (lft == 0) lft = x;
	int cnt = (t - lft) / x;
	//assert(cnt < n);
	for (int i = 1; i <= cnt; i++)
		sum += s[p[i]];
	for (int i = cnt + 1; i <= n; i++)
		chkmax(ans, sum + calc(p[i], lft));
	sum += s[p[cnt + 1]];
	for (int i = 1; i <= cnt; i++)
		chkmax(ans, sum - s[p[i]] + calc(p[i], lft));
	return ans;
}
int main() {
	read(n), read(x);
	for (int i = 1; i <= n; i++) {
		read(b[i]), read(l[i]), read(r[i]);
		s[i] = b[i] * l[i] + (x - b[i]) * r[i];
		p[i] = i, goal += b[i] * l[i];
	}
	sort(p + 1, p + n + 1, cmp);
	if (goal == 0) {
		writeln(0);
		return 0;
	}
	ll l = 1, r = 1ll * n * x;
	while (l < r) {
		ll mid = (l + r) / 2;
		if (check(mid) >= goal) r = mid;
		else l = mid + 1;
	}
	writeln(l);
	return 0;
}
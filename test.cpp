#include<bits/stdc++.h>
using namespace std;
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int M = 200000 + 5;
#define il inline
#define re register
#define Next( i, u ) for( re int i = head[u]; i; i = e[i].next )
#define rep( i, s, t ) for( re int i = s; i <= t; ++ i ) 
#define drep( i, t, s ) for( re int i = t; i >= s; -- i )
struct E {
	int to, next, w;
}e[M * 2];
int n, cnt, tot, book[5], ans, sum, rt;
int head[M], vis[M], dp[M], size[M], dis[M];

int gcd( int a, int b ) {
	if( b == 0 ) return a;
	return gcd( b, a % b );
}
il void add( int x, int y, int z ) {
	e[++ cnt] = (E){ y, head[x], z }, head[x] = cnt;
	e[++ cnt] = (E){ x, head[y], z }, head[y] = cnt;
}
il void input() {
	n = read();
	int x, y, z;
	dp[0] = sum = n, rt = 0;
	rep( i, 1, n - 1 )  x = read(), y = read(), z = read(), add( x, y, z % 3 );
} 

void get_rt( int u, int fa ) {
	size[u] = 1, dp[u] = 0;
	Next( i, u ) {
		int v = e[i].to;
		if( vis[v] || v == fa ) continue;
		get_rt( v , u );
		size[u] += size[v];
		dp[u] = max( size[v], dp[u] );
	}
	dp[u] = max( dp[u], sum - size[u] );
	if( dp[u] < dp[rt] ) rt = u;
}

void get_dis( int x, int fa ) {
	++ book[dis[x] % 3];
	Next( i, x ) {
		int v = e[i].to;
		if( vis[v] || v == fa ) continue;
		dis[v] = ( dis[x] + e[i].w ) % 3;
		get_dis( v, x );
	}
}
il int doit( int x, int w ) {
	memset( book, 0, sizeof(book) ), dis[x] = w % 3;
	get_dis( x, 0 );
	printf("%d %d %d %d\n",x,book[0],book[1],book[2]);
	return book[2] * book[1] * 2 + book[0] * book[0];
}

il void solve( int u ) {
	printf("root: %d %d\n",u,size[u]);
	vis[u] = 1, ans += doit( u, 0 );
	printf("root: %d,val: %d\n",u,ans);
	Next( i, u ) {
		int v = e[i].to;
		if( vis[v] ) continue;
		ans -= doit( v, e[i].w % 3 );
		dp[0] = n, rt = 0, sum = size[v];
		get_rt( v, u ), solve( rt );
	}
}
signed main()
{
	input(), get_rt( 1, 0 ), solve( rt );
	int k = gcd( ans, n * n );
	printf("%d/%d", ans/k, n * n / k );
	return 0;
}
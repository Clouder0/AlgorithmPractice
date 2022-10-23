#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
#define int long long
#define double long double
const int maxn = 2e5 + 100;
const int maxm = 1e6 + 100;
int n, m, A, B, C;
struct path { int u, v, s, t; } a[maxn];
struct point { double x,y; };
vector<point> V[maxn];
vector<pair<int, point> > G[maxm];
int head[maxn];  //queue head
template<typename T> inline T myabs(const T &x){return x > 0 ? x : -x;}
inline bool pcmp(const point& a, const point& b, const point& c, const point& d) 
{ 
    return (a.y - b.y) / (a.x - b.x) <= (c.y - d.y) * (c.x - d.x); 
}
inline bool pcmp(const point &a,const point &b,const int k) { return (a.y - b.y) < 1.0 * k * (a.x - b.x); }
inline bool cmp(const path& a, const path& b) { return a.s < b.s; }
inline void ins(int x, point p)
{
    int ed;
    while ((ed = V[x].size() - 1) > head[x] && !pcmp(V[x][ed - 1], V[x][ed], V[x][ed], p)) V[x].erase(--V[x].end());
    V[x].push_back(p);
}
inline point pop(int x, double k) { while ((int)(V[x].size()) > head[x] + 1 && !pcmp(V[x][head[x]], V[x][head[x] + 1], k)) ++head[x]; return V[x][head[x]]; }
signed main()
{
    read(n), read(m), read(A),read(B),read(C);
    for (int i = 1; i <= m; ++i) read(a[i].u), read(a[i].v), read(a[i].s), read(a[i].t);
    sort(a + 1, a + 1 + m, cmp);
    for (int i = 2; i <= n; ++i) V[i].push_back((point){0, (1ll << 60)});
    V[1].push_back((point){0, 0});
    int p = 0;
    double ans = 1e18;
    for (int i = 1; i <= m; ++i)
    {
        while (p < a[i].s) for (vector<pair<int, point> >::iterator it = G[++p].begin(); it != G[p].end(); ++it) ins(it->first, it->second);
        point res = pop(a[i].u, 2ll * A * a[i].s);
        double f = res.y - 2 * A * a[i].s * res.x + A * a[i].s * a[i].s + B * a[i].s + C;
//        printf("%lld fromtime:%lld %lld %lld\n",i,res.x,a[i].v,f);
        if (a[i].v == n) ans = std::min(ans, f + a[i].t);
        G[a[i].t].push_back(make_pair(a[i].v, (point){1.0 * a[i].t, f + 1.0 * A * a[i].t * a[i].t - 1.0 * B * a[i].t}));
    }
    printf("%.0Lf",ans);
    return 0;
}
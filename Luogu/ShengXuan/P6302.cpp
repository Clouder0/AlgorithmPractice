#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 1e5 + 100;
const int maxm = 1e6 + 100;
const int maxt = 4e4 + 100;
int n, m, A, B, C;
struct path { int u, v, s, t; } P[maxm];
inline bool cmp(const path& a, const path& b) { return a.s < b.s; }
struct point { int x; long long y; };
vector<point> S[maxn];
int head[maxn];
vector<pair<int,point> > M[maxt];
inline bool fcmp(const point& a, const point& b, const point& c, const point& d)
{
    return (a.y - b.y) * (c.x - d.x) < (c.y - d.y) * (a.x - d.x);
}
inline bool kcmp(const point &a,const point &b,long long k) { return a.y - b.y > k * (a.x - b.x); }
inline void ins(int pos, point p)
{
    for (int ed = (int)(S[pos].size()) - 1; ed - 1 >= head[pos] && !fcmp(S[pos][ed - 1], S[pos][ed], S[pos][ed], p); --ed)
        S[pos].pop_back();
    S[pos].push_back(p);
}
inline point pop(int pos, long long k)
{
    while (head[pos] + 1 < (int)(S[pos].size()) && kcmp(S[pos][head[pos]],S[pos][head[pos] + 1],k)) ++head[pos];
    return S[pos][head[pos]];
}
int main()
{
    read(n), read(m), read(A), read(B), read(C);
    for (int i = 1; i <= m; ++i) read(P[i].u),read(P[i].v),read(P[i].s),read(P[i].t);
    sort(P + 1, P + 1 + m, cmp);
    int p = 0;
    long long ans = 1ll << 60;
    for (int i = 2; i <= n; ++i) S[i].push_back((point){0, (1ll << 50)});
    S[1].push_back((point){0, 0ll});
    for (int i = 1; i <= m; ++i) 
    {
        while (p < P[i].s)
            for (vector<pair<int, point> >::iterator it = M[++p].begin(); it != M[p].end(); ++it) ins(it->first, it->second);
        point res = pop(P[i].u, 2.0 * A * P[i].s);
        long long f = res.y - 2ll * A * P[i].s * res.x + 1ll * A * P[i].s * P[i].s + 1ll * B * P[i].s + C;
        if (P[i].v == n) ans = min(ans, f + P[i].t);
        else M[P[i].t].push_back(make_pair(P[i].v, (point){P[i].t, f + 1ll * A * P[i].t * P[i].t - 1ll * B * P[i].t}));
    }
    printf("%lld\n", ans);
    return 0;
}
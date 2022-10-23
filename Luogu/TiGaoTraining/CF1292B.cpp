#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
#define ll long long
ll x0, y0, ax, ay, bx, by, sx, sy, t;
const ll maxx = 1e18;
const int maxn = 200;
ll X[maxn], Y[maxn], cnt, res;
ll d[maxn][maxn];
ll myabs(ll x) { return x > 0 ? x : -x; }
ll getdis(ll x1, ll y1, ll x2, ll y2) { return myabs(x1 - x2) + myabs(y1 - y2); }
bool vis[200];
void dfs(int pos, ll num, ll nowt)
{
    res = std::max(res, num);
    for (int i = 1; i <= cnt; ++i)
        if (myabs(pos - i) < 2 && !vis[i] && nowt >= d[i][pos])
        {
            vis[i] = 1;
            dfs(i, num + 1, nowt - d[i][pos]);
            vis[i] = 0;
        }
}
int main()
{
    read(x0), read(y0), read(ax), read(ay), read(bx), read(by), read(sx), read(sy), read(t);
    ll nowx = x0, nowy = y0;
    for (int i = 0;; ++i)
    {
        if (getdis(nowx, nowy, sx, sy) <= t) X[++cnt] = nowx, Y[cnt] = nowy;
        if ((maxx - bx) / nowx < ax) break;
        if ((maxx - by) / nowy < ay) break;
        nowx = nowx * ax + bx, nowy = nowy * ay + by;
    }
    for (int i = 1; i <= cnt; ++i)
        for (int j = i + 1; j <= cnt; ++j) d[i][j] = d[j][i] = getdis(X[i], Y[i], X[j], Y[j]);
    //printf("%lld\n",cnt);
    for (int i = 1; i <= cnt; ++i)
        if (t >= getdis(sx, sy, X[i], Y[i]))
        {
            vis[i] = 1;
            dfs(i, 1, t - getdis(sx, sy, X[i], Y[i]));
            vis[i] = 0;
        }
    printf("%lld\n", res);
    return 0;
}
#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
using namespace std;
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
const int maxn = 5e5 + 100;
int n, m, s, k;
struct node
{
    int u,v,w;
}E[maxn];
bool cmp(const node& a, const node& b) 
{ 
    if(a.w == b.w) return a.u == s || a.v == s;
    return a.w < b.w; 
}
int fa[maxn];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
signed main()
{
    read(n), read(m), read(s), read(k);
    int maxx = -(1 << 30);
    for (int i = 1; i <= m; ++i) read(E[i].u), read(E[i].v), read(E[i].w),maxx = max(maxx,E[i].w);
    for (int i = 1; i <= m; ++i) if(E[i].u > E[i].v) swap(E[i].u,E[i].v);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int cnt = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (find(E[i].u) == find(E[i].v)) continue;
        fa[find(E[i].u)] = find(E[i].v), ++cnt;
    }
    if(cnt < n - 1) {puts("Impossible");return 0;}
    cnt = 0;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) if (E[i].u == s || E[i].v == s) E[i].w += (1 << 30);
    sort(E + 1,E + 1 + m,cmp);
    for (int i = 1; i <= m; ++i) if (E[i].u == s || E[i].v == s) E[i].w -= (1 << 30);
    for (int i = 1; i <= m; ++i)
    {
        if (find(E[i].u) == find(E[i].v)) continue;
        fa[find(E[i].u)] = find(E[i].v), cnt += (E[i].u == s || E[i].v == s);
    }
    if(cnt > k) {puts("Impossible");return 0;}
    int l = -maxx, r = maxx, mid, ans = (1 << 30);
    while (l <= r)
    {
        mid = l + r >> 1;   
        for (int i = 1; i <= m; ++i) if(E[i].u == s || E[i].v == s) E[i].w += mid;
        sort(E + 1,E + 1 + m,cmp);
        for (int i = 1; i <= m; ++i) if(E[i].u == s || E[i].v == s) E[i].w -= mid;
        for (int i = 1; i <= n; ++i) fa[i] = i;
        int num = 0;
        for (int i = 1; i <= m; ++i) 
        {
            if (find(E[i].u) == find(E[i].v)) continue;
            fa[find(E[i].u)] = find(E[i].v), num += (E[i].u == s || E[i].v == s);
        }
        if(num >= k) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    if (ans == (1 << 30)) { puts("Impossible"); return 0; }
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) if(E[i].u == s || E[i].v == s) E[i].w += ans;
    long long sum = 0,scnt = 0;
    sort(E + 1, E + 1 + m, cmp);
    for (int i = 1; i <= m; ++i)
    {
        if (find(E[i].u) == find(E[i].v)) continue;
        fa[find(E[i].u)] = find(E[i].v), sum += E[i].w, scnt += (E[i].u == s || E[i].v == s);
    }
    printf("%lld\n",sum - 1ll * k * ans);
    return 0;
}
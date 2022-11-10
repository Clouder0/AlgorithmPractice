#include <cstdio>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;
const int maxn = 1e6 + 100;
#define int long long
int n, q, h[maxn], p[maxn], k, np[maxn];
long long ans;
int sav[11000];
template <typename T>
inline void read(T& r)
{
    r = 0;
    static char c;
    c = getchar();
    for (; !isdigit(c);) c = getchar();
    for (; isdigit(c); c = getchar()) r = r * 10 + c - 48;
}
void solve()
{
    ans = 0;
    long long nowans = 0;
    set<int> S;
    S.insert(p[1]);
    for (int i = 2; i <= n; ++i)
    {
        int now = p[i];
        if (S.find(now) != S.end()) 
        {
            ans += nowans;
            continue;
        }
        S.insert(now);
        set<int>::iterator it = S.find(now);
        set<int>::iterator pre = it;
        set<int>::iterator nxt = it;
        ++nxt;
        if (it == S.begin())
        {
            nowans += sav[abs(h[now] - h[*nxt])];
            goto end;
        }
        --pre;
        if (nxt == S.end())
        {
            nowans += sav[abs(h[now] - h[*pre])];
            goto end;
        }
        nowans = nowans - sav[abs(h[*nxt] - h[*pre])] + sav[abs(h[now] - h[*nxt])] + sav[abs(h[now] - h[*pre])];
    end:
        ans += nowans;
    }
}
int s[maxn], top, t[maxn];
inline int calc(int a, int b) { return sav[abs(h[a] - h[b])]; }
void solve2()
{
    for (int i = 1; i <= n; ++i) t[p[i]] = i;
    ans = 0;
    top = 0;
    s[++top] = 1;
    for (int i = 2; i <= n; ++i)
    {
        int last = n + 1;
        while (top && t[s[top]] > t[i]) 
            ans += 1ll * calc(i, s[top]) * (last - t[s[top]]), last = t[s[top]], --top;
        if (top) ans += 1ll * calc(i, s[top]) * (last - t[i]);
        s[++top] = i;
    }
}
signed main()
{
    read(n), read(q);
    for (int i = 1; i <= n; ++i) read(h[i]);
    for (int i = 1; i <= n; ++i) read(p[i]);
    for (int i = 0; i <= 10001; ++i) sav[i] = i * i;
    solve2();
    printf("%lld\n", ans);
    for (int i = 1; i <= q; ++i)
    {
        read(k);
        k += ans;
        k %= n;
        for (int j = 1; j + k <= n; ++j) np[j] = p[j + k];
        for (int j = 1; j <= k; ++j) np[n - k + j] = p[j];
        for (int j = 1; j <= n; ++j) p[j] = np[j];
//        puts("!!!");
//        for(int j = 1;j<=n;++j) printf("%lld ",p[i]);
//        puts("");
//        puts("!!!");
        solve2();
        printf("%lld\n", ans);
    }
    return 0;
}
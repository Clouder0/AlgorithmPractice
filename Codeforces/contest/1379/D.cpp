#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
template<typename T>
inline T abs(const T &a){return a > 0 ? a : -a;}
const int maxn = 1e5 + 100;
int n,H,M,K,half;
int num[maxn*6],tot;
int h[maxn],m[maxn];
int sum[maxn*6];
inline void add(int x)
{
    num[++tot] = x;
    num[++tot] = x - 1;
    num[++tot] = x - K + 1;
}
int main()
{
    read(n),read(H),read(M),read(K);
    half = M / 2;
    num[++tot] = -1,num[++tot] = 0,num[++tot] = M - 1;
    for (int i = 1; i <= n; ++i) 
    {
        read(h[i]), read(m[i]);
        if(m[i] >= half) m[i] -= half;
        add(m[i]),add(m[i] + half);
    }
    std::sort(num + 1,num + 1 + tot);
    tot = std::unique(num + 1,num + 1 + tot) - num - 1;
    for (int i = 1; i <= n; ++i)
        m[i] = std::lower_bound(num + 1, num + 1 + tot, m[i]) - num, sum[m[i]]++;
    for (int i = 1; i <= tot; ++i)  sum[i] += sum[i-1];
    int ans = 1<<30,anst = 0;
    int end = std::lower_bound(num + 1,num + 1 + tot,M - 1) - num;
    int es = std::lower_bound(num + 1,num + 1 + tot,M - K) - num;
    int eans = sum[end] - sum[es - 1];
    for (int i = 1; i <= tot; ++i) 
    {
        int t = num[i];
        if(t < 0) continue;
        if(t >= half) break;
        if(t >= K)
        {
            //[t - K + 1,t - 1] + [t + half - K + 1,t + half - 1] + [M - K,M - 1]
            int l1 = t - K + 1,r1 = t - 1;
            int l2 = t + half - K + 1,r2 = t + half - 1;
            l1 = std::lower_bound(num + 1,num + 1 + tot,l1) - num;
            r1 = std::lower_bound(num + 1,num + 1 + tot,r1) - num;
            l2 = std::lower_bound(num + 1,num + 1 + tot,l2) - num;
            r2 = std::lower_bound(num + 1,num + 1 + tot,r2) - num;
            int tans = eans + sum[r2] - sum[l2 - 1] + sum[r1] - sum[l1 - 1];
            if(tans < ans) ans = tans,anst = i;
        }
        else
        {
            //[,t - 1] + [t + half - K + 1,t + half - 1] + [M - K,M - 1]
            int r1 = t - 1;
            int l2 = t + half - K + 1,r2 = t + half - 1;
            r1 = std::lower_bound(num + 1,num + 1 + tot,r1) - num;
            l2 = std::lower_bound(num + 1,num + 1 + tot,l2) - num;
            r2 = std::lower_bound(num + 1,num + 1 + tot,r2) - num;
            int tans = eans + sum[r1] + sum[r2] - sum[l2 - 1];
            if(tans < ans) ans = tans,anst = i;
        }
    }
    printf("%d %d\n",ans,num[anst]);
    int t = num[anst];
    if(t >= K)
    {
        int l1 = t - K + 1, r1 = t - 1;
        int l2 = t + half - K, r2 = t + half - 1;
        l1 = std::lower_bound(num + 1, num + 1 + tot, l1) - num;
        r1 = std::lower_bound(num + 1, num + 1 + tot, r1) - num;
        l2 = std::lower_bound(num + 1, num + 1 + tot, l2) - num;
        r2 = std::lower_bound(num + 1, num + 1 + tot, r2) - num;
        for (int i = 1; i <= n; ++i) 
            if((m[i] >= l1 && m[i] <= r1) || (m[i] >= l2 && m[i] <= r2) || (m[i] >= es && m[i] <= end)) 
                printf("%d\n",i);
    }
    else
    {
        int r1 = t - 1;
        int l2 = t + half - K + 1, r2 = t + half - 1;
        r1 = std::lower_bound(num + 1, num + 1 + tot, r1) - num;
        l2 = std::lower_bound(num + 1, num + 1 + tot, l2) - num;
        r2 = std::lower_bound(num + 1, num + 1 + tot, r2) - num;
        for (int i = 1; i <= n; ++i)
            if ((m[i] <= r1) || (m[i] >= l2 && m[i] <= r2) || (m[i] >= es && m[i] <= end))
                printf("%d\n", i);
    }
    return 0;
}
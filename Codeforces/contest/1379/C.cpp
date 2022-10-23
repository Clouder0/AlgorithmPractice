#include <cstdio>
#include <algorithm>
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
const int maxn = 1e5 + 100;
struct node
{
    unsigned long long a,b,id;
}A[maxn],B[maxn];
bool cmp(const node &x,const node &y){return x.a > y.a;}
bool cmp2(const node &x,const node &y){return x.b > y.b;}
unsigned long long sum[maxn];
int T,n,m;
bool vis[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(m),read(n);
        for (int i = 1; i <= n; ++i) read(A[i].a), read(A[i].b), B[i].a = A[i].a, B[i].b = A[i].b, A[i].id = B[i].id = i;
        std::sort(A + 1, A + 1 + n, cmp), std::sort(B + 1, B + 1 + n, cmp2);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + A[i].a, vis[i] = 0;
        unsigned long long ans = 0;
        if (m <= n) ans = sum[m];
        int l = 1;
        for (int i = 1; i <= n; ++i)
        {
            while (l <= n && l <= m && A[l].a > B[i].b) vis[A[l].id] = 1, ++l;
            if(l == m + 1)
            {
                if (vis[B[i].id]) ans = std::max(ans, sum[m]);
                else if (!vis[B[i].id]) ans = std::max(ans, sum[m - 1] + B[i].a);
                break;
            }
            if(l == n + 1)
            {
                ans = std::max(ans,sum[n] + (m - n) * B[i].b);
                break;
            }
            if (vis[B[i].id] && m - l + 1 >= 0) ans = std::max(ans, sum[l - 1] + (m - l + 1) * B[i].b);
            else if (!vis[B[i].id] && m - l >= 0) ans = std::max(ans, sum[l - 1] + (m - l) * B[i].b + B[i].a);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
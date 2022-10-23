#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define DEBUG
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
const int maxn = 40;
int n;
struct node
{
    int x,y,p;
}A[maxn];
int mindis[maxn],steps;
long long ans[maxn],tans;
template<typename T>
inline T _abs(const T &x){return x > 0 ? x : -x;}
void dfs(int x)
{
    if(steps > n) return;
    tans = 0;
    for (int i = 1; i <= n; ++i) tans += 1ll * A[i].p * mindis[i];
    ans[steps] = std::min(ans[steps],tans);
    if(x > n) return;
//    printf("%d %d %d\n",steps,ans[steps],tans);
    dfs(x + 1);
    int copy[16];
    for (int i = 1; i <= n; ++i) copy[i] = mindis[i];
    
    ++steps;
    for (int i = 1; i <= n; ++i) mindis[i] = std::min(mindis[i],_abs(A[i].x - A[x].x));
    dfs(x + 1);
    --steps;
    for (int i = 1; i <= n; ++i) mindis[i] = copy[i];
    
    ++steps;
    for (int i = 1; i <= n; ++i) mindis[i] = std::min(mindis[i],_abs(A[i].y - A[x].y));
    dfs(x + 1);
    --steps;
    for (int i = 1; i <= n; ++i) mindis[i] = copy[i];
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(A[i].x),read(A[i].y),read(A[i].p);
    for(int i = 1;i<=n;++i) mindis[i] = std::min(_abs(A[i].x),_abs(A[i].y));
    for (int i = 0; i <= n; ++i) ans[i] = 1ll << 62;
    dfs(1);
    for(int i = 0;i<=n;++i) printf("%lld\n",ans[i]);
    return 0;
}
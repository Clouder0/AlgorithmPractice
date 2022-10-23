#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 3e5 + 100;
int T, n, a[maxn], b[maxn], to[maxn];
vector<int> Va[maxn], Vb[maxn];
int f[maxn], tag[maxn], now;
inline void check(int x)
{
    if (tag[x] != now) f[x] = 1 << 30, tag[x] = now;
}
void update(int x, int k)
{
    //    printf("update %d %d\n",x,k);
    for (; x > 0; x -= (x & -x)) check(x), f[x] = std::min(f[x], k);
}
int ask(int x)
{
    int res = 1 << 30;
    for (; x <= n; x += (x & -x)) check(x), res = std::min(f[x], res);
    return res;
}
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) Va[i].clear(), Vb[i].clear();
        for (int i = 1; i <= n; ++i) read(a[i]), Va[a[i]].push_back(i);
        for (int i = 1; i <= n; ++i) read(b[i]), Vb[b[i]].push_back(i);
        for (int i = 1; i <= n; ++i)
        {
            if (Va[i].size() != Vb[i].size()) goto no;
            for (auto it = Va[i].begin(), it2 = Vb[i].begin(); it != Va[i].end(); ++it, ++it2)
                to[*it] = *it2;
        }
        //        for(int i = 1;i<=n;++i) printf("%d ",to[i]);
        //        puts("");
        ++now;
        for (int i = 1; i <= n; ++i)
        {
            //            printf("to %d\n",i);
            //            printf("ask %d %d\n", to[i] + 1,ask(to[i] + 1));
            if (ask(to[i] + 1) < a[i]) goto no;
            update(to[i], a[i]);
        }
        puts("YES");
        continue;
    no:
        puts("NO");
    }
    return 0;
}
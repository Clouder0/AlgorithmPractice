#include <cstdio>
#include <algorithm>
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
const int maxn = 2e5 + 100;
int T, n, a[maxn], b[maxn], vis[maxn], s[maxn], top;
vector<int> V[33];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        top = 0;
        for (int i = 1; i <= n; ++i) read(a[i]), b[i] = a[i], vis[i] = 0;
        for (int i = 0; i <= 30; ++i) V[i].clear();
        for (int k = 30; k >= 0; --k)
            for (int i = 1; i <= n; ++i)
                if (((a[i] >> k) & 1)) V[k].push_back(i);
        int now = 0;
        for (int k = 30; k >= 0; --k)
        {
            if(V[k].empty()) continue;
            if((now >> k) & 1) continue;
            int maxx = 0;
            for (vector<int>::iterator it = V[k].begin(); it != V[k].end(); ++it)
            {
                b[*it] &= (~now);
                if (!maxx)
                    maxx = *it;
                else if (b[*it] > b[maxx])
                    maxx = *it;
            }
            now |= b[maxx], s[++top] = maxx, vis[maxx] = 1;
        }
        for (int i = 1; i <= top; ++i) printf("%d ",a[s[i]]);
        for (int i = 1; i <= n; ++i) if(!vis[i]) printf("%d ",a[i]);
        puts("");
    }
    return 0;
}
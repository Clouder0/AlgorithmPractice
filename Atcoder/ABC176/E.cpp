#include <cstdio>
#include <bitset>
#include <algorithm>
#include <vector>
#include <ctype.h>
const int bufSize = 1e6;
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
const int maxn = 3e5 + 100;
int n, m, k;
int row[maxn], col[maxn];
bool vis[maxn];
bitset<maxn> bs;
vector<int> v[maxn];
int main()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= k; ++i) 
    {
        int x, y;
        read(x), read(y), row[x]++, col[y]++, v[x].push_back(y);
    }
    int maxx = 0,maxy = 0;
    for (int i = 1; i <= n; ++i) maxx = std::max(maxx, row[i]);
    for (int i = 1; i <= m; ++i) maxy = std::max(maxy, col[i]);
    for (int i = 1; i <= m; ++i) if (col[i] == maxy) bs.set(i);
    int ans = maxx + maxy - 1;
    for (int i = 1; i <= n; ++i)
        if (row[i] == maxx)
        {
            bitset<maxn> ts;
            for (vector<int>::iterator it = v[i].begin(); it != v[i].end(); ++it) ts.set(*it);
            ts.flip();
            if ((ts & bs).any())
            {
                ans = maxx + maxy;
                break;
            }
        }
    printf("%d\n",ans);
    return 0;
}
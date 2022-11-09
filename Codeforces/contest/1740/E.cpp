#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctype.h>
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
const int maxn = 1e5 + 100;
int n, fa[maxn], h[maxn], f[maxn];
vector<int> son[maxn];
int main()
{
    read(n);
    for (int i = 2; i <= n; ++i) read(fa[i]), son[fa[i]].push_back(i);
    for (int i = n; i; --i)
    {
        f[i] = max(f[i], h[i] + 1);
        h[fa[i]] = max(h[fa[i]], h[i] + 1);
        f[fa[i]] += f[i];
    }
    printf("%d\n", f[1]);
    return 0;
}
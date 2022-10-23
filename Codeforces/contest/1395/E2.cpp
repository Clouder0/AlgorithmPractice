#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
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
int n,m,k;
int U[maxn],V[maxn];
vector<int> E[maxn];
set
int main()
{
    read(n),read(m),read(k);
    for(int i = 1;i<=m;++i)
    {
        int a,b,c;
        read(a),read(b),read(c);
        U[c] = a,V[c] = b;
    }
    for(int i = 1;i<=m;++i) E[U[i]].push_back(V[i]);

    return 0;
}
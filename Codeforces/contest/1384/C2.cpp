#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <queue>
using namespace std;
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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
int T, n;
char A[maxn], B[maxn];
int fa[40], siz[40];
int find(const int& x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y) return;
    fa[y] = x, siz[x] += siz[y];
}
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        read(A + 1), read(B + 1);
        int times = 0;
        for (int i = 1; i <= n; ++i) if (A[i] > B[i]) goto fail;
        for (int i = 1; i <= 20; ++i) fa[i] = i, siz[i] = 1;
        for (int i = 1; i <= n; ++i) if (A[i] < B[i]) merge(A[i] - 'a' + 1, B[i] - 'a' + 1);
        for (int i = 1; i <= 20; ++i) if (find(i) == i) times += siz[i] - 1;
        printf("%d\n", times);
        continue;
    fail:
        puts("-1");
    }
    return 0;
}
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
const int inf = 1 << 30;
int n, m, up, cnt;
struct node
{
    int pos, id;
} A[maxn << 1];
inline bool cmp(const node& a, const node& b) { return a.pos != b.pos ? a.pos < b.pos : a.id < b.id; }
int f[1 << 9], popc[1 << 9];
int vis[15];
int main()
{
    read(n), read(m), read(up);
    for (int i = 1, l, r; i <= n; ++i) read(l), read(r), A[++cnt].pos = l, A[cnt].id = i, A[++cnt].pos = r + 1, A[cnt].id = -i;
    std::sort(A + 1, A + 1 + cnt, cmp);
    for (int i = 1; i < (1 << up); ++i) f[i] = -inf, popc[i] = popc[i >> 1] ^ (i & 1);
    for (int i = 1; i < cnt; ++i)
    {
        int len = A[i + 1].pos - A[i].pos, k;
        if (A[i].id > 0)
        {
            for (int j = 0; j < 8; ++j) if (!vis[j]) { vis[j] = A[i].id, k = j; break; }
            for (int j = (1 << up) - 1; j >= 0; --j)
                if (j & (1 << k)) f[j] = f[j ^ (1 << k)] + len * popc[j]; else f[j] = f[j] + len * popc[j];
        }
        else
        {
            for (int j = 0; j < 8; ++j) if (vis[j] == -A[i].id) { vis[j] = 0, k = j; break; }
            for (int j = 0; j < (1 << up); ++j)
                if (j & (1 << k)) f[j] = -inf;
                else f[j] = std::max(f[j], f[j ^ (1 << k)]) + len * popc[j];
        }
    }
    int res = 0;
    for (int i = 0; i < (1 << up); ++i) res = std::max(res, f[i]);
    printf("%d\n", res);
    return 0;
}
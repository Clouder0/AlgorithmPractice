#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int maxn = 210;
int R, G, B;
long long f[maxn][maxn][maxn], ans;
int r[maxn], g[maxn], b[maxn];
bool cmp(const int& a, const int& b) { return a > b; }
void dfs(int i, int j, int k)
{
    if (f[i][j][k] != -1) return;
    f[i][j][k] = 0;
    if (i && j) dfs(i - 1, j - 1, k), f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k] + r[i] * g[j]);
    if (i && k) dfs(i - 1, j, k - 1), f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k - 1] + r[i] * b[k]);
    if (j && k) dfs(i, j - 1, k - 1), f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k - 1] + g[j] * b[k]);
    if (i) dfs(i - 1, j, k), f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k]);
    if (j) dfs(i, j - 1, k), f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k]);
    if (k) dfs(i, j, k - 1), f[i][j][k] = std::max(f[i][j][k], f[i][j][k - 1]);
    ans = std::max(ans, f[i][j][k]);
}
int main()
{
    read(R), read(G), read(B);
    for (int i = 1; i <= R; ++i) read(r[i]);
    for (int i = 1; i <= G; ++i) read(g[i]);
    for (int i = 1; i <= B; ++i) read(b[i]);
    std::sort(r + 1, r + 1 + R, cmp);
    std::sort(g + 1, g + 1 + G, cmp);
    std::sort(b + 1, b + 1 + B, cmp);
    memset(f, -1, sizeof(f));
    dfs(R, G, B);
    printf("%lld\n", ans);
    return 0;
}
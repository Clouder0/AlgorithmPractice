#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <vector>
const int bufSize = 1e6;
#define DEBUG
using namespace std;
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
    for (; !isalpha(c); c = nc()) ;
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
const int maxn = 1e5 + 100;
const int maxm = 22;
int T, n;
char A[maxn], B[maxn];
int G[maxm][maxm];
int G2[maxm];
vector<int> s[maxm];
int fa[maxm];
int find(const int& x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y) return;
    if (s[x].size() < s[y].size()) swap(x, y);
    fa[y] = x;
    for (vector<int>::iterator it = s[y].begin(); it != s[y].end(); ++it) s[x].push_back(*it);
    s[y].clear();
}
int f[1 << 21], num[1 << 21];
inline void init()
{
    for (int i = 1; i <= 20; ++i) fa[i] = i, s[i].clear(), s[i].push_back(i);
    for (int i = 1; i <= 20; ++i)
        for (int j = 1; j <= 20; ++j) G[i][j] = 0;
}
int main()
{
    for (int i = 0; i < (1 << 20); ++i)
        for (int x = i; x; x >>= 1) num[i] += (x & 1);
    read(T);
    while (T--)
    {
        read(n);
        read(A + 1), read(B + 1);
        init();
        for (int i = 1; i <= n; ++i)
        {
            if (A[i] == B[i]) continue;
            G[A[i] - 'a' + 1][B[i] - 'a' + 1] = 1;
            merge(A[i] - 'a' + 1, B[i] - 'a' + 1);
        }
        int ans = 0;
        for (int i = 1; i <= 20; ++i)
        {
            if (find(i) != i) continue;
            for (unsigned int j = 0; j < s[i].size(); ++j) G2[j] = 0;
            for (unsigned int j = 0; j < s[i].size(); ++j)
                for (unsigned int k = 0; k < s[i].size(); ++k)
                    if (G[s[i][j]][s[i][k]]) G2[j] |= (1 << k);
            int maxx = (1 << (int)s[i].size());
            for (int status = 0; status < maxx; ++status) f[status] = 0;
            f[0] = 1;
            int res = 0;
            for (int status = 0; status < maxx; ++status)
            {
                if (!f[status]) continue;
                res = max(res, num[status]);
                for (unsigned int j = 0; j < s[i].size(); ++j) 
                    if (!(status & (1 << j)) && !(G2[j] & status)) f[status | (1 << j)] = 1;
            }
            ans += 2 * s[i].size() - res - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
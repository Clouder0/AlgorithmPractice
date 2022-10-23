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
const int maxn = 510, maxm = 4e5;
struct node
{
    int type, x1, x2, y1, y2, val, id;
} A[maxm], q1[maxm], q2[maxm];
int n, m, cnt, ans[maxm];
int sum[maxn][maxn],vis[maxn][maxn],tim;
inline void check(int x, int y) { if (vis[x][y] != tim) sum[x][y] = 0, vis[x][y] = tim; }
inline void clear() { ++tim; }
inline void add(int x, int y, int k)
{
    for (int tx = x; tx <= n; tx += tx & -tx)
        for (int ty = y; ty <= n; ty += ty & -ty)
            check(tx, ty), sum[tx][ty] += k;
}
inline int ask(int x,int y)
{
    int res = 0;
    for (int tx = x; tx > 0; tx -= tx & -tx)
        for (int ty = y; ty > 0; ty -= ty & -ty)
            check(tx, ty), res += sum[tx][ty];
    return res;
}
inline int ask(int x1, int y1, int x2, int y2)
{
    return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
}
void solve(int l, int r, int L, int R)
{
    if(L > R) return;
    if(l == r)
    {
        for (int i = L; i <= R; ++i) if (A[i].type) ans[A[i].id] = l;
        return;
    }
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = L; i <= R; ++i)
    {
        if(A[i].type)
        {
            int num = ask(A[i].x1, A[i].y1, A[i].x2, A[i].y2);
            if(num >= A[i].val) q1[++cnt1] = A[i];
            else A[i].val -= num, q2[++cnt2] = A[i];
        }
        else
        {
            if (A[i].val <= mid) add(A[i].x1, A[i].y1, 1), q1[++cnt1] = A[i];
            else q2[++cnt2] = A[i];
        }
    }
    clear();
    for (int i = 1; i <= cnt1; ++i) A[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) A[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= n; ++j) read(x), A[++cnt].type = 0, A[cnt].x1 = i, A[cnt].y1 = j, A[cnt].val = x;
    for (int i = 1; i <= m; ++i) read(A[++cnt].x1), read(A[cnt].y1), read(A[cnt].x2), read(A[cnt].y2), read(A[cnt].val), A[cnt].id = i, A[cnt].type = 1;
    solve(0, 1000000000, 1, cnt);
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}
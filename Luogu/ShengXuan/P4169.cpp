#include <cstdio>
#include <algorithm>
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
const int maxm = 1e6 + 100;
int n, m, cnt, ANS[maxn], qnum, maxx, maxy;
struct node
{
    int type, t, x, y, id;
} A[maxn << 1], B[maxn << 1], C[maxn << 1];
const int inf = 1 << 29;
namespace U
{
int minn[maxm], vis[maxm], tim;
inline void clear() { ++tim; }
inline void check(int x) { if (vis[x] != tim) minn[x] = inf, vis[x] = tim; }
inline void add(int x, int k) { for (++x; x <= maxy + 1; x += x & -x) check(x), minn[x] = min(minn[x], k); }
inline int ask(int x) { int res = inf; for (++x; x > 0; x -= x & -x) check(x),res = min(res, minn[x]); return res; }
}
namespace D
{
int minn[maxm], vis[maxm], tim;
inline void clear() { ++tim; }
inline void check(int x) { if (vis[x] != tim) minn[x] = inf, vis[x] = tim; }
inline void add(int x, int k) { for (++x; x > 0; x -= x & -x) check(x), minn[x] = min(minn[x], k); }
inline int ask(int x) { int res = inf; for (++x; x <= maxy + 1; x += x & -x) check(x),res = min(res, minn[x]); return res; }
}  // namespace D
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int p = l, p1 = l, p2 = mid + 1;
    bool need = 0;
    for (int i = mid + 1; i <= r; ++i) need |= (A[i].type == 2);
    if(!need) goto end;
    U::clear(), D::clear();
    for (int i = mid + 1; i <= r; ++i)
    {
        while (p <= mid && A[p].x <= A[i].x)
        {
            if (A[p].type == 1) U::add(A[p].y, -A[p].x - A[p].y), D::add(A[p].y, -A[p].x + A[p].y);
            ++p;
        }
        if(A[i].type == 2)
        {
            ANS[A[i].id] = min(ANS[A[i].id], A[i].x + A[i].y + U::ask(A[i].y));
            ANS[A[i].id] = min(ANS[A[i].id], A[i].x - A[i].y + D::ask(A[i].y + 1));
        }
    }
    end:
    for (p = l; p1 <= mid && p2 <= r;) B[p++] = A[p1].x <= A[p2].x ? A[p1++] : A[p2++];
    while (p1 <= mid) B[p++] = A[p1++];
    while (p2 <= r) B[p++] = A[p2++];
    for (int i = l; i <= r; ++i) A[i] = B[i];
}
int main()
{
    read(n), read(m);
    for (int i = 1, x, y; i <= n; ++i)
    {
        read(x), read(y), A[++cnt].x = x, A[cnt].y = y, A[cnt].t = 0, A[cnt].type = 1;
        maxx = std::max(maxx, x), maxy = std::max(maxy, y);
    }
    for (int i = 1, opt, x, y; i <= m; ++i)
    {
        read(opt), read(x), read(y), maxx = std::max(maxx, x), maxy = std::max(maxy, y);
        if (opt == 1) A[++cnt].type = 1, A[cnt].t = i, A[cnt].x = x, A[cnt].y = y;
        else A[++cnt].type = 2, A[cnt].t = i, A[cnt].x = x, A[cnt].y = y, A[cnt].id = ++qnum;
    }
    for (int i = 1; i <= qnum; ++i) ANS[i] = 1 << 30;
    for (int i = 1; i <= cnt; ++i) C[i] = A[i];
    cdq(1, cnt);
    for (int i = 1; i <= cnt; ++i) A[i] = C[i], A[i].x = maxx - A[i].x;
    cdq(1, cnt);
    for (int i = 1; i <= qnum; ++i) printf("%d\n", ANS[i]);
    return 0;
}
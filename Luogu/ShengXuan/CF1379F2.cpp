#include <cstdio>
#include <algorithm>
#include <set>
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
const int maxn = 2e5 + 100;
int n, m, q;
int minr[maxn << 2], maxl[maxn << 2];
bool cant[maxn << 2];
set<int> LS[maxn], RS[maxn];
#define ls p << 1
#define rs p << 1 | 1
void build(int l, int r, int p)
{
    minr[p] = 1 << 30, maxl[p] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
}
inline void pushup(int p)
{
    cant[p] = cant[ls] | cant[rs] | (minr[ls] <= maxl[rs]);
    minr[p] = min(minr[ls], minr[rs]);
    maxl[p] = max(maxl[ls], maxl[rs]);
}
void update(int l, int r, int p, int pos)
{
    if(l == r)
    {
        minr[p] = RS[l].size() ? *RS[l].begin() : 1 << 30;
        maxl[p] = LS[l].size() ? *--LS[l].end() : 0;
        cant[p] = minr[p] <= maxl[p];
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(l, mid, ls, pos);
    else update(mid + 1, r, rs, pos);
    pushup(p);
}
int main()
{
    read(n), read(m), read(q);
    build(1, n, 1);
    for (int i = 1, x, y; i <= q; ++i)
    {
        read(x), read(y);
        int gx = (x + 1) >> 1, gy = (y + 1) >> 1;
        if (x & 1)
        {
            //R
            set<int>::iterator it = RS[gx].find(gy);
            if (it == RS[gx].end()) RS[gx].insert(gy);
            else RS[gx].erase(it);
        }
        else
        {
            //L
            set<int>::iterator it = LS[gx].find(gy);
            if (it == LS[gx].end()) LS[gx].insert(gy);
            else LS[gx].erase(it);
        }
        update(1, n, 1, gx);
        puts(cant[1] ? "NO" : "YES");
    }
    return 0;
}
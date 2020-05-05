#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0;
    register bool f = 0;
    register char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = 1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    return f ? -x : x;
}
char cr[200];
int tt;
inline void print(int x, char k = '\n')
{
    if (!x)
        putchar('0');
    if (x < 0)
        putchar('-'), x = -x;
    while (x)
        cr[++tt] = x % 10 + '0', x /= 10;
    while (tt)
        putchar(cr[tt--]);
    putchar(k);
}
const int maxn = 100010;
const int ratio = 4;
struct lef
{
    int v, w, ls, rs;
} t[maxn * 80];
int rt, tot, ans, lastans;
void nnd(int &o, int v, int w, int ls, int rs)
{
    o = ++tot;
    t[o] = (lef){v, w, ls, rs};
}
void merge(int &o, int x, int y)
{
    nnd(o, t[y].v, t[x].w + t[y].w, x, y);
}
void pushup(int o)
{
    if (!t[o].ls)
    {
        t[o].w = 1;
        return;
    }
    t[o].w = t[t[o].ls].w + t[t[o].rs].w;
    t[o].v = t[t[o].rs].v;
}
void maintain(int o)
{
    if (t[t[o].ls].w > t[t[o].rs].w * ratio)
    {
        merge(t[o].rs, t[t[o].ls].rs, t[o].rs);
        t[o].ls = t[t[o].ls].ls;
    }
    if (t[t[o].rs].w > t[t[o].ls].w * ratio)
    {
        merge(t[o].ls, t[o].ls, t[t[o].rs].ls);
        t[o].rs = t[t[o].rs].rs;
    }
}
int qrk(int o, int k)
{
    if (t[o].w == 1)
        return 1;
    if (k <= t[t[o].ls].v)
        return qrk(t[o].ls, k);
    else
        return t[t[o].ls].w + qrk(t[o].rs, k);
}
int qnm(int o, int k)
{
    if (t[o].w == 1)
        return t[o].v;
    if (k <= t[t[o].ls].w)
        return qnm(t[o].ls, k);
    else
        return qnm(t[o].rs, k - t[t[o].ls].w);
}
void ins(int o, int x)
{
    if (t[o].w == 1)
    {
        nnd(t[o].ls, min(t[o].v, x), 1, 0, 0);
        nnd(t[o].rs, max(t[o].v, x), 1, 0, 0);
    }
    else
    {
        ins(x > t[t[o].ls].v ? t[o].rs : t[o].ls, x);
    }
    pushup(o);
    maintain(o);
}
void del(int o, int x)
{
    int wh, el;
    if (x <= t[t[o].ls].v)
        wh = t[o].ls, el = t[o].rs;
    else
        wh = t[o].rs, el = t[o].ls;
    if (t[wh].w == 1)
        if (x == t[wh].v)
        {
            t[o].ls = t[el].ls;
            t[o].rs = t[el].rs;
            t[o].v = t[el].v;
        }
        else
            return;
    else
        del(wh, x);
    pushup(o);
    maintain(o);
}
int pre(int rk, int x)
{
    return qnm(rt, qrk(rt, x) - 1);
}
int suf(int rk, int x)
{
    return qnm(rt, qrk(rt, x + 1));
}
signed main()
{
    int n = read(), m = read();
    nnd(rt, 2147483647, 1, 0, 0);
    for (int i = 1; i <= n; i++)
    {
        int a = read();
        ins(rt, a);
    }
    while (m--)
    {
        int opt = read(), x = read() ^ lastans;
        switch (opt)
        {
        case 1:
            ins(rt, x);
            break;
        case 2:
            del(rt, x);
            break;
        case 3:
            lastans = qrk(rt, x);
            break;
        case 4:
            lastans = qnm(rt, x);
            break;
        case 5:
            lastans = pre(rt, x);
            break;
        case 6:
            lastans = suf(rt, x);
            break;
        }
        printf("last %d %d %d\n",m,lastans,x);
        if (opt != 1 && opt != 2)
            ans ^= lastans;
    }
    print(ans);
    return 0;
}

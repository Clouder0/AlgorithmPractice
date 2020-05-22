#include <bits/stdc++.h>
<<<<<<< HEAD
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
=======

#define NS (1000005)
#define LGS (20)

#define INF (100000000)

using namespace std;

typedef long long LL;

template <typename _Tp>
inline void IN(_Tp &dig)
{
	char c;
	bool flag = 0;
	dig = 0;
	while (c = getchar(), !isdigit(c))
		if (c == '-')
			flag = 1;
	while (isdigit(c))
		dig = dig * 10 + c - '0', c = getchar();
	if (flag)
		dig = -dig;
}

struct graph
{
	int head[NS], nxt[NS << 1], to[NS << 1], sz;
	void init() { memset(head, -1, sizeof(head)), sz = 0; }
	graph() { init(); }
	void push(int a, int b) { nxt[sz] = head[a], to[sz] = b, head[a] = sz++; }
	int operator[](const int a) { return to[a]; }
} g;

int n, id[NS], dfn, q, k, h[NS], sz[NS], mn[NS], mx[NS], mnans, mxans;

int pre[NS][LGS + 1], dep[NS];

int sta[NS], top;

bool book[NS];

LL f[NS], tot;

void Init(int a, int fa)
{
	pre[a][0] = fa, dep[a] = dep[fa] + 1, id[a] = ++dfn;
	for (int i = 1; i <= LGS; i += 1)
		pre[a][i] = pre[pre[a][i - 1]][i - 1];
	for (int i = g.head[a]; ~i; i = g.nxt[i])
		if (g[i] != fa)
			Init(g[i], a);
}

int lca(int a, int b)
{
	if (dep[a] > dep[b])
		swap(a, b);
	for (int i = LGS; i >= 0; i -= 1)
		if (dep[pre[b][i]] >= dep[a])
			b = pre[b][i];
	if (a == b)
		return a;
	for (int i = LGS; i >= 0; i -= 1)
		if (pre[a][i] != pre[b][i])
			a = pre[a][i], b = pre[b][i];
	return pre[a][0];
}

bool cmp(int a, int b) { return id[a] < id[b]; }

void Dp(int a)
{
	printf("now %d\n",a);
	sz[a] = book[a], f[a] = 0;
	if (book[a])
		mn[a] = mx[a] = 0;
	else
		mn[a] = INF, mx[a] = -INF;
	for (int i = g.head[a], l; ~i; i = g.nxt[i])
	{
		Dp(g[i]), l = dep[g[i]] - dep[a];
		tot += (f[a] + sz[a] * l) * sz[g[i]] + f[g[i]] * sz[a];
		sz[a] += sz[g[i]], f[a] += f[g[i]] + l * sz[g[i]];
		mnans = min(mnans, mn[a] + mn[g[i]] + l);
		mxans = max(mxans, mx[a] + mx[g[i]] + l);
		mn[a] = min(mn[a], mn[g[i]] + l);
		mx[a] = max(mx[a], mx[g[i]] + l);
	}
}

int main(int argc, char const *argv[])
{
	IN(n);
	for (int i = 1, a, b; i < n; i += 1)
		IN(a), IN(b), g.push(a, b), g.push(b, a);
	Init(1, 0), IN(q);
	while (q--)
	{
		IN(k);
		for (int i = 1; i <= k; i += 1)
			IN(h[i]), book[h[i]] = 1;
		sort(h + 1, h + 1 + k, cmp);
		sta[top = 1] = 1, g.sz = 0, g.head[1] = -1;
		for (int i = 1, l; i <= k; i += 1)
			if (h[i] != 1)
			{
				l = lca(h[i], sta[top]);
				if (l != sta[top])
				{
					while (id[l] < id[sta[top - 1]])
						g.push(sta[top - 1], sta[top]), top--;
					if (id[l] > id[sta[top - 1]])
						g.head[l] = -1, g.push(l, sta[top]), sta[top] = l;
					else
						g.push(l, sta[top--]);
				}
				g.head[h[i]] = -1, sta[++top] = h[i];
			}
		for (int i = 1; i < top; i += 1)
			g.push(sta[i], sta[i + 1]);
		mnans = INF, mxans = -INF, tot = 0, Dp(1);
		printf("%lld %d %d\n", tot, mnans, mxans);
		for (int i = 1; i <= k; i += 1)
			book[h[i]] = 0;
	}
	return 0;
}
>>>>>>> 8a89711ace3019fbcef75e106e5f3dfd2a1b05b3

#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long

int t, n, m, k;
int root[N], res;

struct SEG
{
#define M N * 35
    int cnt, lson[M], rson[M];
    struct node
    {
        int tm, pos;
        ll Max;
        bool operator<(const node &r) const
        {
            return Max == r.Max ? tm < r.tm : Max < r.Max;
        }
    } a[M];

    void pushup(int id)
    {
        a[id] = max(a[lson[id]], a[rson[id]]);
    }

    void update(int &root, int l, int r, ll val, int tm, int pos)
    {
        if (!root)
        {
            root = ++cnt;
            lson[root] = rson[root] = 0;
            a[root].Max = a[root].tm = a[root].pos = 0;
        }
        if (l == r)
        {
            a[root].Max += val;
            a[root].tm = max(a[root].tm, tm);
            a[root].pos = pos;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lson[root], l, mid, val, tm, pos);
        else
            update(rson[root], mid + 1, r, val, tm, pos);
        pushup(root);
    }
} segtree;

void Init()
{
    segtree.cnt = 0;
    memset(root, 0, sizeof root);
    res = 0;
}

struct OP
{
    int a, b, c, tm;
    void scan(int tm)
    {
        this->tm = tm;
        scanf("%d%d%d", &a, &b, &c);
    }
} op[N];

void update(int a, int b, int c, int tm)
{
    int bef = segtree.a[root[a]].pos;
    segtree.update(root[a], 1, n, c, tm, b);
    int now = segtree.a[root[a]].pos;
    if (bef == now)
        return;
    if (bef)
    {
        if (segtree.a[root[bef]].pos == a)
            ++res;
        else
            --res;
    }
    if (now)
    {
        if (segtree.a[root[now]].pos == a)
            --res;
        else
            ++res;
    }
}

void Run()
{
    segtree.a[0].tm = 1000000; // 防止取max操作时误把空节点pushup上去
    scanf("%d", &t);
    while (t--)
    {
        Init();
        scanf("%d%d%d", &n, &k, &m);
        for (int i = 1; i <= k; ++i)
        {
            op[i].scan(i);
            update(op[i].a, op[i].b, op[i].c, i);
            update(op[i].b, op[i].a, op[i].c, i);
            if (i > m)
            {
                update(op[i - m].a, op[i - m].b, -op[i - m].c, i - m);
                update(op[i - m].b, op[i - m].a, -op[i - m].c, i - m);
            }
            printf("%d\n", res);
        }
    }
}

int main()
{
#ifdef LOCAL
    freopen("Test.in", "r", stdin);
#endif

    Run();
    return 0;
}
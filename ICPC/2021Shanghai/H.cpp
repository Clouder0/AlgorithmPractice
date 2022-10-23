#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
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
    for (; !isalpha(c); c = nc())
        ;
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

const int N = 1e5 + 100;
const int M = 2e5 + 100;
int n, m, a[N];
struct node
{
    int val, rank, lchild, rchild, wsum;
} tree[4 * N + M * 19];  // 每次操作增加节点数最多为 log2(4 * N) = 19

int init[N + 1], root[M + 1], tot;

int build(int l, int r)
{  // 建树
    int now = ++tot;
    if (l == r)
    {
        tree[now].val = init[l];
        tree[now].wsum = a[l];
        tree[now].rank = 1;
        return now;
    }
    int mid = (l + r) >> 1;
    tree[now].lchild = build(l, mid);
    tree[now].rchild = build(mid + 1, r);
    return now;
}

int update(int x, int l, int r, int target, int newroot)
{  // 合并操作-更新父亲节点信息
    int now = ++tot;
    tree[now] = tree[x];
    if (l == r)
    {
        tree[now].val = newroot;
        tree[newroot].rank = std::max(tree[newroot].rank, tree[now].rank + 1);
        return now;
    }
    int mid = (l + r) >> 1;
    if (target <= mid)
        tree[now].lchild = update(tree[x].lchild, l, mid, target, newroot);
    else
        tree[now].rchild = update(tree[x].rchild, mid + 1, r, target, newroot);
    return now;
}

int updatew(int x, int l, int r, int target, int w)
{
    int now = ++tot;
    tree[now] = tree[x];
    if (l == r)
    {
        tree[now].wsum += w;
        return now;
    }
    int mid = (l + r) >> 1;
    if (target <= mid)
        tree[now].lchild = updatew(tree[x].lchild, l, mid, target, w);
    else
        tree[now].rchild = updatew(tree[x].rchild, mid + 1, r, target, w);
    return now;
}

int query(int x, int l, int r, int target)
{  // 查询父亲节点
    if (l == r) return tree[x].val;
    int mid = (l + r) >> 1;
    if (target <= mid)
        return query(tree[x].lchild, l, mid, target);
    else
        return query(tree[x].rchild, mid + 1, r, target);
}

int queryw(int x, int l, int r, int target)
{
    if (l == r) return tree[x].wsum;
    int mid = (l + r) >> 1;
    if (target <= mid)
        return queryw(tree[x].lchild, l, mid, target);
    else
        return queryw(tree[x].rchild, mid + 1, r, target);
}

int getroot(int x, int l, int r, int target)
{  // 查询根节点
    int ans = query(x, l, r, target);
    if (ans == target)
        return ans;
    else
        return getroot(x, l, r, ans);
}
struct Edge
{
    int u, v, w;
} E[M];
bool cmp(const Edge& a, const Edge& b) { return a.w < b.w; }
int q;
int find_next(int w)
{
    int l = 1, r = m, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (E[mid].w <= w)
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}
int main()
{
    read(n), read(m), read(q);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= m; ++i) read(E[i].u), read(E[i].v), read(E[i].w);
    std::sort(E + 1, E + 1 + m, cmp);
    for (int i = 1; i <= n; ++i) init[i] = i;
    root[0] = build(1, n);
    for (int i = 1; i <= m; ++i)
    {
        int a = getroot(root[i - 1], 1, n, E[i].u);
        int b = getroot(root[i - 1], 1, n, E[i].v);
        if (a == b)
        {
            root[i] = root[i - 1];
            continue;
        }
        if (tree[a].rank < tree[b].rank)
        {
            int aw = queryw(root[i - 1], 1, n, a);
            root[i] = updatew(root[i - 1], 1, n, b, aw);
            b = getroot(root[i], 1, n, E[i].v);
            root[i] = update(root[i], 1, n, a, b);
        }
        else
        {
            int bw = queryw(root[i - 1], 1, n, b);
            root[i] = updatew(root[i - 1], 1, n, a, bw);
            a = getroot(root[i], 1, n, E[i].u);
            root[i] = update(root[i], 1, n, b, a);
        }

        //        for (int j = 1; j <= n; ++j) printf("w:%d=%d\n", j, queryw(root[i], 1, n, getroot(root[i], 1, n, j)));
        //        puts("");
    }
    while (q--)
    {
        int x, k;
        read(x), read(k);
        int t = k;
        int now = find_next(k), last = now;
        while (1)
        {
            t = queryw(root[now], 1, n, getroot(root[now], 1, n, x));
            //            printf("now:%d t:%d\n",now, t);
            last = now;
            now = find_next(k + t);
            if (now == last)
            {
                printf("%d\n", k + t);
                break;
            }
        }
    }
    return 0;
}
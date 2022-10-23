#include <cstdio>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        if (c == '-')
            flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
    r *= flag;
}
const int maxn = 40000;
int n;
int root, tot, cnt[maxn], fa[maxn], size[maxn], val[maxn], son[maxn][2];
inline void push_up(const int &p)
{
    size[p] = size[son[p][0]] + size[son[p][1]] + cnt[p];
}
inline bool isRightChild(const int &x)
{
    return son[fa[x]][1] == x;
}
inline void rotate(const int &x)
{
    int y = fa[x], z = fa[y], isRC = isRightChild(x);
    son[y][isRC] = son[x][isRC ^ 1];
    fa[son[x][isRC ^ 1]] = y;
    son[x][isRC ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z)
        son[z][y == son[z][1]] = x;
    push_up(y);
    push_up(x);
}
inline void splay(int x)
{
    for (int f = fa[x]; (f = fa[x]); rotate(x))
        if (fa[f])
            rotate(isRightChild(x) == isRightChild(f) ? f : x);
    root = x;
}
inline void insert(int k)
{
    if (!root)
    {
        val[++tot] = k;
        cnt[tot] = 1;
        push_up(tot);
        root = tot;
        return;
    }
    int p = root, f = 0;
    while (1)
    {
        if (val[p] == k)
        {
            cnt[p]++;
            push_up(p);
            push_up(f);
            splay(p);
            return;
        }
        f = p;
        p = son[p][val[p] < k];
        if (!p)
        {
            val[++tot] = k;
            cnt[tot] = 1;
            fa[tot] = f;
            son[f][val[f] < k] = tot;
            push_up(tot);
            push_up(f);
            splay(tot);
            return;
        }
    }
}
inline int pre()
{
    int p = son[root][0];
    while (son[p][1])
        p = son[p][1];
    return p;
}
inline int next()
{
    int p = son[root][1];
    while (son[p][0])
        p = son[p][0];
    return p;
}
int main()
{
    read(n);
    int x;
    int ans = 0;
    read(x);
    insert(x);
    ans += x;
    for (int i = 1; i < n; ++i)
    {
        read(x);
        insert(x);
        if (cnt[root] > 1)
        {
            continue;
        }
        int a = pre(), b = next();
        if (!a)
            ans += val[b] - x;
        else if (!b)
            ans += x - val[a];
        else
            ans += min(val[b] - x, x - val[a]);
    }
    printf("%d", ans);
    return 0;
}
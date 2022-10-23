#include <cstdio>
#include <algorithm>
#include <cctype>
#include <set>
using std::set;
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
const int maxn = 5e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y) { static int tot = 0; E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int n, m, siz[maxn], fa[maxn], dep[maxn], son[maxn], top[maxn], dfn[maxn], id[maxn], len[maxn], ind;
void dfs1(int u)
{
    siz[u] = 1;
    for (int p = head[u], v; p; p = E[p].next)
    {
        if ((v = E[p].to) == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    id[dfn[u] = ++ind] = u, len[top[u]]++;
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u], v; p; p = E[p].next) if ((v = E[p].to) != fa[u] && v != son[u]) dfs2(top[v] = v);
}

struct L  //A Simple Linked List
{
struct Lnode
{
    int x, val, pre, next;
} A[maxn*20];
int head[maxn*3], tot, id[maxn],bin[maxn*20],top;  //id[top] stands for the Linked List node id that belongs to top
inline int newnode(){return top ? bin[top--] : ++tot;}
inline void add(int x, int k) { x+=n+10;int p = newnode();A[p].next = head[x], A[p].x = x, A[head[x]].pre = p, head[x] = p, id[k] = p, A[p].val = k; }
inline void deltop(int top)  //delete the node that belongs to a specific top
{
    int p = id[top];
    if (A[p].pre) A[A[p].pre].next = A[p].next;
    else head[A[p].x] = A[p].next;
    if (A[p].next) A[A[p].next].pre = A[p].pre;
    A[p].val = id[top] = 0;
    bin[++top] = p;
}
inline int get(int x) { return A[head[x+=n+10]].val; }
} UL, DL;//head[x] saves the id of the tops that satisfy upval[top] == x or downval[top] == x
namespace Bit // used to see how many points belongs to S in subtree(u)
{
int sum[maxn];
inline void add(int x, int k) { for (; x <= n; x += x & -x) sum[x] += k; }
inline int ask(int x) { int res = 0; for (; x > 0; x -= x & -x) res += sum[x]; return res; }
}  // namespace Bit
inline int getw(int u) { return Bit::ask(dfn[u] + siz[u] - 1) - Bit::ask(dfn[u] - 1); }  // get the value of u
set<int> s[maxn];                                                         //ordered by depth, only saving depth and get node id by id[dfn[top[x] + dep]]
int up[maxn], down[maxn];                                                //up stands for the lowest node in C, and down stands for the highest node in D.  Note that up[t] < down[t], while both saving depth
int upval[maxn], downval[maxn];                                          // the val for up[t] and down[t]
inline int pre(int x, int y)
{
    // find the previous element of y in s[x].
    set<int>::iterator it = s[x].lower_bound(y);
    return it == s[x].begin() ? 0 : *--it;
}
inline int nex(int x, int y)
{
    set<int>::iterator it = s[x].upper_bound(y);
    return *it;
}
inline void delC(int x)
{
    //now that the top is x, delete up[x] from C, but not adding it into D
    //mainly used when deleting a point from S
    up[x] = pre(x, up[x]);
    upval[x] = up[x] ? getw(id[dfn[x] + up[x] - 1]) : 0;
}
inline void delD(int x)
{
    down[x] = nex(x, down[x]);
    downval[x] = down[x] <= len[x] ? getw(id[dfn[x] + down[x] - 1]) : 0;
}
inline void CtoD(int x)
{
    //moving node up[x] from C to D, and getting the new up[x]
    down[x] = up[x], downval[x] = upval[x];  //since up[x] < down[x], it is trivial that the old up[x] will become the new down[x]
    delC(x); //now we can simply delete it
}
inline void DtoC(int x) { up[x] = down[x], upval[x] = downval[x], delD(x); }
inline void update(int x) 
{
    //update the value of up[x] and down[x] in Linked List
    UL.deltop(x), DL.deltop(x);
    if (up[x]) UL.add(upval[x], x);
    if (down[x] <= len[x]) DL.add(downval[x], x);
}
inline void updateval(int x, int d, int k)
{
    //updating the value of up[x],down[x] when knowing a specific point is added/deleted in S
    //k stands for the value change, and d stands for the depth of that specific point
    if (up[x] && up[x] <= d) upval[x] += k;
    if (down[x] <= d) downval[x] += k;
}
int cnt, lim;  //cnt stands for the number of elements in C, and lim is just a auxiliary variable
//note that after an operation, cnt == lim is always true
void insert(int x)
{
    //insert node x into S
    int t = top[x], d = dep[x] - dep[t] + 1;
    Bit::add(dfn[x], 1);
    s[t].insert(d);
    updateval(t, d, 1);
    //now we need to redivide the nodes into C and D
    if(downval[t] > lim)
    {
        //the origin down[t] now exceeds lim, which means that x is under it contributing to the value
        ++cnt, DtoC(t);  // it is trivial that only one move will happen
    }
    else if(down[t] > d)
    {
        //the adding node x becomes the new down[t]
        int v = getw(x);
        if (v <= lim) down[t] = d, downval[t] = v;  //in this case, we can keep node x in D, and setting it to down[t]
        else
        {
            ++cnt;                                   //now we have to divide node x into C, in this case the origin down[t]'s value equals to lim
            if (d > up[t]) up[t] = d, upval[t] = v;  //determine whether node x can become the new up[t]
        }
    }
    update(t);
    for (int x = fa[t], t = top[x]; x; x = fa[t], t = top[x])
    {
        //now jump to the root
        d = dep[x] - dep[t] + 1;//CAUTION! set this to only cover the upper part of the chain, or you will modify some unexpected nodes.
        updateval(t, d, 1);
        if (downval[t] > lim) ++cnt, DtoC(t);  //redivide into C, this will happen at most once
        update(t);
    }
    if(cnt > lim)
    {
        int x = UL.get(lim);
        if (!x) ++lim; else --cnt, CtoD(x), update(x);
    }
}
void del(int x)
{
    int t = top[x], d = dep[x] - dep[t] + 1;
    Bit::add(dfn[x], -1), s[t].erase(d), updateval(t, d, -1);
    if (d <= up[t]) --cnt;  //as deleting, we first need to update the nodes for future operation
    if (d == up[t]) delC(t);
    else if (d == down[t]) delD(t);
    if (up[t] && upval[t] <= lim) --cnt, CtoD(t);
    update(t);
    for (int x = fa[t], t = top[x]; x; x = fa[t], t = top[x])
    {
        d = dep[x] - dep[t] + 1,updateval(t, d, -1);
        if (up[t] && upval[t] <= lim) --cnt, CtoD(t);
        update(t);
    }
    if(cnt < lim)
    {
        int x = DL.get(lim);
        if (!x) --lim; else ++cnt, DtoC(x), update(x);
    }
    if(cnt < lim)
    {
        int x = DL.get(lim);
        if (!x) --lim; else ++cnt, DtoC(x), update(x);
    }
}
int main()
{
    int total = 0;
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1; i <= n; ++i) if (top[i] == i) down[i] = len[i] + 1, s[i].insert(0), s[i].insert(len[i] + 1);
    //you'd better initialize like this, I don't know why but after I copied this I finally got AC at 2:30 in the morning.
    //now I'm going bed and have a good 'night'.
    read(m);
    for (int i = 1,opt,x; i <= m; ++i) 
    {
        read(opt), read(x);
        if (opt == 1) ++total,insert(x); else --total,del(x);
        printf("%d\n", !total ? 0 : cnt);
    }
    return 0;
}
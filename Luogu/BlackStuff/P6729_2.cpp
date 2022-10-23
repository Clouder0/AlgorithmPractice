#include <cstdio>
#include <algorithm>
#include <cctype>
#include <set>
using std::set;
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
const int maxn = 2e6 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int& x, const int& y)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, head[x] = tot;
}
int n, m, siz[maxn], fa[maxn], dep[maxn], son[maxn], top[maxn], dfn[maxn], id[maxn], ind;
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
    id[dfn[u] = ++ind] = u;
    if (!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u], v; p; p = E[p].next) if ((v = E[p].to) != fa[u] && v != son[u]) dfs2(top[v] = v);
}

struct List
{  //表头为权值，后面接着点的编号
    int pre[maxn], nxt[maxn];
    void deltop(int x)
    {
        printf("deltop:%d\n",x);
        if (nxt[x]) pre[nxt[x]] = pre[x];
        if (pre[x]) nxt[pre[x]] = nxt[x];
        pre[x] = x;
        nxt[x] = x;
    }
    void add(int v, int x)
    {  //在权值v后插入点x
        printf("ListAdd:%d %d\n",v,x);
        v += n + 1;
        nxt[x] = nxt[v];
        if (nxt[v]) pre[nxt[v]] = x;
        nxt[v] = x;
        pre[x] = v;
    }
    int get(int v) { return nxt[v + n + 1]; }
} UL, DL;
/*
struct L  //A Simple Linked List
{
struct Lnode
{
    int x, val, pre, next;
} A[maxn];
int head[maxn], tot, id[maxn];  //id[top] stands for the Linked List node id that belongs to top
inline void add(int x, int k) { ++x,A[++tot].next = head[x], A[tot].x = x, A[head[x]].pre = tot, head[x] = tot, id[k] = tot, A[tot].val = k; }
inline void deltop(int top)  //delete the node that belongs to a specific top
{
    int p = id[top];
    if (A[p].pre) A[A[p].pre].next = A[p].next;
    else head[A[p].x] = A[p].next;
    if (A[p].next) A[A[p].next].pre = A[p].pre;
    A[p].val = id[top] = 0;
}
inline int get(int x) { return A[head[++x]].val; }
} UL, DL;//head[x] saves the id of the tops that satisfy upval[top] == x or downval[top] == x
*/
namespace Bit // used to see how many points belongs to S in subtree(u)
{
int sum[maxn];
inline void add(int x, int k) { printf("Bitadd:%d %d\n",x,k);for (; x <= n; x += x & -x) sum[x] += k; }
inline int ask(int x) { int res = 0; for (; x > 0; x -= x & -x) res += sum[x]; return res; }
}  // namespace Bit
inline int getw(int u) { return printf("getw:%d\n",u),Bit::ask(dfn[u] + siz[u] - 1) - Bit::ask(dfn[u] - 1); }  // get the value of u
set<int> s[maxn];                                                         //ordered by depth, only saving depth and get node id by id[dfn[top[x] + dep]]
int up[maxn], down[maxn];                                                //up stands for the lowest node in C, and down stands for the highest node in D.  Note that up[t] < down[t], while both saving depth
int upval[maxn], downval[maxn];                                          // the val for up[t] and down[t]
inline int pre(int x, int y)
{
    // find the previous element of y in s[x].
    set<int>::iterator it = s[x].lower_bound(y);
    if (it == s[x].begin()) return 0;
    if (it == s[x].end()) return 0;
    return *--it;
}
inline int nex(int x, int y) { set<int>::iterator it = s[x].upper_bound(y); return it != s[x].end() ? *it : 0; }
inline void delC(int x)
{
    printf("dela:%d\n",x);
    //now that the top is x, delete up[x] from C, but not adding it into D
    //mainly used when deleting a point from S
    up[x] = pre(x, up[x]);
    printf("pre:%d\n", up[x] - dep[x] + 1);
    upval[x] = up[x] ? getw(id[dfn[x] + up[x] - dep[x]]) : 0;
    printf("upval:%d\n",upval[x]);
}
inline void delD(int x)
{
    printf("delb:%d\n", x);
    down[x] = nex(x, down[x]);
    printf("nex:%d\n", down[x] - dep[x] + 1);
    downval[x] = down[x] ? getw(id[dfn[x] + down[x] - dep[x]]) : 0;
}
inline void CtoD(int x)
{
    //moving node up[x] from C to D, and getting the new up[x]
    printf("a to b:%d\n",x);
    down[x] = up[x], downval[x] = upval[x];  //since up[x] < down[x], it is trivial that the old up[x] will become the new down[x]
    delC(x); //now we can simply delete it
}
inline void DtoC(int x) { up[x] = down[x], upval[x] = downval[x], delD(x); }
inline void update(int x) 
{
    //update the value of up[x] and down[x] in Linked List
    printf("update:%d %d %d\n",x,upval[x],downval[x]);
    UL.deltop(x); 
    if (up[x]) UL.add(upval[x], x);
    DL.deltop(x);
    if (down[x]) DL.add(downval[x], x);
}
inline void updateval(int x, int d, int k)
{
    //updating the value of up[x],down[x] when knowing a specific point is added/deleted in S
    //k stands for the value change, and d stands for the depth of that specific point
    printf("updateval:%d %d %d\n", x, d - dep[x] + 1, k);
    if (up[x] && up[x] <= d) upval[x] += k;
    if (down[x] && down[x] <= d) downval[x] += k;
    printf("updatedval:up:%d upval:%d down:%d downval:%d\n", up[x], upval[x], down[x], downval[x]);
}
int cnt, lim;  //cnt stands for the number of elements in C, and lim is just a auxiliary variable
//note that after an operation, cnt == lim is always true
void insert(int x)
{
    //insert node x into S
    int t = top[x], d = dep[x];
    Bit::add(dfn[x], 1);
    s[t].insert(d);
    updateval(t, d, 1);
    //now we need to redivide the nodes into C and D
    if(downval[t] > lim)
    {
        //the origin down[t] now exceeds lim, which means that x is under it contributing to the value
        ++cnt, DtoC(t);  // it is trivial that only one move will happen
    }
    else if(!down[t] || down[t] > d)
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
        d = dep[x];
        updateval(t, d, 1);
        if (down[t] && downval[t] > lim) ++cnt, DtoC(t);  //redivide into C, this will happen at most once
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
    int t = top[x], d = dep[x];
    printf("del:%d %d\n",t,d);
    Bit::add(dfn[x], -1), s[t].erase(d), updateval(t, d, -1);
    if (d <= up[t]) --cnt;  //as deleting, we first need to update the nodes for future operation
    if (d == up[t]) puts("delc"),delC(t);
    else if (d == down[t]) puts("deld"),delD(t);
    if (up[t] && upval[t] <= lim) --cnt, CtoD(t);
    update(t);
    for (int x = fa[t], t = top[x]; x; x = fa[t], t = top[x])
    {
        printf("jump:%d %d up:%d down:%d upval:%d downval:%d\n",x,t,up[t],down[t],upval[t],downval[t]);
        d = dep[x];
        updateval(t, d, -1);
        if (up[t] && upval[t] <= lim) --cnt, CtoD(t);
        update(t);
    }
    while(cnt < lim)
    {
        printf("cnt %d < lim %d\n",cnt,lim);
        int x = DL.get(lim);
        if (!x) --lim; else ++cnt, DtoC(x), update(x);
    }
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    read(m);
    for (int i = 1,opt,x; i <= m; ++i) 
    {
        read(opt), read(x);
        if (opt == 1) insert(x); else del(x);
        printf("%d done with %d\n\n",i,cnt);
//        printf("%d\n", cnt);
    }
    return 0;
}
#include <cstdio>
const int maxn = 1e5 + 10;
template<typename T>
inline void swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int root,tot,fa[maxn],son[maxn][2],val[maxn],cnt[maxn],size[maxn],tag[maxn];
int n,m;
inline bool isRightChild(const int &x)
{
    return son[fa[x]][1] == x;
}
inline void maintain(const int &x)
{
    size[x] = size[son[x][0]] + size[son[x][1]] + cnt[x];
}
inline void push_down(const int &p)
{
    if(!p || !tag[p])
        return;
    tag[son[p][0]] ^= 1;
    tag[son[p][1]] ^= 1;
    swap(son[p][0],son[p][1]);
    tag[p] = 0;
}
inline void rotate(int x)
{
    int y = fa[x],z = fa[y],isRC = isRightChild(x);
    push_down(y);
    push_down(x);
    son[y][isRC] = son[x][isRC^1];
    fa[son[x][isRC^1]] = y;
    son[x][isRC ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if(z)
        son[z][son[z][1] == y] = x;
    maintain(y);
    maintain(x);
}
inline void splay(int x,int goal)
{
    for(int f = fa[x];(f = fa[x]) != goal;rotate(x))
        if(fa[f] != goal)   rotate(isRightChild(f) == isRightChild(x) ? f : x);
    if(!goal) root = x;
}
int build(int l,int r,int f)
{
    if(l > r)
        return 0;
    int mid = l + r >> 1;
    int now = ++tot;
    if(mid == 1)
        val[now] = 1<<31;
    else if(mid == n + 2)
        val[now] = 1<<30;
    else
        val[now] = mid - 1;
    fa[now] = f;
    cnt[now] = 1;
    son[now][0] = build(l,mid - 1,now);
    son[now][1] = build(mid + 1,r,now);
    maintain(now);
    return now;
}

inline int find(int x)
{
    int p = root;
    while(1)
    {
        push_down(p);
        if(son[p][0] && size[son[p][0]] >= x)
            p = son[p][0];
        else
        {
            x -= size[son[p][0]] + cnt[p];
            if(x <= 0)
                return p;
            p = son[p][1];
        }
    }
}
inline void reverse(int x,int y)
{
    int l = find(x - 1);
    int r = find(y + 1);
    splay(l,0);
    splay(r,l);
    int p = son[root][1];
    p = son[p][0];
    tag[p] ^= 1;
}
void dfs(int p)
{
    if(!p)
        return;
    push_down(p);
    dfs(son[p][0]);
    if(val[p] != 1<<30 && val[p] != 1<<31)
        printf("%d ",val[p]);
    dfs(son[p][1]);
}
int main()
{
    read(n);
    read(m);
    root = build(1,n + 2,0);
    int x,y;
    while(m--)
    {
        read(x);
        read(y);
        reverse(x + 1,y + 1);
    }
    dfs(root);
    return 0;
}
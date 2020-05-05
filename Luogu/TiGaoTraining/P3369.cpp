#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <algorithm>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2 = (p1=buf) + fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    r *= flag;
}
const int maxn = 2e6 + 10;
int root,tot,fa[maxn],son[maxn][2],val[maxn],size[maxn],cnt[maxn];
int n;
inline void maintain(const int &x)
{
    size[x] = size[son[x][0]] + size[son[x][1]] + cnt[x];
}
bool isRightChild(const int &x)
{
    return son[fa[x]][1] == x;
}
void clear(const int &x)
{
    son[x][0] = son[x][1] = fa[x] = val[x] = size[x] = cnt[x] = 0;
}
inline void rotate(const int &x)
{
    int y = fa[x],z = fa[y],isRC = isRightChild(x);
    son[y][isRC] = son[x][isRC ^ 1];
    fa[son[x][isRC ^ 1]] = y;
    son[x][isRC^1] = y;
    fa[y] = x;
    fa[x] = z;
    if(z)
        son[z][y == son[z][1]] = x;
    maintain(y);
    maintain(x);
}
inline void splay(const int &x)
{
    for(int f = fa[x];f = fa[x],f;rotate(x))
        if(fa[f])   rotate(isRightChild(x) == isRightChild(f) ? f : x);
    root = x;
}
inline void insert(int k)
{
    if(!root)
    {
        val[++tot] = k;
        cnt[tot]++;
        root = tot;
        maintain(root);
        return;
    }
    int cnr = root, f = 0;
    while(1)
    {
        if(val[cnr] == k)
        {
            cnt[cnr]++;
            maintain(cnr);
            maintain(f);
            splay(cnr);
            break;
        }
        f = cnr;
        cnr = son[cnr][val[cnr] < k];
        if(!cnr)
        {
            val[++tot] = k;
            cnt[tot]++;
            fa[tot] = f;
            son[f][val[f] < k] = tot;
            maintain(tot);
            maintain(f);
            splay(tot);
            break;
        }
    }
}
inline int getRank(int k)
{
    int res = 0,cnr = root;
    while(1)
    {
        if(k < val[cnr])
        {
            cnr = son[cnr][0];
        }
        else
        {
            res += size[son[cnr][0]];
            if(val[cnr] == k)
            {
                splay(cnr);
                return res + 1;
            }
            res += cnt[cnr];
            cnr = son[cnr][1];
        }
    }
}
inline int getByRank(int k)
{
    int cnr = root;
    while(1)
    {
        if(son[cnr][0] && k <= size[son[cnr][0]])
        {
            cnr = son[cnr][0];
        }
        else
        {
            k -= cnt[cnr] + size[son[cnr][0]];
            if(k <= 0)
            {
                splay(cnr);
                return val[cnr];
            }
            cnr = son[cnr][1];
        }
    }
}
inline int pre()
{
    int cnr = son[root][0];
    while(son[cnr][1])
        cnr = son[cnr][1];
    splay(cnr);
    return cnr;
}
inline int next()
{
    int cnr = son[root][1];
    while(son[cnr][0])
        cnr = son[cnr][0];
    splay(cnr);
    return cnr;
}
inline void del(int k)
{
    getRank(k);
    if(cnt[root] > 1)
    {
        --cnt[root];
        maintain(root);
        return;
    }
    if(!son[root][0] && !son[root][1])
    {
        clear(root);
        root = 0;
        return;
    }
    if(!son[root][1])
    {
        int cnr = root;
        root = son[cnr][0];
        fa[root] = 0;
        clear(cnr);
        return;
    }
    if(!son[root][0])
    {
        int cnr = root;
        root = son[cnr][1];
        fa[root] = 0;
        clear(cnr);
        return;
    }
    int cnr = root, x = pre();
    splay(x);
    fa[son[cnr][1]] = x;
    son[x][1] = son[cnr][1];
    clear(cnr);
    maintain(root);
}
int m;
int origin[maxn];
int build(int l,int r,int f)
{
    if(l > r)
        return 0;
    int mid = l + r >> 1;
    int now = ++tot;
    val[now] = origin[mid];
    fa[now] = f;
    cnt[now] = 1;
    son[now][0] = build(l,mid - 1,now);
    son[now][1] = build(mid + 1,r,now);
    maintain(now);
    return now;
}
int main()
{
    read(n);
    read(m);
    int opt,x,last = 0,ans = 0;
    for(int i = 1;i<=n;++i)
        read(origin[i]);
    sort(origin + 1,origin + 1 + n);
    root = build(1,n,0);
    insert(1<<30),insert(1<<31);
    while(m--)
    {
        read(opt);
        read(x);
        x ^= last;
        switch(opt)
        {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                insert(x);
                last = getRank(x) - 1;
                del(x);
                break;
            case 4:
                last = getByRank(x + 1);
                break;
            case 5:
                insert(x);
                last = val[pre()];
                del(x);
                break;
            case 6:
                insert(x);
                last = val[next()];
                del(x);
                break;
        }
        if(opt >= 3)
            ans ^= last;
    }
    printf("%d\n",ans);
    return 0;
}
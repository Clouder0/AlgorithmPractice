#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline void _swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
template<typename T>
inline T read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn =  10;
int n;
int a[maxn];
int tar[maxn];
bool suc;
int maxdeep;
inline int dif()
{
    int res = 0;
    for(int i = 1;i<=n;++i)
        if(a[i] != a[i-1] + 1)
            ++res;
    return res;
}
inline void swap(int l,int r,int p,int q)
{
    int mem[10];
    int k = 0;
    for(int i = p;i <= q;++i)
        mem[++k] = a[i];
    for(int i = l;i<=r;++i)
        mem[++k] = a[i];
    k = 0;
    for(int i = l;i<=q;++i)
        a[i] = mem[++k];
}
void dfs(int step)
{
    int d = dif();
    if(suc)
        return;
    if(step == maxdeep)
    {
        suc = suc||!d;
        return;
    }
    if(3 * step + d > 3 * maxdeep)
        return;
    int origin[10];
    for(int i = 1;i<=n;++i)
        origin[i] = a[i];
    for(int l = 1;l<=n;++l)
    {
        for(int r = l;r<=n;++r)
        {
            int len = r - l + 1;
            for(int p = 1;p<=n;++p)
            {
                if(p >= l && p <= r + 1)
                    continue;
                if(p < l)
                    swap(p,l-1,l,r);
                else
                    swap(l,r,r+1,p - 1);
                dfs(step+1);
                for(int i = 1;i<=n;++i)
                    a[i] = origin[i];
            }
        }
    }
}
int main()
{
    int T = 0;
    while(read(n) != 0)
    {
        ++T;
        suc = false;
        for(int i = 1;i<=n;++i)
            read(a[i]);
        for(maxdeep = 1;maxdeep<=9;++maxdeep)
        {
            dfs(0);
            if(suc)
            {
                printf("Case %d: %d\n",T,maxdeep);
                break;
            }
        }
    }
    return 0;
}
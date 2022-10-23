#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
const int maxk = 210;
int n,k;
long long s[maxn];
long long f[2][maxn];
int q[maxn],head,tail;
int last,now;
int cut[maxk][maxn];
int out[maxk];
inline long long gx(int x)
{
    return s[x];
}
inline long long gy(int x)
{
    return f[last][x] - s[x] * s[x];
}
inline int cmp1(int x1,int x2,int x3)
{
    return (gy(x2) - gy(x1)) * (gx(x3) - gx(x2)) <= (gy(x3) - gy(x2)) * (gx(x2) - gx(x1));
}
inline int cmp2(int x1,int x2,long long k)
{
    return gy(x2) - gy(x1) > k * (gx(x2) - gx(x1));
}
void dfs(int tail,int v)
{
    if(v == 0)
        return;
    out[v] = cut[v][tail];
    dfs(cut[v][tail],v-1);
}
int main()
{
    read(n);
    read(k);
    for(int i = 1;i<=n;++i)
        read(s[i]),s[i] += s[i-1];
    now = 1,last = 0;
    for(int v = 1;v<=k;++v)
    {
        head = 1,tail = 0;
        q[++tail] = 0;
        for(int i = 1;i<=n;++i)
        {
            while(tail > head && cmp2(q[head],q[head+1],-s[i])) ++head;
            f[now][i] = f[last][q[head]] - s[q[head]] * s[q[head]] + s[i] * s[q[head]];
            cut[v][i] = q[head];
            while(tail > head && cmp1(q[tail-1],q[tail],i)) --tail;
            q[++tail] = i;
        }
        last ^= 1;
        now ^= 1;
    }
    printf("%lld\n",f[last][n]);
    dfs(n,k);
    for(int i = 1;i<=k;++i)
        printf("%d ",out[i]);
    return 0;
}
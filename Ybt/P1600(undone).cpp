#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 10;
int n,p[maxn],d[maxn];
int pn[maxn],dn[maxn];
int sum[maxn];
int origin[maxn];
int q[maxn],head = 1,tail;
bool res[maxn];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(p[i]),read(d[i]),sum[i] = sum[i-1] + p[i] - d[i];
    for(int i = n+1;i<=n*2;++i)
        p[i] = p[i-n],d[i] = d[i-n],sum[i] = sum[i-1] + p[i] - d[i];
    for(int i = 1;i<n*2;++i)
    {
        while(tail >= head && sum[q[tail]] >= sum[i])
            --tail;
        q[++tail] = i;
        while(tail >= head && q[tail] - q[head] + 1 > n)
            ++head;
        if(i >= n)
            if(sum[q[head]] - sum[i-n] >= 0)
                res[i-n+1] = true;
    }
    for(int i = 1;i<=n;++i)
        origin[i] = n-i+1;
    for(int i = n+1;i<=n*2;++i)
        origin[i] = origin[i-n];
    for(int i = 1;i<=n*2;++i)
        pn[i] = p[origin[i]];
    for(int i = 1;i<=n;++i)
        dn[i] = d[origin[i+1]];
    for(int i = n+1;i<=n*2;++i)
        dn[i] = dn[i-n];
    for(int i = 1;i<=n*2;++i)
        sum[i] = sum[i-1] + pn[i] - dn[i];
    head = 1,tail = 0;
    for(int i = 1;i<n*2;++i)
    {
        while(tail >= head && sum[q[tail]] >= sum[i])
            --tail;
        q[++tail] = i;
        while(tail >= head && q[tail] - q[head] + 1 > n)
            ++head;
        if(i >= n)
            if(sum[q[head]] - sum[i-n] >= 0)
                res[origin[i-n+1]] = true;
    }
    for(int i = 1;i<=n;++i)
        if(res[i])
            puts("TAK");
        else
            puts("NIE");
    return 0;
}
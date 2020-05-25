#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
int n,m;
int a[maxn];
long long sum[maxn];
int f[maxn];
int q[maxn],head,tail;
inline int maxk(int l,int r)
{
    int res = 0;
    for(int i = l;i<=r;++i)
        res = _max(res,a[i]);
    return res;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]),sum[i] = sum[i-1] + a[i];
    memset(f,0x3f,sizeof(f));
    f[0] = 0;
    head = 1;
    q[++tail] = 0;
    int p = 0;
    for(int i = 1;i<=n;++i)
    {
        while(p < i)
        {
            while(sum[i] - sum[p] > m) ++p;
            while(tail >= head && f[q[tail]] + maxk(q[tail] + 1,i) >= f[p] + maxk(p + 1,i))  --tail;
            q[++tail] = p;
            ++p;
        }
        while(tail >= head && sum[i] - sum[q[head]] > m) ++head;
        f[i] = f[q[head]] + maxk(q[head] + 1,i);
    }
    printf("%d",f[n]);
    return 0;
}
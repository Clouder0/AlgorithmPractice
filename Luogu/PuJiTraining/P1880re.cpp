#include <cstdio>
#include <cstring>
using namespace std;
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
inline int min(const int &a,const int &b){return a<b?a:b;}
inline int max(const int &a,const int &b){return a>b?a:b;}
int sum[210],all[210];
int sa[210][210];
int n;
int dfsmin(int l,int r)
{
    if(sa[l][r] != -1)
        return sa[l][r];
    if(r <= l)
        return sa[l][r] = 0;
    int mina = 99999999;
    for(int k = l;k<r;++k)
        mina = min(dfsmin(l,k) + dfsmin(k+1,r) + sum[r] - sum[l-1],mina);
    return sa[l][r] = mina;
}
int dfsmax(int l,int r)
{
    if(sa[l][r] != -1)
        return sa[l][r];
    if(r <= l)
        return sa[l][r] = 0;
    int maxa = 0;
    for(int k = l;k<r;++k)
        maxa = max(dfsmax(l,k) + dfsmax(k+1,r) + sum[r] - sum[l-1],maxa);
    return sa[l][r] = maxa;
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        read(all[i]);
        all[i+n] = all[i];
    }
    for(int i = 1;i<=n<<1;++i)
        sum[i] = sum[i-1] + all[i];
    memset(sa,-1,sizeof(sa));
    dfsmin(1,n<<1);
    int ans = 999999999;
    for(int i = 1;i<=n;++i)
        ans = min(ans,sa[i][i+n-1]);
    printf("%d\n",ans);
    memset(sa,-1,sizeof(sa));
    dfsmax(1,n<<1);
    ans = 0;
    for(int i = 1;i<=n;++i)
        ans = max(ans,sa[i][i+n-1]);
    printf("%d\n",ans);
    return 0;
}
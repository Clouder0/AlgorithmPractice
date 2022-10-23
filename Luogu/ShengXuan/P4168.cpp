#include <cstdio>
#include <cmath>
#include <algorithm>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 4e4 + 100;
const int maxnum = 220;
int a[maxn],H[maxn],tot;
int n,m,size,num;
int L[maxnum],R[maxnum],pos[maxn];
int f[maxnum][maxnum],s[maxnum][maxn];
int cnt[maxn];
inline int calc(int x,int y,int k){return s[x][k] - s[y][k];}
inline int ask(int l,int r)
{
    int lp = pos[l],rp = pos[r];
    if(lp == rp)
    {
        int res = 0;
        for (int i = l; i <= r; ++i) if (cnt[res] < ++cnt[a[i]] || (cnt[res] == cnt[a[i]] && res > a[i])) res = a[i];
        for(int i = l;i<=r;++i) cnt[a[i]] = 0;
        return res;
    }
    int res = f[lp + 1][rp - 1];
    for(int i = l;i<=R[lp];++i) cnt[a[i]]++;
    for(int i = L[rp];i<=r;++i) cnt[a[i]]++;
    int t = calc(rp - 1,lp,res);
    for(int i = l;i<=R[lp];++i) 
    {
        int z = calc(rp - 1, lp, a[i]) + cnt[a[i]];
        if (t < z || (t == z && a[i] < res)) res = a[i],t = z;;
    }
    for(int i = L[rp];i<=r;++i) 
    {
        int z = calc(rp - 1, lp, a[i]) + cnt[a[i]];
        if (t < z || (t == z && a[i] < res)) res = a[i],t = z;;
    }
    for(int i = l;i<=R[lp];++i) cnt[a[i]] = 0;
    for(int i = L[rp];i<=r;++i) cnt[a[i]] = 0;
    return res;
}
inline void init();
int main()
{
    init();
    int x = 0;
    while(m--)
    {
        int l,r;
        read(l),read(r);
        l = l + x - 1,r = r + x - 1;
        if(l >= n) l %= n;
        if(r >= n) r %= n;
        ++l,++r;
        if(l > r) std::swap(l,r);
        printf("%d\n",x = H[ask(l,r)]);
    }
    return 0;
}
inline void init()
{
    read(n), read(m);
    for(int i = 1;i<=n;++i) read(a[i]),H[++tot] = a[i];
    std::sort(H + 1,H + 1 + tot),tot = std::unique(H + 1,H + 1 + tot) - H - 1;
    for(int i = 1;i<=n;++i) a[i] = std::lower_bound(H + 1,H + 1 + tot,a[i]) - H;

    size = sqrt(n) + 10;
    num = n / size;
    for(int i = 1;i<=num;++i)
    {
        L[i] = R[i-1] + 1,R[i] = L[i] + size - 1;
        for(int j = L[i];j<=R[i];++j) pos[j] = i;
    }
    if(R[num] < n)
    {
        L[num + 1] = R[num] + 1,R[++num] = n;
        for(int j = L[num];j<=n;++j) pos[j] = num;
    }
    for (int i = 1; i <= num; ++i)
    {
        for(int j = 1;j<=tot;++j) s[i][j] = s[i-1][j];
        for(int j = L[i];j<=R[i];++j) s[i][a[j]]++;
    }
    for(int i = 1;i<=num;++i)
        for(int j = i;j<=num;++j)
        {
            int t = f[i][j-1];
            for (int k = L[j]; k <= R[j]; ++k) if((calc(j,i - 1,a[k]) == calc(j,i - 1,t) && a[k] < t) || calc(j,i - 1,a[k]) > calc(j,i - 1,t)) t = a[k];
            f[i][j] = t;
        }
}
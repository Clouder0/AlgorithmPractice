#include <cstdio>
#include <algorithm>
template <typename T> inline T max(const T &a,const T &b){return a>b?a:b;}
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
void read(int &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
int n,m,k;
int last[5001];//last[i]保存i点最晚能在哪里被派兵守卫
int a[5001],b[5001],c[5001],d[5001];//d[i]代表占领i前到达i这里的兵力
int q[5001];
bool cmp(const int &a,const int &b)
{
    return c[a] > c[b];
}
inline bool check(const int &p)
{
    for(int i = p;i<=n;++i)
        if(a[i] + 1 > d[i])
            return false;
    return true;
}
int main()
{
    read(n);
    read(m);
    read(k);
    int now = k;//现在兵力
    for(int i = 1;i<=n;++i)
    {
        read(a[i]);
        read(b[i]);
        read(c[i]);
        d[i] = now;
        if(now < a[i])
        {
            printf("-1");
            return 0;
        }
        now += b[i];//顺便判断是否能占领所有城堡，也就是判断每次取完兵能否一路全部占领
        q[i] = last[i] = i;
    }
    int u,v;
    for(;m;--m)
    {
        read(u);
        read(v);
        last[v] = max(last[v],u);
    }
    std::sort(q+1,q+1+n,cmp);//按照贡献值排序
    int ans = 0;
    for(int i = 1;i<=n;++i)
    {
        if(check(last[q[i]] + 1))
        {
            for(int j = last[q[i]] + 1;j<=n;++j)
                --d[j];
            ans += c[q[i]];
        }
    }
    printf("%d",ans);
    return 0;
}
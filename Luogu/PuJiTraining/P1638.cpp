#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
const int maxm = 2e3 + 100;
int a[maxn];
int cnt[maxn],kind;
int n,m;
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]);
    int l = 1,r = 1,ans = 1<<30,ansl,ansr;
    cnt[a[1]]++,kind = 1;
    while(r <= n)
    {
        while(r < n && kind < m)
        {
            ++r;
            cnt[a[r]]++;
            if(cnt[a[r]] == 1) ++kind;
        }
        if(kind != m) break;
        while(cnt[a[l]] > 1) cnt[a[l]]--,++l;
        if(ans > r - l + 1) {ans = r - l + 1;ansl = l,ansr = r;}
        if(cnt[a[l]] == 1) --kind;
        cnt[a[l]]--,++l;
    }
    printf("%d %d",ansl,ansr);
    return 0;
}
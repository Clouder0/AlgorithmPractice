#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
const int maxn = 510;
int n;
int a[maxn];
int ans[maxn*maxn],top;
inline bool check()
{
    bool flag = true;
    for (int i = 1; flag && i < n; ++i) if (a[i] > a[i + 1]) flag = false;
    if (flag)
    {
        printf("%d\n", top);
        for (int i = 1; i <= top; ++i) printf("%d ", ans[i]);
        putchar('\n');
        return true;
    }
    return false;
}
int main()
{
    read(T);
    while(T--)
    {
        top = 0;
        read(n);
        for(int i = 1;i<=n;++i) read(a[i]);
        if(check()) goto end;
        for(int k = 0;k<n;++k)
        {
            int t = 1;
            for(int i = 2;i<=n-k;++i) if(a[i] > a[t]) t = i;
            int dis = n - k - t;
            if(dis == 0) continue;
            if(dis <= 2)
            {
                
            }
            if(dis % 2 == 0)
            {
                while(t != n - k)
                {
                    ans[++top] = t;
                    std::swap(a[t],a[t+1]);
                    std::swap(a[t+1],a[t+2]);
                    t += 2;
                }
            }
            else
            {
                if(t <= 2)
                {
                    ans[++top] = t;
                    std::swap(a[t],a[t+1]);
                    std::swap(a[t+1],a[t+2]);
                    t += 2;
                }
                ans[++top] = t - 2;
                std::swap(a[t-2],a[t-1]);
                std::swap(a[t-1],a[t]);
                t--;
                while(t != n - k)
                {
                    ans[++top] = t;
                    std::swap(a[t],a[t+1]);
                    std::swap(a[t+1],a[t+2]);
                    t += 2;
                }
            }
            if(check()) goto end;
        }
        puts("-1");
        end:;
    }
    return 0;
}
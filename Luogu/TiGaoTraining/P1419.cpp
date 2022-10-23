#include <cstdio>
using namespace std;
template<typename T>
inline void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1e5 + 100;
int n;
int s,t;
int a[maxn];
double sum[maxn];
int q[maxn],head,tail;
inline bool check(double x)
{
    for(int i = 1;i<=n;++i)
        sum[i] = sum[i-1] + a[i] - x;
    head = 1;
    tail = 0;
    int p = 1;
    for(int i = 1;i<=n;++i)
    {
        while(i - p + 1 <= t && i - p + 1 >= s)
        {
            while(tail >= head && sum[p-1] < sum[q[tail]-1])
                --tail;
            q[++tail] = p;
            ++p;
            while(tail >= head && i - q[head] + 1 > t)
                ++head;
        }
        if(tail >= head && sum[i] - sum[q[head] - 1] >= 0)
            return true;
    }
    return false;
}
int main()
{
    read(n);
    read(s);
    read(t);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    double l = -10001,r = 10001,mid,ans;
    while(r - l > 1e-5)
    {
        mid = (l + r) / 2;
        if(check(mid))
        {
            ans = mid;
            l = mid;
        }
        else
            r = mid;
    }
    printf("%.3f",ans);
    return 0;
}
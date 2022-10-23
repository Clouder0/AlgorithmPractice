#include <cstdio>
#define nc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++)
using namespace std;
const int maxn = 1000010;
int sum[maxn], sta[maxn], h[maxn], w[maxn], n, ans, top;
static char buf[10000000], *p1 = buf, *p2 = buf;
void read(int &r)
{
    static char c; r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(h[i]);
        read(w[i]);
        while (top && h[i] > h[sta[top]])
            sum[i] += w[sta[top--]];
        sum[sta[top]] += w[i];
        sta[++top] = i;
    }
    for (int i = 1; i <= n; ++i)
        ans = ans < sum[i] ? sum[i] : ans;
    printf("%d", ans);
    return 0;
}
#include <cstdio>
#include <cstring>
#define LL __int128
#define pre b
using namespace std;
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 4e7 + 10;
const int maxm = 1e5 + 10;
int n,type;
long long s[maxn];
int p[maxm],l[maxm],r[maxm];
int b[maxn];
int q[maxn],head,tail;
char out[200],top;
LL getans(int i)
{
    if(i <= 0)
        return 0;
    LL t = s[i] - s[pre[i]];
    return t * t + getans(pre[i]);
}
void solve()
{
    head = 1, tail = 0;
    q[++tail] = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (tail > head && s[i] - s[q[head + 1]] >= s[q[head + 1]] - s[pre[q[head + 1]]])
            ++head;
        pre[i] = q[head];
        //f[i] = (s[i] - s[pre[i]]) * (s[i] - s[pre[i]]) + f[q[head]];
        while (tail > head && s[q[tail]] + s[q[tail]] - s[pre[q[tail]]] >= s[i] + s[i] - s[pre[i]])
            --tail;
        q[++tail] = i;
    }
    LL ans = getans(n);
    while (ans)
    {
        out[++top] = (ans % 10) + 48;
        ans /= 10;
    }
    while(top)
        putchar(out[top--]);
}
int main()
{
    read(n);
    read(type);
    if(!type)
    {
        for(int i = 1;i<=n;++i)
            read(s[i]),s[i] += s[i-1];
        solve();
    }
    else
    {
        int x,y,z,b1,b2,m;
        read(x);
        read(y);
        read(z);
        read(b[1]);
        read(b[2]);
        read(m);
        for(int i = 1;i<=m;++i)
            read(p[i]),read(l[i]),read(r[i]);
        for(int i = 3;i<=n;++i)
            b[i] = ((long long)x*b[i-1] + (long long)y * b[i-2] + z) % (1<<30);
        int now = 0;
        for(int i = 1;i<=n;++i)
        {
            if(i > p[now]) ++now;
            s[i] = s[i-1] + (b[i] % (r[now] - l[now] + 1)) + l[now];
        }
        solve();
    }
    return 0;
}
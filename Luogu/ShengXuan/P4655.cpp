#include <cstdio>
#include <algorithm>
#define int long long
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 2e5 + 100;
const int inf = 1ll<<60;
int n;
int h[maxn];
long long s[maxn],f[maxn];
int A[maxn];
int queue[maxn],head,tail;
inline long long gy(int x)
{
    return f[x] - s[x] + 1ll * h[x] * h[x];
}
inline int gx(int x) {return h[x];}
bool check1(int x1,int x2,int x3)
{
    return (gy(x2) - gy(x1)) * (gx(x3) - gx(x2)) >=  (gy(x3) - gy(x2)) * (gx(x2) - gx(x1));
}
bool check2(int x1,int x2,int k)
{
    return gy(x2) - gy(x1) < k * (gx(x2) - gx(x1));
}
bool cmp(int x, int y)
{
    if (h[x] == h[y]) return x < y;
    return h[x] < h[y];
}
bool cmp2(int a,int b){return a<b;}
void cdq(int l,int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    std::sort(A + l,A + r + 1,cmp2);
    std::sort(A + mid + 1,A + r + 1,cmp);
    cdq(l,mid);
    std::sort(A + l,A + mid + 1,cmp);
    head = 1,tail = 0;
    for(int i = l;i<=mid;++i)
    {
        while (head < tail && check1(queue[tail - 1], queue[tail], A[i])) --tail;
        queue[++tail] = A[i];
    }
    for(int q = mid + 1;q<=r;++q)
    {
        while (head < tail && check2(queue[head], queue[head + 1], 2 * h[A[q]])) ++head;
        int i = A[q], j = queue[head];
        f[i] = min(f[i], f[j] + s[i - 1] - s[j] + h[i] * h[i] + h[j] * h[j] - 2 * h[i] * h[j]);
    }
    cdq(mid + 1, r);
}
signed main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(h[i]),f[i] = inf,A[i] = i;
    for(int i = 1;i<=n;++i) read(s[i]),s[i] += s[i-1];
    f[1] = 0;
    cdq(1,n);
    printf("%lld",f[n]);
    return 0;
}
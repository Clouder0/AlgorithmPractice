#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
inline T read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r*=flag;
}
const int maxn = 1e6 + 100;
struct node
{
    int l, r;
} a[maxn];
int X[maxn], cnt;
int T;
int n;
inline int search(int x)
{
    int ll = 1, rr = cnt, mid, ans;
    while (ll <= rr)
    {
        mid = (ll + rr) >> 1;
        if (X[mid] <= x)
        {
            ans = mid;
            ll = mid + 1;
        }
        else
            rr = mid - 1;
    }
    return ans;
}
int A[maxn];
int B[maxn];
int sum[maxn];
int main()
{
    read(T);
    while (T--)
    {
        cnt = 0;
        read(n);
        for (int i = 1; i <= n; ++i)
            read(a[i].l), read(a[i].r), X[++cnt] = a[i].l, X[++cnt] = a[i].r;
        sort(X + 1, X + 1 + cnt);
        cnt = unique(X + 1, X + 1 + cnt) - X - 1;
        for (int i = 1; i <= n; ++i)
        {
            a[i].l = search(a[i].l);
            a[i].r = search(a[i].r);
            a[i].l <<= 1;
            a[i].r <<= 1;
            A[a[i].l]++;
            A[a[i].r + 1]--;
        }
        cnt <<= 1;
        cnt += 10;
        for (int i = 1; i <= cnt; ++i)
            A[i] += A[i - 1];
        int origin = 0;
        for (int i = 0; i <= cnt; ++i)
            origin += (A[i] && !A[i + 1]);
        for (int i = 0; i < cnt; ++i)
            if (A[i] != 1 && A[i + 1] == 1)
                B[i + 1]++;
        for (int i = 1; i <= cnt; ++i)
            if(A[i] == 1 && A[i + 1] != 1)
                B[i]++;
        for (int i = 1; i <= cnt; ++i)
            B[i] += B[i - 1];
        int maxx = -(1<<30);
        for (int i = 1; i <= n; ++i)
        {
            int temp = (B[a[i].r] - B[a[i].l - 1]) >> 1;
            temp -= (A[a[i].l] == 1) + (A[a[i].r] == 1);
            if (maxx < temp)
                maxx = temp;
        }
        printf("%d\n", origin + maxx);
        for (int i = 0; i <= cnt; ++i)
            A[i] = B[i] = 0;
    }
    return 0;
}
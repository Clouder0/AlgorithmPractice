#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e3 + 10;
int a,b,n;
int all[maxn][maxn];
int q[maxn],head,tail;
int maxa[maxn][maxn],maxb[maxn][maxn];
int mina[maxn][maxn],minb[maxn][maxn];
int main()
{
    read(a);
    read(b);
    read(n);
    for(int i = 1;i<=a;++i)
        for(int j = 1;j<=b;++j)
            read(all[i][j]);
    for(int i = 1;i<=a;++i)
    {
        head = 1,tail = 0;
        for(int j = 1;j<=b;++j)
        {
            while(tail >= head && all[i][q[tail]] <= all[i][j])
                --tail;
            q[++tail] = j;
            while(tail >= head && q[tail] - q[head] + 1 > n)
                ++head;
            if(j >= n)
            maxa[i][j-n+1] = all[i][q[head]];
        }
        head = 1,tail = 0;
        for(int j = 1;j<=b;++j)
        {
            while(tail >= head && all[i][q[tail]] >= all[i][j])
                --tail;
            q[++tail] = j;
            while(tail >= head && q[tail] - q[head] + 1 > n)
                ++head;
            if(j >= n)
            mina[i][j-n+1] = all[i][q[head]];
        }
    }
    for(int i = 1;i<=b;++i)
    {
        head = 1,tail = 0;
        for(int j = 1;j<=a;++j)
        {
            while(tail >= head && maxa[q[tail]][i] <= maxa[j][i])
                --tail;
            q[++tail] = j;
            while(tail >= head && q[tail] - q[head] + 1 > n)
                ++head;
            if(j >= n)
            maxb[j-n+1][i] = maxa[q[head]][i];
        }
        head = 1, tail = 0;
        for (int j = 1; j <= a; ++j)
        {
            while(tail >= head && mina[q[tail]][i] >= mina[j][i])
                --tail;
            q[++tail] = j;
            while(tail >= head && q[tail] - q[head] + 1 > n)
                ++head;
            if(j >= n)
            minb[j-n+1][i] = mina[q[head]][i];
        }
    }
    int ans = 1<<30;
    for(int i = 1;i<=a-n+1;++i)
        for(int j = 1;j<=b-n+1;++j)
            if(maxb[i][j] - minb[i][j] < ans)
                ans = maxb[i][j] - minb[i][j];
    printf("%d",ans);
    return 0;
}
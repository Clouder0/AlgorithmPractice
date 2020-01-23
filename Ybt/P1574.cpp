#include <cstdio>
#include <memory.h>
using namespace std;
int power = 10000;
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
struct hp
{
    int num[200];
    hp()
    {
        memset(num,0,sizeof(num));
    }
    hp(int a)
    {
        memset(num,0,sizeof(num));
        for(;a;num[++num[0]] = a % power,a /= power);
    }
    hp operator+(const hp &b)
    {
        hp r;
        r.num[0] = max(num[0],b.num[0]);
        for(int i = 1;i<=r.num[0];++i)
        {
            r.num[i] += num[i] + b.num[i];
            if(r.num[i] >= power)
                r.num[i] -= power,++r.num[i+1];
        }
        if(r.num[r.num[0]+1] > 0)
            ++r.num[0];
        return r;
    }
    hp operator*(const hp &b)
    {
        hp r;
        r.num[0] = num[0] + b.num[0] + 1;
        for(int i = 1;i<=num[0];++i)
            for(int j = 1;j<=b.num[0];++j)
            {
                r.num[i+j-1] += num[i] * b.num[j];
                r.num[i+j] += r.num[i+j-1] / power;
                r.num[i+j-1] %= power;
            }
        while(r.num[r.num[0]] == 0 && r.num[0] > 1)
            --r.num[0];
        return r;
    }
    bool operator>(const hp b) const
    {
        if(num[0] != b.num[0])
            return num[0] > b.num[0];
        for(int i = num[0];i>=1;--i)
            if(num[i] != b.num[i])
                return num[i] > b.num[i];
        return false;
    }
    void print()
    {
        printf("%d",num[num[0]]);
        for(int i = num[0] - 1;i>=1;--i)
            printf("%04d",num[i]);
    }
};
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
int n, m;
int all[100][100];
hp dp[100][100];
hp t[100];
hp ans;
int main()
{
    read(n);
    read(m);
    t[0] = 1;
    for(int i = 1;i<=m;++i)
        t[i] = t[i-1] * hp(2);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            read(all[i][j]);
    for (int i = 1; i <= n; ++i)
    {
        for (int len = 0; len <= m; ++len)
        {
            for (int l = 1; l + len <= m; ++l)
            {
                int r = l + len;
                dp[l][r] = max(dp[l][r], dp[l][r - 1] + hp(all[i][r]) * t[m - len]);
                dp[l][r] = max(dp[l][r], dp[l+1][r] + hp(all[i][l]) * t[m - len]);
            }
        }
        ans = ans + dp[1][m];
        for(int i = 1;i<=m;++i)
            for(int j = 1;j<=m;++j)
                dp[i][j] = hp();
    }
    ans.print();
    return 0;
}
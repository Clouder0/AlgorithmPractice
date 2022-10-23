#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
const int maxn = 50001;
char A[maxn], B[maxn];
int T, n, sum[maxn];
bitset<50001> pre[3 * maxn];
bitset<50001> suf[3 * maxn];
template <std::size_t N>
void bit_reverse(std::bitset<N>& b)
{
    for(std::size_t i = 0; i < N/2; ++i) {
        bool t = b[i];
        b[i] = b[N - i - 1];
        b[N - i - 1] = t;
    }
}
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        scanf("%s%s", A + 1, B + 1);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + A[i] - '0';
        int minn = n;
        int maxx = n;

        for (int i = 1; i <= n; ++i)
        {
            minn = min(minn, 2 * sum[i] - i + n);
            maxx = max(maxx, 2 * sum[i] - i + n);
        }
        for(int i = minn;i<=maxx;++i) pre[i].flip(), suf[i].flip();
        pre[n].set(0,0);
        suf[n].set(0,0);
        for(int i = 1;i<=n;++i)
        {
            pre[2 * sum[i] - i + n].set(i, 1);
            suf[2 * sum[i] - i + n].set(i, 1);
        }
        for (int i = minn + 1; i <= maxx; ++i) pre[i] &= pre[i - 1];
        for (int i = maxx - 1; i >= minn; --i) suf[i] &= suf[i + 1];
        bitset<50001> ans;
        for (int i = 1; i <= n; ++i)
        {
            bitset<50001> s;
            if(B[i])
                s = pre[2 * sum[i] - i + n - 1];
            else
                s = suf[2 * sum[i] - i + n];
            for (int j = 0; 2 * j <= i; ++j)
            {
                bool t = s[j];
                s[j] = s[i - j];
                s[i - j] = t;
            }   
            printf("i:%d\n",i);
            for (int i = 1; i <= n; ++i)
                putchar(s[i] ? '1' : '0');
            puts("");
            puts("");
            ans |= s;
        }
        for (int i = 1; i <= n; ++i)
            putchar(ans[i] ? '0' : '1');
        puts("");
    }
    return 0;
}
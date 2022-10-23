#include <cstdio>
const int maxn = 3e5 + 100;
int T,n,k;
char s[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        scanf("%s", s + 1);
        int one = 0,zero = 0;
        for (int i = 1; i < k; ++i) one += (s[i] == '1'), zero += (s[i] == '0');
        for (int i = 1; i <= n - k + 1; ++i)
        {
            one -= (s[i - 1] == '1'), zero -= (s[i - 1] == '0');
            one += (s[i + k - 1] == '1'), zero += (s[i + k - 1] == '0');
            if (one > k / 2 || zero > k / 2) goto fail;
            if (i + k > n) break;
            if (s[i + k] != '?')
            {
                if (s[i] != '?') { if (s[i] != s[i + k]) goto fail; }
                else s[i] = s[i + k];
            }
            else if (s[i] != '?') s[i + k] = s[i];
        }
        one = zero = 0;
        for (int i = 1; i < k; ++i) one += (s[i] == '1'), zero += (s[i] == '0');
        for (int i = 1; i <= n - k + 1; ++i)
        {
            one -= (s[i - 1] == '1'), zero -= (s[i - 1] == '0');
            one += (s[i + k - 1] == '1'), zero += (s[i + k - 1] == '0');
            if (one > k / 2 || zero > k / 2) goto fail;
        }
        printf("%s\n", s + 1);
        puts("YES");
        continue;
    fail:
        puts("NO");
    }
    return 0;
}
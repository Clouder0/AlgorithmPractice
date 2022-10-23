#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long

const int maxn = 5e5 + 100;
int T, n, cnt1[maxn], cnt2[maxn];
char s[maxn];

signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld", &n);
        for (int i = 1; i <= 26; ++i) cnt1[i] = cnt2[i] = 0;
        int first1 = 27, last2 = 0;
        while(n--)
        {
            int type, k, num1 = 0, num2 = 0;
            scanf("%lld %lld %s", &type, &k, s + 1);
            int len = strlen(s + 1);
            if(type == 1)
            {
                for (int i = 1; i <= len; ++i) cnt1[s[i] - 'a' + 1] += k;
            }
            else
            {
                for (int i = 1; i <= len; ++i) cnt2[s[i] - 'a' + 1] += k;
            }
            for (int i = 1; i <= 26; ++i)
                if (cnt1[i])
                {
                    first1 = i;
                    break;
                }
            for (int i = 26; i; --i)
                if (cnt2[i])
                {
                    last2 = i;
                    break;
                }
            if (first1 == 27) goto yes;
            if(!last2) goto no;
            if (first1 < last2) goto yes;
            if (first1 > last2) goto no;
            for (int i = 1; i <= 26; ++i) num1 += (cnt1[i] != 0);
            for (int i = 1; i <= 26; ++i) num2 += (cnt2[i] != 0);
            if(num1 == 1 && num2 == 1)
            {
                if(cnt1[first1] < cnt2[last2]) goto yes;
                goto no;
            }
            goto no;
            yes:
            puts("YES");
            continue;
            no:
            puts("NO");
            continue;
        }
    }
    return 0;
}
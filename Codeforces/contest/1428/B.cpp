#include <cstdio>
const int maxn = 3e5 + 100;
int T, n;
char s[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d", &n);
        scanf("%s", s + 1);
        int flag = 0,flag2 = 0;
        for (int i = 1; i <= n; ++i) if (s[i] == '>') flag = 1; else if (s[i] == '<') flag2 = 1;
        if(!flag || !flag2) printf("%d\n",n);
        else
        {
            int res = 0;
            s[0] = s[n], s[n + 1] = s[1];
            for (int i = 1; i <= n; ++i) if (s[i] == '-' || s[i + 1] == '-') ++res;
            printf("%d\n",res);
        }
    }
    return 0;
}
#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 100;
char s[maxn];
int pi[maxn],len,maxx;
int main()
{
    scanf("%s",s + 1);
    len = strlen(s + 1);
    for(int i = 2,k = 0;i<=len;++i)
    {
        while(k && s[i] != s[k + 1]) k = pi[k];
        if(s[i] == s[k + 1]) ++k;
        pi[i] = k;
        if(i != len && pi[i] > maxx) maxx = pi[i];
    }
    while(pi[len] > maxx) pi[len] = pi[pi[len]];
    if(pi[len] == 0) return 0,puts("Just a legend");
    for (int i = 2; i < len; ++i)
        if (pi[i] == pi[len])
        {
            for (int j = 1; j <= pi[i]; ++j)
                putchar(s[j]);
            return 0;
        }
    return 0;
}
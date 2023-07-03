#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 100;
char s1[maxn],s2[maxn];
int len1,len2;
int pi[maxn];
int main()
{
    scanf("%s %s",s1 + 1,s2 + 1);
    len1 = strlen(s1 + 1),len2 = strlen(s2 + 1);
    for (int i = 2, k = 0; i <= len2; ++i)
    {
        while(k && s2[i] != s2[k + 1]) k = pi[k];
        if(s2[i] == s2[k + 1]) ++k;
        pi[i] = k;
    }
    for (int i = 1, k = 0; i <= len1; ++i)
    {
        while(k && s1[i] != s2[k + 1]) k = pi[k];
        if(s1[i] == s2[k + 1]) ++k;
        if (k == len2) printf("%d\n", i - len2 + 1), k = pi[k];
    }
    for (int i = 1; i <= len2; ++i) printf("%d ", pi[i]);
    return 0;
}
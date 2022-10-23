#include <cstdio>
const int maxn = 1e6 + 100;
int n, pi[maxn];
char s[maxn];
int main()
{
    scanf("%d", &n);
    scanf("%s", s);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while(j && s[i] != s[j]) j = pi[j - 1];
        if(s[i] == s[j]) ++j;
        pi[i] = j;
    }
    printf("%d\n", n - pi[n - 1]);
    return 0;
}
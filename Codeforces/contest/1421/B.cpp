#include <cstdio>
char s[210][210];
int T, n;
int ansx[3],ansy[3],tot;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d", &n);
        tot = 0;
        for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
        if (s[1][2] == s[2][1])
        {
            if (s[1][2] == s[n - 1][n]) ansx[++tot] = n - 1, ansy[tot] = n;
            if (s[1][2] == s[n][n - 1]) ansx[++tot] = n, ansy[tot] = n - 1;
        }
        else if (s[n - 1][n] == s[n][n - 1])
        {
            if (s[1][2] == s[n - 1][n]) ansx[++tot] = 1, ansy[tot] = 2;
            if (s[2][1] == s[n][n - 1]) ansx[++tot] = 2, ansy[tot] = 1;
        }
        else
        {
            ansx[++tot] = 1,ansy[tot] = 2;
            if (s[n - 1][n] == s[2][1]) ansx[++tot] = n - 1, ansy[tot] = n;
            else if (s[n][n - 1] == s[2][1]) ansx[++tot] = n, ansy[tot] = n - 1;
        }
        printf("%d\n",tot);
        for (int i = 1; i <= tot; ++i)  printf("%d %d \n",ansx[i],ansy[i]);
    }
    return 0;
}
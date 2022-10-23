#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 2e6 + 100;
int n;
char S[maxn], T[maxn], TS[maxn];
char res[maxn];
int pi[maxn];
void kmp(int len)
{
    for (int i = 2, k = 0; i <= len; ++i)
    {
        while (k && T[k + 1] != T[i]) k = pi[k];
        if (T[k + 1] == T[i]) ++k;
        pi[i] = k;
    }
}
int main()
{
    scanf("%d", &n);
    scanf("%s", S + 1);
    int slen = strlen(S + 1), tlen;
    for (int i = 2; i <= n; ++i)
    {
        scanf("%s", T + 1);
        tlen = strlen(T + 1);
        T[tlen + 1] = '\0';
        int num = std::min(tlen, slen);
        for (int j = 1; j <= num; ++j) T[tlen + 1 + j] = S[slen - num + j];
        kmp(tlen + 1 + num);
        int cutlen = pi[tlen + 1 + num];
        for (int j = cutlen + 1; j <= tlen; ++j) S[++slen] = T[j];
    }
    printf("%s", S + 1);
    return 0;
}
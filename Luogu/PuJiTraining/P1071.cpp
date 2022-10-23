#include <cstdio>
#include <cstring>
using namespace std;
int nto[110], otn[110];
char s1[110], s2[110], s3[110];
int l1, l2, l3;
char output[110];
int top = 0;
int main()
{
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    scanf("%s", s3 + 1);
    memset(nto, -1, sizeof(nto));
    memset(otn, -1, sizeof(otn));
    l1 = strlen(s1 + 1);
    l2 = l1;
    l3 = strlen(s3 + 1);
    for (int i = 1; i <= l1; ++i)
    {
        if (nto[s1[i] - 'A'] != -1 && nto[s1[i] - 'A'] != s2[i] - 'A')
            goto fail;
        if (otn[s2[i] - 'A'] != -1 && otn[s2[i] - 'A'] != s1[i] - 'A')
            goto fail;
        otn[s2[i] - 'A'] = s1[i] - 'A';
        nto[s1[i] - 'A'] = s2[i] - 'A';
    }
    for (int i = 0; i < 26; ++i)
        if (nto[i] == -1 || otn[i] == -1)
            goto fail;
    for (int i = 1; i <= l3; ++i)
    {
        if (nto[s3[i] - 'A'] == -1)
            goto fail;
        output[++top] = nto[s3[i] - 'A'] + 'A';
    }
    for (int i = 1; i <= l3; ++i)
        putchar(output[i]);
    return 0;
fail:
    printf("Failed");
    return 0;
}
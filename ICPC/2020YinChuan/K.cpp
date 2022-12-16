#include <cstdio>
#include <cstring>
const int maxn = 3e6 + 100;
int n;
char n2c[28], c2n[1000];
int res;
struct Trie
{
    int fa[maxn], to[maxn][28], cnt, untag[maxn], sum[maxn];
    void ins_rel(char* s)
    {
        int p = 0, place = -1;
        untag[p]--;
        for (; *s != '\0'; ++s)
        {
            int c = c2n[(int)*s];
            if (!to[p][c]) to[p][c] = ++cnt, fa[cnt] = p;  // create a new edge to that node
            p = to[p][c];
            untag[p]--;
            if (untag[p] == 0 && place == -1) place = p;
        }
        int delta = 1 - sum[place];
        res = res + delta;
        while (place != 0) sum[place] += delta, place = fa[place];
    }
    void ins_un(char* s)
    {
        int p = 0;
        untag[p]++;
        for (; *s != '\0'; ++s)
        {
            int c = c2n[(int)*s];
            if (!to[p][c]) to[p][c] = ++cnt, fa[cnt] = p;  // create a new edge to that node
            p = to[p][c];
            untag[p]++;
        }
    }
} T;
char s[51000][51];
int main()
{
    for (int i = 0; i < 26; ++i) n2c[i] = 'a' + i, c2n['a' + i] = i;
    n2c[26] = '.', n2c[27] = '/';
    c2n['.'] = 26, c2n['/'] = 27;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1), T.ins_un(s[i] + 1);
    for (int i = 1; i <= n; ++i)
    {
        T.ins_rel(s[i] + 1);
        printf("%d\n", res);
    }
    return 0;
}
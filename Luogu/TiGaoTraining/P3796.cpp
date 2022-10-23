#include <cstdio>
const int maxn = 1e6 + 100;
int n;
char s[maxn];
int son[maxn][26],val[maxn],fail[maxn],tot;
inline void clear(int x)
{
    fail[x] = val[x] = 0;
    for(int i = 0;i<26;++i) son[x][i] = 0;
}
inline void ins(char *s)
{
    int u = 0;
    for(;*s!='\0';++s)
    {
        int p = *s - 'a';
        if(!son[u][p]) son[u][p] = ++tot,clear(tot);
        u = son[u][p];
    }
    val[u]++;
}
int q[maxn],head,tail;
inline void build()
{
    head = 1,tail = 0;
    for(int i = 0;i<26;++i) if(son[0][i]) fail[son[0][i]] = 0,q[++tail] = son[0][i];
    while(tail >= head)
    {
        int u = q[head++];
        for(int i = 0;i<26;++i) 
            if(son[u][i]) fail[son[u][i]] = son[fail[u]][i],q[++tail] = son[u][i];
            else son[u][i] = son[fail[u]][i];
    }
}
int ans[maxn],cnt;
inline int ask(char *s)
{
    int u = 0,res = 0;
    for(;*s!='\0';++s)
    {
        int p = *s - 'a';
        u = son[u][p];
        for (int i = u; i && val[i] != -1; i = fail[i])
        {
            if(val[i] > res) res = val[i],ans[cnt = 1] = ;
            val[i] = -1;
        }
    }
    return res;
}
inline void init()
{
    tot = 1;
    clear(0);
}
int main()
{
    while(scanf("%d",&n) && n != 0)
    {
        while(n--) scanf("%s",s),ins(s);
        build();
        scanf("%s",s);
        printf("%d",ask(s));
    }
    return 0;
}
#include <cstdio>
const int maxn = 1e6 + 100;
int n;
char s[maxn];
int son[maxn][26],val[maxn],fail[maxn],tot;
inline void ins(char *s)
{
    int u = 0;
    for(;*s!='\0';++s)
    {
        int p = *s - 'a';
        if(!son[u][p]) son[u][p] = ++tot;
        u = son[u][p];
    }
    val[u]++;
}
int q[maxn],head = 1,tail;
inline void build()
{
    for(int i = 0;i<26;++i) if(son[0][i]) fail[son[0][i]] = 0,q[++tail] = son[0][i];
    while(tail >= head)
    {
        int u = q[head++];
        for(int i = 0;i<26;++i) 
            if(son[u][i]) fail[son[u][i]] = son[fail[u]][i],q[++tail] = son[u][i];
            else son[u][i] = son[fail[u]][i];
    }
}
inline int ask(char *s)
{
    int u = 0,res = 0;
    for(;*s!='\0';++s)
    {
        int p = *s - 'a';
        u = son[u][p];
        for (int i = u; i && val[i] != -1; i = fail[i]) res += val[i], val[i] = -1;
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    while(n--) scanf("%s",s),ins(s);
    build();
    scanf("%s",s);
    printf("%d",ask(s));
    return 0;
}
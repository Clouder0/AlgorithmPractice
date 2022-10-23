#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
}
inline void read(char *s)
{
    static char c;
    for(c = nc();!islower(c);c=nc());
    for (; islower(c); c = nc()) *s++ = c;
    *s = '\0';
}
const int maxn = 5e6 + 100;
int n,m;
int son[maxn][26],tot;
struct node
{
    int val,next;
}E[maxn];
int head[maxn];
inline void add(int x,int v)
{
    static int tot = 0;
    E[++tot].next = head[x],head[x] = tot,E[tot].val = v;
}
inline void insert(char *s,int bel)
{
    int u = 0;
    for(;*s != '\0';++s)
    {
        int p = *s - 'a';
        if(!son[u][p]) son[u][p] = ++tot;
        u = son[u][p];
    }
    if(E[head[u]].val == bel) return;
    add(u,bel);
}
int out[maxn],tail;
inline void search(char *s)
{
    int u = 0;
    for(;*s != '\0';++s)
    {
        int p = *s - 'a';
        if(!son[u][p]) return;
        u = son[u][p];
    }
    tail = 0;
    for(int p = head[u];p;p=E[p].next) out[++tail] = E[p].val;
    while(tail) printf("%d ",out[tail--]);
}
char s[30];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        int num;
        read(num);
        while(num--)
        {
            read(s);
            insert(s,i);
        }
    }
    read(m);
    while(m--)
    {
        read(s);
        search(s);
        putchar('\n');
    }
    return 0;
}
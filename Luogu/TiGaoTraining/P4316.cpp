#include <cstdio>
template<typename T>
inline void read(T &r)
{
    static char c;
    for(r = 0,c = getchar();c>'9'||c<'0';) c = getchar();
    for(;c>='0'&&c<='9';c=getchar()) r = r * 10 + c - 48;
}
const int maxn = 1e5 + 100;
const int maxm = 2e5 + 200;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val){E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;    }
int n,m;
double f[maxn];
int in[maxn],degree[maxn];
int q[maxn],qhead = 1,qtail;
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=m;++i)
    {
        int u,v,w;
        read(u),read(v),read(w);
        add(v,u,w);
        in[u]++,degree[u]++;
    }
    for(int i = 1;i<=n;++i) if(in[i] == 0) q[++qtail] = i;
    while(qtail >= qhead)
    {
        int u = q[qtail--];
        for(int p = head[u];p;p=E[p].next)
        {
            int v = E[p].to;
            f[v] += (f[u] + E[p].val) / degree[v];
            if(--in[v] == 0) q[++qtail] = v;
        }
    }
    printf("%.2f",f[1]);
    return 0;
}
#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[5100];
int head[510];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = node(y,head[x]),head[x] = tot;
}
int n,m;
int w[]
int main()
{
    read(n);
    read(m);
    
}
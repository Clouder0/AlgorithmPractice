#include <cstdio>
using namespace std;
struct node
{
    int id;
    node *pre,*next;
    node(){}
    node(const int &_id,node *_pre,node *_next) : id(_id),pre(_pre),next(_next){}
};
node *f[201000];
void pushfront(const int &x,const int &y)
{
    //在x前面插入y
    f[y] = new node(y,f[x]->pre,f[x]);
    f[x] -> pre = f[y];
    if(f[y]->pre)
        f[y]->pre->next = f[y];
}
void pushback(const int &x,const int &y)
{
    //在x后面插入y
    f[y] = new node(y,f[x],f[x]->next);
    f[x] -> next = f[y];
    if(f[y]->next)
        f[y]->next->pre = f[y];
}
void del(const int &id)
{
    if(!f[id])
        return;
    if(f[id]->pre)
        f[id]->pre->next = f[id]->next;
    if(f[id]->next)
        f[id]->next->pre = f[id]->pre;
    delete(f[id]);
    f[id] = NULL;
}
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m;
int main()
{
    read(n);
    f[0] = new node(0,NULL,NULL);
    pushback(0,1);
    int k,flag;
    for(int i = 2;i<=n;++i)
    {
        read(k);
        read(flag);
        if(flag == 0)
            pushfront(k,i);
        else
            pushback(k,i);
    }
    read(m);
    while(m--)
    {
        read(k);
        del(k);
    }
    node *head = f[0]->next;
    while(head)
    {
        printf("%d ",head->id);
        head = head->next;
    }
    return 0;
}
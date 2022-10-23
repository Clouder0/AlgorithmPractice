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
    int id;
    node* next;
    node(){}
    node(const int &_id,node* _next) : id(_id),next(_next){}
};
int n,m;
node *head = NULL;
template<typename T>
inline void swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
void erase(node *p)
{
    if(!p->next)
    {
        delete(p);
        return;
    }
    printf("%d ",p->id);
    swap(p->id,p->next->id);
    node *s = p->next;
    p->next = p->next->next;
    delete(s);
}
int main()
{
    read(n);
    read(m);
    node *last = new node(n,NULL);
    head = last;
    for(int i = n - 1;i>=1;--i)
        head = new node(i,head);
    last -> next = head;//构造循环链表
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<m;++j)
            head = head->next;
        erase(head);
    }
    return 0;
}
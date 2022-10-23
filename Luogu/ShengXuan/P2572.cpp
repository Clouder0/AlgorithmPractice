#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <set>
using namespace std;
inline char nc()
{
    static char buf[100000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
struct node
{
    int l,r;
    mutable bool val;
    node(){}
    node(const int &_l,const int &_r = -1,const bool &_val = 0) : l(_l),r(_r),val(_val){}
    bool operator<(const node &b) const
    {
        return this->l < b.l;
    }
};
set<node> s;
typedef set<node>::iterator IT;
IT split(const int &pos)
{
    //分为[l,x-1]和[x,r]
    IT it = s.lower_bound(node(pos));
    if(it != s.end() && it->l == pos)
        return it;
    --it;
    int ll = it->l,rr = it->r;
    bool val = it->val;
    s.erase(it);
    s.insert(node(ll,pos-1,val));
    return s.insert(node(pos,rr,val)).first;
}
inline void assign(const int &ll,const int &rr,const bool &val)
{
    IT itr = split(rr+1),itl = split(ll);
    s.erase(itl,itr);
    s.insert(node(ll,rr,val));
}
inline void opposite(const int &ll,const int &rr)
{
    IT itr = split(rr+1),itl = split(ll);
    for(;itl!=itr;++itl)
        itl->val ^= 1;
}
inline int countOne(const int &ll,const int &rr)
{
    IT itr = split(rr+1),itl = split(ll);
    int res = 0;
    for(;itl!=itr;++itl)
        if(itl->val)
            res += (itl->r - itl->l + 1);
    return res;
}
inline int countseqOne(const int &ll,const int &rr)
{
    IT itr = split(rr+1),itl = split(ll);
    int res(0),temp(0);
    for(;itl != itr;++itl)
    {
        if(itl->val)
            temp += (itl->r - itl->l + 1);
        else
        {
            res = (res > temp ? res : temp);
            temp = 0;
        }
    }
    res = (res > temp ? res : temp);
    return res;
}
int n,m;
int main()
{
    read(n);
    read(m);
    int flag,x,y;
    for(int i = 0;i<n;++i)
        read(x),s.insert(node(i,i,x));
    s.insert(node(n,n,0));
    for(;m;--m)
    {
        read(flag);
        read(x);
        read(y);
        switch(flag)
        {
            case 0:
                assign(x,y,0);
                break;
            case 1:
                assign(x,y,1);
                break;
            case 2:
                opposite(x,y);
                break;
            case 3:
                printf("%d\n",countOne(x,y));
                break;
            case 4:
                printf("%d\n",countseqOne(x,y));
                break;
        }
    }
    return 0;
}
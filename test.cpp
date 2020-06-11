#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
int val[maxn],to[maxn],n,m;
namespace BIT{//树状数组,清空BIT我选择了打时间戳
    int f[maxn],t[maxn],n,tot;
    inline void init(int x){n = x;}
    inline int lowbit(int x){return x & (-x);}
    inline void clear(){tot++;}
    inline void add(int pos,int x){
        while(pos <= n){
            if(t[pos] < tot)f[pos] = 0,t[pos] = tot;
            f[pos] += x;
            pos += lowbit(pos);
        }
    }
    inline int query(int pos){
        int ret = 0;
        while(pos){
            if(t[pos] < tot)f[pos] = 0,t[pos] = tot;
            ret += f[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
    inline int query(int a,int b){return query(b) - query(a - 1);}
}
ll ans[maxn];
struct Node{//三元组,本来打算用tuple,但是担心常数还是选择手写
    int x,y,z;
    bool operator < (const Node &rhs)const{
        return x < rhs.x;
    }
};
namespace cdqa{//对应上文第一种情况
    Node val[maxn],tmp[maxn];
    void cdq(int a,int b){
        if(a == b)return;
        int mid = (a + b) >> 1;
        cdq(a,mid),cdq(mid + 1,b);
        int p1 = a,p2 = mid + 1,p = a;
        while(p1 <= mid && p2 <= b){
            if(val[p1].y < val[p2].y)BIT::add(val[p1].z,1),tmp[p++] = val[p1++];//按第二维从小到大的顺序归并
            else ans[val[p2].x] += BIT::query(val[p2].z + 1,n),tmp[p++] = val[p2++];
        }
        while(p1 <= mid)tmp[p++] = val[p1++];
        while(p2 <= b)ans[val[p2].x] += BIT::query(val[p2].z + 1,n),tmp[p++] = val[p2++];
        for(int i = a;i <= b;i++)val[i] = tmp[i];
        BIT::clear();
    }
}
namespace cdqb{//第二种情况
    Node val[maxn],tmp[maxn];
    void cdq(int a,int b){
        if(a == b)return;
        int mid = (a + b) >> 1;
        cdq(a,mid),cdq(mid + 1,b);
        int p1 = a,p2 = mid + 1,p = a;
        while(p1 <= mid && p2 <= b){
            if(val[p1].y > val[p2].y)BIT::add(val[p1].z,1),tmp[p++] = val[p1++];
            else ans[val[p2].x] += BIT::query(1,val[p2].z - 1),tmp[p++] = val[p2++];
        }
        while(p1 <= mid)tmp[p++] = val[p1++];
        while(p2 <= b)ans[val[p2].x] += BIT::query(1,val[p2].z - 1),tmp[p++] = val[p2++];
        for(int i = a;i <= b;i++)val[i] = tmp[i];
        BIT::clear();
    }
}
int main(){
#ifdef LOCAL
    freopen("fafa.in","r",stdin);
#endif
    scanf("%d %d",&n,&m);
    BIT::init(n);
    for(int i = 1;i <= n;i++)scanf("%d",&val[i]),to[val[i]] = i;//由于读入的是元素,所以我们需要做一个映射得到下标
    for(int i = 1;i <= n;i++){//读入
        cdqa::val[i].x = 0,cdqa::val[i].y = i,cdqa::val[i].z = val[i];
        cdqb::val[i].x = 0,cdqb::val[i].y = i,cdqb::val[i].z = val[i];
    }
    for(int pos,i = 1;i <= m;i++){//得到时间戳
        scanf("%d",&pos);
        cdqa::val[to[pos]].x = m - i + 1;
        cdqb::val[to[pos]].x = m - i + 1;
    }
    sort(cdqa::val + 1,cdqa::val + 1 + n);
    sort(cdqb::val + 1,cdqb::val + 1 + n);
    cdqa::cdq(1,n);
    cdqb::cdq(1,n);//计算
    for(int i = 1;i <= m;i++)ans[i] += ans[i - 1];//前缀和
    for(int i = m;i >= 1;i--)printf("%lld\n",ans[i]);//询问的是删除之后的逆序对数量,因此需要倒序输出.没有询问一开始的数量因而不需要输出ans[0]
    return 0;
}

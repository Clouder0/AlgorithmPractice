#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;
const int MAXN = 410;
long long a[MAXN], b[MAXN], c[MAXN], m_p[MAXN][MAXN];
int n, p[MAXN];

const long long o_o=1e3+10;
const long long m_a=1e18;
//long long m_p[o_o][o_o];//建立点点之间的边权 
long long b_d[o_o];//存储匹配的编号 
long long s_s[o_o];//到节点的最小值 
long long p_r[o_o];//记录增广的节点（从那个点来的）
long long m_x[o_o];//匹配点集权值 
long long m_y[o_o];//被匹配点集权值 
bool b_b[o_o];//标记是否遍历过 
void f_i(long long u){
	//初始化 
    long long k_k=0;//记录当前处理的节点的编号 
	long long l_t=0;//记录最优路径的编号 
	long long x,m_i;//当前处理的节点，最小值 
    memset(p_r,0,sizeof(p_r));//初始化 
    for(long long i=1;i<=n;i++)s_s[i]=m_a;//初始化 
    b_d[0]=u;//从当前节点开始 
    
    while(1){
        x=b_d[k_k];//找到匹配的节点 
		m_i=m_a;//初始化最小值 
		b_b[k_k]=1;//标记 
        for(long long i=1;i<=n;i++){//枚举所有被匹配的节点 
            if(b_b[i])continue;//被标记过 
            if(s_s[i]>m_x[x]+m_y[i]-m_p[x][i]){//更新最小值	
            	//这里边的权值取的是相反数，所以权值越大，值越小 
            	
                s_s[i]=m_x[x]+m_y[i]-m_p[x][i];//更新最小值 
                p_r[i]=k_k;//记录来的点 
            }
            if(s_s[i]<m_i){
				m_i=s_s[i];//更新最小值 
				l_t=i;//记录编号 
			}
        }
        for(long long i=0;i<=n;i++){//枚举所有节点 
            if(b_b[i]){//标记过的节点 
            	m_x[b_d[i]]-=m_i;//匹配节点加上最大边权 
				m_y[i]+=m_i;//被匹配节点减去最大边权 
			}else s_s[i]-=m_i;//所有节点加上最大边权
			//加上最大边权，下次的边权一定小于等于这个边权，可以继续找次大边权 
        }
        k_k=l_t;//处理记录的编号最优边的增广路 
        if(b_d[k_k]==-1)break;//没有增广路，退出循环 
    }
    while(k_k){//回溯（换配）
		b_d[k_k]=b_d[p_r[k_k]];//更新匹配编号 
		k_k=p_r[k_k];//往回找 
	}
}
long long k_m(){
	//初始化 
    memset(b_d,-1,sizeof(b_d));//未匹配过的节点的值是 -1 
    memset(m_x,0,sizeof(m_x));
    memset(m_y,0,sizeof(m_y));
    
    for(long long i=1;i<=n;i++){
        memset(b_b,0,sizeof(b_b));//清空标记 
        f_i(i);//匹配 i 节点 
    }
    long long r_s=0;
    for(long long i=1;i<=n;i++)
        if(b_d[i]!=-1)r_s+=m_p[b_d[i]][i];//统计权值 
    return r_s;
}

signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i) scanf("%lld", p + i);
    for (int i = 1; i <= n; ++i) scanf("%lld", b + i);
    for (int i = 1; i <= n; ++i) scanf("%lld", c + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            long long num = b[i] + c[j];
            for (int k = 1; k <= n; ++k)
                if (num > a[k])
                    m_p[i][j] += p[k];
        }
    printf("%lld\n", k_m());
    return 0;
}

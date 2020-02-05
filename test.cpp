#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

const int N=10000086;

int n,max_dep,vis[N],root;
struct node
{
    int to,next;
}E[N];
int head[N];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = (node){y,head[x]},head[x] = tot;
}

void dfs(int dep,int fa,int x)
{
	max_dep=max(max_dep,dep);
    for(int i = head[x];i;i=E[i].next)
		if(E[i].to!=fa) dfs(dep+1,x,E[i].to);
}

int main()
{
	scanf("%d",&n);
	int a,b;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
        add(i,a);
        add(i,b);
		vis[a]=1;
		vis[b]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) 
		{
			root=i;
			break;
		}
	dfs(0,0,root);
	printf("%d\n",max_dep);
	return 0;
}
#include<bits/stdc++.h>
    #define WALK(v,p) for(int i=hd[v][p],to;i;i=e[i].nxt)
    using namespace std;
    const int maxn=5e6+10;
    int n,m,d,id[1<<17][51],o[maxn],k[maxn],vis[maxn],h[1<<17],t,tt;
    int s[maxn],vl[maxn],f[maxn],a[1<<17][51],hd[2][maxn],w[maxn];
    struct edge{int v,nxt;}e[maxn*2];
    void add(int p,int u,int v){e[++t]={v,hd[p][u]},hd[p][u]=t;}
    void dfs(int p){
    	vis[p]=1;
    	WALK(1,p)if(!vis[to=e[i].v])dfs(to);
    	s[++t]=p;
    }
    void dfs1(int p){
    	vis[p]=t;w[tt++]=p;
    	if(!h[o[p]]&&a[o[p]][k[p]])++vl[t],h[o[p]]=1;
    	WALK(0,p)if(!vis[to=e[i].v])dfs1(to);
    }
    int main(){
    	scanf("%d%d%d",&n,&m,&d);
    	for(int i=1;i<=n;i++)for(int j=0;j<d;j++)id[i][j]=++t,o[t]=i,k[t]=j;
    	t=0;
    	for(int i=1;i<=m;i++){
    		int x,y;scanf("%d%d",&x,&y);
    		for(int j=0;j<d;j++)
    			add(0,id[x][j],id[y][(j+1)%d]),
    			add(1,id[y][(j+1)%d],id[x][j]);
    	}
    	for(int i=1;i<=n;i++){
    		getchar();
    		for(int j=0;j<d;j++)
    			a[i][j]=getchar()=='1';
    	}
    	t=0;
    	for(int i=1;i<=n*d;i++)if(!vis[i])dfs(i);
    	memset(vis,0,sizeof vis);t=0;
    	for(int i=n*d;i;i--)if(!vis[s[i]]){
    		tt=0;++t,dfs1(s[i]);f[t]=vl[t];
    		for(int j=0;j<tt;j++){
    			h[o[w[j]]]=0;
    			WALK(0,w[j])if(vis[to=e[i].v]!=t)f[t]=max(f[t],f[vis[to]]+vl[t]);
    		}
    	}
    	printf("%d\n",f[vis[id[1][0]]]);
    	return 0;
    }
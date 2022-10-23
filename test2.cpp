/*********************************************************************
	Problem:「WC2020」有根树
	Author:hydd
	Date:2020/8/13-2020/8/14
*********************************************************************/
#include<cstdio>
#include<algorithm>
#include<set>
#define File(x) freopen(x".in","r",stdin);//freopen(x".out","w",stdout)
using namespace std;
const int INF=0x3f3f3f3f;
const int MAXN=510000;
const int MAXM=1100000;
int n,q;
namespace IO{
	const int LEN=1<<20;
	char Getchar(){
		static char now[LEN],*A,*B;
		if (B==A){
			B=(A=now)+fread(now,1,LEN,stdin);
			if (B==A) return EOF;
		}
		return *A++;
	}
	int read(){
		int x=0,f=1;
		char ch=Getchar();
		while (ch<'0'||ch>'9'){
			if (ch=='-') f=-1;
			ch=Getchar();
		}
		while (ch<='9'&&ch>='0') x=x*10+ch-'0',ch=Getchar();
		return x*f;
	}
	char pbuf[LEN],*pp=pbuf;
	void pc(const char c) {
		if (pp-pbuf==LEN) fwrite(pbuf,1,LEN,stdout),pp=pbuf;
		*pp++=c;
	}
	void write(int x){
		static int sta[35];
		if (x<0){ pc('-'); x=-x;}
		int top=0;
		do{
			sta[top++]=x%10;
			x/=10;
		} while (x);
		while (top) pc(sta[--top]+'0');
	}
	void IOflush(){ fwrite(pbuf,1,pp-pbuf,stdout);}
} using namespace IO;
namespace Graph{
	int edgenum,vet[MAXM],val[MAXM],Next[MAXM],Head[MAXN];
	void addedge(int u,int v){
		vet[++edgenum]=v;
		Next[edgenum]=Head[u];
		Head[u]=edgenum;
	}
} using namespace Graph;
namespace HLD{//Heavy-Light Decompositions
	int fa[MAXN],sz[MAXN],son[MAXN];
	int dtime,L[MAXN],R[MAXN],num[MAXN];
	int tot[MAXN],top[MAXN];
	void dfs(int u,int f){
		fa[u]=f; sz[u]=1; son[u]=0;
		for (int e=Head[u],v;e;e=Next[e]){ v=vet[e];
			if (v==f) continue;
			dfs(v,u); sz[u]+=sz[v];
			if (sz[v]>sz[son[u]]) son[u]=v;
		}
	}
	void dfs2(int u,int tp){
		top[u]=tp; tot[tp]++; num[++dtime]=u;
		L[u]=dtime;
		if (son[u]) dfs2(son[u],tp);
		for (int e=Head[u],v;e;e=Next[e]){ v=vet[e];
			if (v==fa[u]||v==son[u]) continue;
			dfs2(v,v);
		}
		R[u]=dtime;
	}
} using namespace HLD;

namespace BIT{//Binary Index Tree
	int tree[MAXN];
	void add(int x,int y){
		for (;x<=n;x+=x&-x) tree[x]+=y;
	}
	int query(int x){
		int res=0;
		for (;x;x-=x&-x) res+=tree[x];
		return res;
	}
} using namespace BIT;

struct List{//表头为权值，后面接着点的编号
	int pre[MAXM],nxt[MAXM];
	void del(int x){
		if (nxt[x]) pre[nxt[x]]=pre[x];
		if (pre[x]) nxt[pre[x]]=nxt[x];
		pre[x]=x; nxt[x]=x;
	}
	void ins(int v,int x){//在权值v后插入点x
		v+=n+1;
		nxt[x]=nxt[v];
		if (nxt[v]) pre[nxt[v]]=x;
		nxt[v]=x; pre[x]=v;
	}
	int get(int v){ return nxt[v+n+1];}
} Up,Dw;
int up[MAXN],dw[MAXN],up_w[MAXN],dw_w[MAXN];
void update(int x){//更新每条链的分界点的值，存入Up,Dw
	Up.del(x);
	if (up[x]>=1) Up.ins(up_w[x],x);
	Dw.del(x);
	if (dw[x]<=tot[x]) Dw.ins(dw_w[x],x);
}
/*
	up[x]为链上最深度最大的A中的点的深度，up_w[x]为其w值
	dw[x]为链上最深度最小的B中的点的深度，dw_w[x]为其w值
	>lim的点放入A中，<=lim的点放入B中
*/
void update_w(int x,int d,int w){//更新分界点的w值
	if (1<=up[x]&&up[x]<=d) up_w[x]+=w;
	if (dw[x]<=d) dw_w[x]+=w;
}
int get_w(int x){ return query(R[x])-query(L[x]-1);}//获得一个在S中的点的w值
set<int> s[MAXN];
set<int>::iterator it;
int pred(int x,int y){
	it=s[x].lower_bound(y);
	if (it==s[x].begin()) return 0;
	else return *--it;
}
int succ(int x,int y){
	it=s[x].upper_bound(y);
	if (it==s[x].end()) return 0;
	else return *it;
}
void delA(int x){//将链上的深度最大的A从A中删除
	up[x]=pred(x,up[x]);
	up_w[x]=!up[x]?0:get_w(num[L[x]+up[x]-1]);
}
void delB(int x){//将链上的深度最大的B从B中删除
	dw[x]=succ(x,dw[x]);
	dw_w[x]=dw[x]>tot[x]?0:get_w(num[L[x]+dw[x]-1]);
}
void AtoB(int x){//将链上的深度最大的A移到B中
	dw[x]=up[x]; dw_w[x]=up_w[x];
	delA(x);
}
void BtoA(int x){//将链上的深度最小的B移到A中
	up[x]=dw[x]; up_w[x]=dw_w[x];
	delB(x);
}
int cnt,lim;
void ins(int x){
	add(L[x],1);
	int t=top[x],d=L[x]-L[t]+1;//d为以t为根时x的深度（t深度为1）
	s[t].insert(d);
	update_w(t,d,1);//更新链上分界点的w（分界点在t--x的链上）
	if (dw_w[t]>lim){ cnt++; BtoA(t);}//直接上移，因为最多分界点只会移动一步
	else
		if (dw[t]>d){//现在已知dw[t]满足条件且在x之下，看分界点是否能移动
			int s=get_w(x);
			if (s<=lim){ dw[t]=d; dw_w[t]=s;}//原先t--fa[x]链上所有点都在A中，son[x]--*所有点都在B中，且当前点可以加入B
			else {
				cnt++;
				if (d>up[t]){ up[t]=d; up_w[t]=s;}//原先t--fa[x]链上所有点都在A中，son[x]--*所有点都在B中，且当前点可以加入A
			}
		}
	update(t);
	for (int x=fa[t],t=top[x];x;x=fa[t],t=top[x]){
		d=L[x]-L[t]+1;
		update_w(t,d,1);//更新链上分界点的w
		if (dw_w[t]>lim){ cnt++; BtoA(t);}//分界点上移
		update(t);
	}
	//前面的操作会导致cnt增大
	while (cnt>lim){
		int x=Up.get(lim);
		if (!x){ lim++; continue;}//没有权值为lim的A中的点
		cnt--; AtoB(x); update(x);
	}
	//做完后cnt==lim
}
void del(int x){
	add(L[x],-1);
	int t=top[x],d=L[x]-L[t]+1;//d为以t为根时x的深度（t深度为1）
	s[t].erase(d);
	update_w(t,d,-1);//更新链上分界点的w（分界点在t--x的链上）
	if (d<=up[t]) cnt--;//从A中删除，因为x已经不在S中了
	if (d==up[t]) delA(t);//若x为A中深度最大的点，删去后要重新求深度最大的点
	else if (d==dw[t]) delB(t);//若x为B中深度最大的点，删去后要重新求深度最大的点
	if (up[t]>=1&&up_w[t]<=lim){ cnt--; AtoB(t);}//x到根路径所有w--，可能导致分界点下移
	update(t);
	for (int x=fa[t],t=top[x];x;x=fa[t],t=top[x]){
		d=L[x]-L[t]+1;
		update_w(t,d,-1);//更新链上分界点的w
		if (up[t]>=1&&up_w[t]<=lim){ cnt--; AtoB(t);}//分界点下移
		update(t);
	}
	//前面的操作会导致cnt减小
	while (cnt<lim){
		int x=Dw.get(lim);
		if (!x){ lim--; continue;}//没有权值为lim的A中的点
		cnt++; BtoA(x); update(x);
	}
}
int main(){
//	File("tree");
	n=read();
	for (int i=1;i<=(n<<1|1);i++){
		Up.pre[i]=0; Up.nxt[i]=0;
		Dw.pre[i]=0; Dw.nxt[i]=0;
	}
	int t,u,v;
	for (int i=1;i<n;i++){
		u=read(); v=read();
		addedge(u,v); addedge(v,u);
	}
	dfs(1,0); dfs2(1,1);
	for (int i=1;i<=n;i++)
		if (top[i]==i){
			dw[i]=tot[i]+1;//B中深度最小的点是i往下dw[i]深度的点
			s[i].insert(0); s[i].insert(tot[i]+1);
		}
	q=read(); 
	while (q--){
		t=read(); v=read();
		if (t==1) ins(v);
		else del(v);
		write(cnt); pc('\n'); 
	}
	IOflush();
	return 0;
}
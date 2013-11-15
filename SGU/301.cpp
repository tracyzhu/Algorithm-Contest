#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <queue>
using namespace std;

typedef long long LL;
const int N = 3000 + 5;
int n,x,y;
int dis[2][N],Idx[N];
int inq[N];
struct Edge{
	int p,l,next;
}e[500000 + 5];
int head[N],eidx = 0;
int ans[N];
vector<pair<int,int> >E;
queue<int>Q;
void spfa(int s,int f) {
	 memset(inq,0,sizeof(inq));
	 memset(dis[f],-1,sizeof(dis[f]));
	 dis[f][s] = 0;
	 inq[s] = 1;
	 while(Q.empty() != true) Q.pop();
	 Q.push(s);
	 while(Q.empty() != true) {
	 	int cur = Q.front();
	 	Q.pop();
	 	inq[cur] = 0;
	 	for(int i = head[cur];i != -1;i = e[i].next) {
			 int p = e[i].p,l = e[i].l;
			 if(dis[f][p] == -1 || dis[f][cur] + l < dis[f][p]) {
			 	dis[f][p] = dis[f][cur] + l;
			 	if(inq[p] == 0) {
				 	inq[p] = 1;
				 	Q.push(p);
				 }
			 }
	 	}
	 }
	 return;
}
void addedge(int a,int b,int c) {
	 e[eidx].p = b;e[eidx].l = c;e[eidx].next = head[a];head[a] = eidx;eidx++;
	 e[eidx].p = a;e[eidx].l = c;e[eidx].next = head[b];head[b] = eidx;eidx++;
	 return;
}
void Init(){
	 memset(head,-1,sizeof(head));
	 scanf("%d %d %d",&n,&x,&y);
	 int m;
	 scanf("%d",&m);
	 for(int i = 0;i < m;i++) {
	 	int a,b,c;
	 	scanf("%d %d %d",&a,&b,&c);
	 	addedge(a,b,c);
	 }
}
int sum[N],cnt[N];
int main(){
	#ifndef ONLINE_JUDGE
		freopen("1.in","r",stdin);
	#endif
	Init();
	spfa(x,0);
	spfa(y,1);
	for(int i = 1;i <= n;i++) {
		//printf("i:%d %lld %lld\n",i,dis[0][i],dis[1][i]);
		if(dis[0][i] == -1 || dis[1][i] == -1) continue;
		if(dis[0][i] + dis[1][i] > dis[0][y]) continue;
		E.push_back(make_pair(dis[0][i],i));
		//printf("%d:%lld\n",i,dis[0][i]);
	}
	sort(E.begin(),E.end());
	int idx = 0;
	memset(Idx,-1,sizeof(Idx));
	Idx[E[0].second] = idx;
	cnt[0] = 1;
	for(int i = 1;i < E.size();i++) {
		if(E[i].first != E[i-1].first) {
			idx++;
			Idx[E[i].second] = idx;
			cnt[idx]++;
		} else {
			Idx[E[i].second] = idx;
			cnt[idx]++;
		}
	}
	for(int i = 1;i <= n;i++) {
		for(int j = head[i];j != -1;j = e[j].next) {
			if(dis[0][i] + e[j].l == dis[0][e[j].p]){
				//printf("%d-%d %d\n",i,e[j].p,e[j].l);
				int L = Idx[i],R = Idx[e[j].p];
				L++;R--;
				if(L<=R){
					sum[L]++;
					sum[R+1]--;
				}
			}
		}
	}	
	for(int i = 1;i <= idx;i++) {
		sum[i]+=sum[i-1];
	}
	for(int i = 1;i <= n;i++) {
		if(Idx[i] != -1) {
			ans[i] += sum[Idx[i]] + cnt[Idx[i]];
		}
	}
	for(int i = 1;i < n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
}
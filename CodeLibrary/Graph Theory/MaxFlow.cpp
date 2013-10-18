#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>
using namespace std;
const int N = 6000+5;
const int M = 100000+5;
const int inf = 200000000;
class Graph{
    public:
        struct Edge{
            int v,next;
            int cap;
        }e[M];
        int pre[N],head[N],dis[N],gap[N],cur[N],n,ec;
        int s,t;
        Graph(int _n,int _s,int _t):n(_n),s(_s),t(_t){
            ec = 0;memset(head,-1,sizeof(head));
        }
        Graph(){}
        void Add(int u,int v,int c,int cc = 0){
            //printf("%d %d %d\n",u,v,c);
           e[ec].v=v;e[ec].cap=c;e[ec].next=head[u];head[u]=ec++;
           e[ec].v=u;e[ec].cap=cc;e[ec].next=head[v];head[v]=ec++;
        }
        int Sap(){
            int i,x=pre[s]=s,v;int aug=inf,ans = 0;
            for(i = 1;i<=n;i++) cur[i]=head[i];
            memset(dis,0,sizeof(dis)); gap[0]=n;
            while(dis[s] < n){
                for(i = cur[x];i!=-1;i = e[i].next)
                    if(e[i].cap>0 && dis[e[i].v]+1==dis[x])
                    break;
                if(i!=-1){
                    cur[x]=i;pre[e[i].v]=x;
                    aug = min(aug,e[i].cap);
                    if((x=e[i].v)==t){
                        ans+=aug;
                        for(x = pre[x],v=e[i].v;v!=s;v = x,x = pre[x]){
                        e[cur[x]].cap-= aug;
                        e[cur[x] ^ 1].cap+= aug;
                        }
                        aug=inf;
                    }
                }else{                //Gap Optimization
                    if(--gap[dis[x]]==0)break;
                    dis[x]=n;
                    for(i= cur[x] = head[x];i!=-1;i = e[i].next) 
                        if( e[i].cap>0 && dis[x]>dis[e[i].v]+1 ) cur[x] = i,dis[x]=dis[e[i].v]+1;
                    ++gap[dis[x]];
                    x=pre[x];
                }
            }
            return ans;    
       }
       void init(int _n,int _s,int _t){
           n = _n;s = _s;t = _t;ec = 0;
           memset(head,-1,sizeof(head));
       }
};

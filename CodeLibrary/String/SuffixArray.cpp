#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
const int N = 100000+5;
#define move(i) (1<<(i))
class SA{
	int str[N],Sa[N],Rank[N],Sec[N],tmps[N],tmpv[N];
	int Height[N],h[N];
	int n;
	int dp[N][20+5];
	int Log[N+5];
	int cmp(int *R,int a,int b,int l){
		return R[a] == R[b] && R[a+l] == R[b+l];
	}
	void SuffixArray(int n,int m){ 
		// n = string length + 1
	 	int i,j,p;
	 	int *x = Rank,*y = Sec,*t;
	 	memset(tmps,0,sizeof(tmps));
 		for(i = 0;i < n;i++)
	 		tmps[x[i] = str[i]]++;
	 	for(i = 1;i < m;i++)
	 		tmps[i] += tmps[i-1];	
	 	for(i = n-1;i >= 0;i--)
	 		Sa[--tmps[x[i]]] = i;	
	 	for(j = 1,p = 1;p < n;j *= 2,m = p){
		 //p is the number of substrings
	 		 for(p = 0,i = n-j;i < n;i++)
	 	 		y[p++] = i;
 	 		for(i = 0;i < n;i++)
		  		if(Sa[i] >= j) y[p++] = Sa[i]-j;
 			for(i = 0;i < n;i++)
		 		tmpv[i] = x[y[i]];
 			for(i = 0;i < m;i++)
		 		tmps[i] = 0;
 			for(i = 0;i < n;i++)
		 		tmps[tmpv[i]]++;
			for(i = 1;i < m;i++)
		 		tmps[i] += tmps[i-1];
	 		for(i = n-1;i >= 0;i--)
		 		Sa[--tmps[tmpv[i]]] = y[i];
	 		for(t=x,x=y,y=t,p = 1,x[Sa[0]] = 0,i = 1;i < n;i++)
		 		x[Sa[i]] = cmp(y,Sa[i-1],Sa[i],j)?p-1:p++;	  	 	 	 	 		 			  	
	 	}	 
	 	return; 		 		 	
	}
	void GetHeight(int n){ // n = string length
		int i,j,k = 0;
		for(i = 1;i <= n;i++) Rank[Sa[i]] = i;
		for(i = 0;i < n;Height[Rank[i++]] = k){
			for(k?k--:0,j = Sa[Rank[i]-1];str[i+k] == str[j+k];k++);
		}
		return;
	}
	void st(){
		for(int i = 1;i <= n;i++)
			dp[i][0] = Height[i];
		for(int i = 1;move(i) <= n;i++){
			for(int j = 1;j <= n;j++){
				if(j+move(i)-1 <= n)
					dp[j][i] = min(dp[j][i-1],dp[j+move(i-1)][i-1]);
			}
		}
		return;	
	}
	void init(){
		for(int i = 1;i <= 100000;i++)
			Log[i] = (int)(log((double)i)/log(2.0));
		return;	
	}	
	int Lcp(int x,int y){
		if(x == y) return n-Sa[x];
		x++;
		int k = Log[y-x+1];
		return min(dp[x][k],dp[y-move(k)+1][k]);	
	}
};
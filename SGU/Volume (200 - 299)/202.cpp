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

//#define DEBUG_MODE

#ifdef DEBUG_MODE
	#define DEG printf
#else
	#define DEG //
#endif

unsigned long long dp[70][70];
int go[70][70];
unsigned long long pow2[65];
int tower[70][70],idx[70];
int all;
void Init(int n){
	 dp[3][0] = 0;
	 for(int i = 1;i <= n;i++) {
	 	dp[3][i] = dp[3][i-1] + dp[3][i-1] + 1;
	 	go[3][i] = i-1;
	 }
	 return;
}
void Move(int m,int n,int src,int dest) {
	 if(n == 1) {
	 	if(idx[dest] == 0) {
		 	printf("move %d from %d to %d\n",tower[src][idx[src]-1],src,dest);
		 }else{
		 	printf("move %d from %d to %d atop %d\n",tower[src][idx[src]-1],src,dest,tower[dest][idx[dest]-1]);
		 }
		 tower[dest][idx[dest]] = tower[src][idx[src]-1];
		 idx[src]--;
		 idx[dest]++;
	 	 return;
	 } 
  	 int bottom = tower[src][idx[src]-go[m][n]];
  	 int mid = -1;
  	 for(int i = 1;i <= all;i++) {
		 if(i != src && i != dest && (idx[i] == 0 || bottom < tower[i][idx[i]-1])) {
		 		mid = i;
		 		break;
		 }		 	  	
  	 }
  	 Move(m,go[m][n],src,mid);
  	 Move(m-1,n-go[m][n],src,dest);
  	 Move(m,go[m][n],mid,dest);
  	 return;
}
int main(){
	#ifndef ONLINE_JUDGE
		freopen("1.in","r",stdin);
	#endif
	int n,m;
	scanf("%d %d",&n,&m);
	all = m;
	Init(n);
	for(int i = 4;i <= m;i++) {
		dp[i][0] = 0;dp[i][1] = 1;
		for(int j = 2;j <= n;j++) {
			for(int k = 1;k < j;k++) {
				if(k == 1) {
					dp[i][j] = dp[i][k] * 2 + dp[i-1][j-k];
					go[i][j] = k;
				}else {
					if(dp[i][k] * 2 + dp[i-1][j-k] < dp[i][j]) {
						dp[i][j] = dp[i][k] * 2 + dp[i-1][j-k];
						go[i][j] = k;
					}
 				}
			}
		}
	}
	printf("%d\n",dp[m][n]);
	for(int i = 0;i < n;i++) tower[1][i] = n-i;
	idx[1] = n;
	Move(m,n,1,m);
	return 0;
}
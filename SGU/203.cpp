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

int main(){
	#ifndef ONLINE_JUDGE
		freopen("1.in","r",stdin);
	#endif
	int n;
	LL ans = 0;
	scanf("%d",&n);
	for(int i = 0;i < n;i++) {
		scanf("%d",&p[i]);	
		Q.push(-p[i]);
	}
	while(Q.empty() != true) {
		LL L,R;
		L = Q.top();
		Q.pop();
		if(Q.empty() == true) break;
		R = Q.top();
		Q.pop();
		ans -= L + R;
		//printf("%lld %lld %lld\n",L,R,ans);
		
		Q.push(L+R);
	}
	printf("%lld\n",ans);
	return 0;
}
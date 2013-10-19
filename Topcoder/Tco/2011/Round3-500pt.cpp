// BEGIN CUT HERE  
  
// END CUT HERE  
#line 5 "PrefixFreeSuperset.cpp"  
#include <vector>  
#include <list>  
#include <map>  
#include <set>  
#include <deque>  
#include <stack>  
#include <bitset>  
#include <algorithm>  
#include <functional>  
#include <numeric>  
#include <utility>  
#include <sstream>  
#include <iostream>  
#include <iomanip>  
#include <cstdio>  
#include <cmath>  
#include <cstdlib>  
#include <ctime>  
#include <cstring>  
using namespace std;
typedef long long LL;
bool isprefix(string a,string b) {
	 if(a.length() > b.length()) return false;
	 for(int i = 0;i < a.length();i++) {
	 	if(a[i] != b[i]) return false;
	 }
	 return true;
}  
vector<string>prefix;
void getgood(string s,vector<string> &cur) {
	 int f = false; 
 	 for(int i = 0;i < cur.size();i++) {
 		 if(cur[i] == s) return;
 		 if(isprefix(s,cur[i]) || isprefix(cur[i],s)) 
		  	f = true;
	 }
	 if(f == true) {
	 	 getgood(s+"0",cur);
	 	 getgood(s+"1",cur);
	 } else {
	 	prefix.push_back(s);
	 }
	 return;
}
LL x[100 + 5];
class PrefixFreeSuperset  
{  
public:  
long long minSumLength(vector <string> cur, long long k)  
{  
	 prefix.clear();
	 memset(x,0,sizeof(x));
	 LL limit = 1e18;
     getgood("0",cur);
	 getgood("1",cur);
     for(int i = 0;i < prefix.size();i++) {
	 	 x[prefix[i].length()] ++;
	 }
	 LL ans = 0;
	 for(int i = 0;i < cur.size();i++) 
	 	ans += cur[i].length();
 	 k-=cur.size();
 	 //
	 for(int i = 1;i < 100;i++) {
	 	LL a = x[i],b = x[i+1];
		if(a >= k) {  
			ans += k * i;
			return ans;			
		}else if(k < a + b){
			ans += a * (LL)i;
			ans += (k - a) * (LL)(i+1);
			return ans; 
		}else if(a * 2 + b >= k){
			LL d = k - a - b;
			ans += (a - d) * (LL)i + (b + 2 * d) * (LL)(i + 1);
			return ans;                                                                                                                                                                                                  
		}else {
			x[i+1] += x[i] * 2;
			x[i] = 0;
		}
	 }
	 return -1;
}  

};  
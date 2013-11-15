import java.util.*;
import java.math.*;
import java.io.*;

class Task {
	private int [][]x = new int[1000+5][30];
	private int [][]go = new int[1000+5][30];
	private int [][]beg = new int[1000+5][30];
	String s;
	private BigInteger [][]dp = new BigInteger[65][1000+5];
	private int [][]st = new int[1000+5][30];
	private int []end = new int[1000+5];
	int n,m,l;
	public int dfs(int i,int j) {
		if(st[i][j] == 2) return go[i][j];
		if(st[i][j] == 1) {
			go[i][j] = 0;
		}else{
			st[i][j] = 1;
			if(x[i][j] == 0) {
				go[i][j] = beg[i][j];
			}else{
				go[i][j] = dfs(beg[i][j],j);
			}
		}
		st[i][j] = 2;
		return go[i][j];
	}
	public void solve(){
		Scanner in = new Scanner(System.in);
		s = in.next();
		m = s.length();
		n = in.nextInt();
		int start = in.nextInt();
		l = in.nextInt();
		for(int i = 1;i <= n;i++) end[i] = 0;
		for(int i = 0;i < l;i++) {
			int tmp;
			tmp = in.nextInt();
			end[tmp] = 1;
		}
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++){
				beg[i][j] = in.nextInt();
			}
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {
				x[i][j] = in.nextInt();
			}
		}
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {
				dfs(i,j);
			}
		}
		int Len = in.nextInt();
		in.close();
		for(int i = 0;i <= Len;i++)
			for(int j = 0;j <= n;j++)
				dp[i][j] = BigInteger.ZERO;
		dp[0][start] = BigInteger.ONE;
		for(int i = 0;i < Len;i++) {
			for(int j = 1;j <= n;j++) {
				if(dp[i][j].equals(BigInteger.ZERO) == false){
					for(int k = 1;k <= m;k++) {
						dp[i+1][go[j][k]] = dp[i+1][go[j][k]].add(dp[i][j]);
					}
				}
			}
		}
		BigInteger ans = BigInteger.ZERO;
		for(int i = 1;i <= n;i++) {
			if(end[i] == 1) {
				ans = ans.add(dp[Len][i]);
			}
		}
		System.out.println(ans);
	}
}
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Task SGU201 = new Task();
		SGU201.solve();
	}

}

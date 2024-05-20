import java.util.*;
public class oncallteam_xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();
    int[][] can = new int[m][n];
    int[] szs = new int[m];
    for(int i = 0; i < n; i++) {
      String s = sc.next();
      for(int j = 0; j < m; j++) {
        if(s.charAt(j) == '1') can[j][szs[j]++] = i;
      }
    }
    int[] dp = new int[n];
    Arrays.fill(dp, -1);
    int ret = m;
    for(int mask = 1; mask < (1<<m); mask++) {
      int cand = Integer.bitCount(mask);
      if(cand > ret) continue;
      int amt = 0;
      for(int i = 0; i < m && amt < cand; i++) {
        if((mask&(1<<i)) == 0) continue;
        for(int j = 0; j < szs[i] && amt < cand; j++) {
          int curr = can[i][j];
          if(dp[curr] != mask) {
            amt++;
            dp[curr] = mask;
          }
        }
      }
      if(amt < cand) ret = Math.min(ret, amt);
    }
    System.out.println(ret);
  }
}
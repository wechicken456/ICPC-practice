import java.util.*;
public class eccentricexcursion_xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int k = sc.nextInt(); k = n-1-k;
    cands = new ArrayList<>();
    for(int i = 0; i < n; i++) cands.add(i);
    postorder = new ArrayList<>();
    graph = new boolean[n][n];
    edges = new Set[n];
    used = new boolean[n];
    for(int i = 0; i < n; i++) {
      edges[i] = new HashSet<>();
    }
    for(int i = 1; i < n; i++) {
      int a = sc.nextInt()-1;
      int b = sc.nextInt()-1;
      graph[a][b] = true;
      graph[b][a] = true;
      edges[a].add(b);
      edges[b].add(a);
    }
    dfs(0, -1);
    int[] poss = analyze(-1);
    if(k < poss[0] || k > poss[1]) stop();
    ArrayList<Integer> ret = new ArrayList<>();
    int lhs = -1;
    for(int qq = 0; qq < n; qq++) {
      boolean found = false;
      for(int i = 0; !found && i < n; i++) {
        if(!cands.contains(i)) continue;
        poss = analyze(i);
        int nk = k;
        if(edges[i].contains(lhs)) nk--;
        if(poss[0] <= nk && nk <= poss[1]) {
          ret.add(i);
          lhs = i;
          k = nk;
          found = true;
          break;
        }
      }
      if(!found) throw new RuntimeException();
      cands.remove(Integer.valueOf(lhs));
      postorder.remove(Integer.valueOf(lhs));
      used[lhs] = true;
    }
    for(int i = 0; i < n; i++) {
      if(i > 0) System.out.print(' ');
      System.out.print(ret.get(i)+1);
    }
    System.out.println();
  }
  public static void stop() {
    System.out.println(-1);
    System.exit(0);
  }
  public static void dfs(int curr, int par) {
    for(int out: edges[curr]) {
      if(out == par) continue;
      dfs(out, curr);
    }
    postorder.add(curr);
  }
  public static int[] analyze(int root) {
    if(cands.size()==0) throw new RuntimeException();
    if(cands.size()==1) return new int[]{0, 0};
    if(cands.size()==2) {
      int a = cands.get(0);
      int b = cands.get(1);
      if(graph[a][b]) return new int[]{1, 1};
      return new int[]{0, 0};
    }
    int lhs = 0;
    // is answer >= 1 ?
    {
      int canskip = root >= 0 ? 1 : 0;
      // non-root check
      for(int i = 0; i < cands.size(); i++) {
        if(cands.get(i) == root) continue;
        int skipped = 0;
        for(int j = 0; skipped <= canskip && j < cands.size(); j++) {
          if(i == j) continue;
          if(cands.get(j) == root) skipped++;
          else if(!graph[cands.get(i)][cands.get(j)]) skipped++;
        }
        if(skipped <= canskip) {
          lhs = 1;
          break;
        }
      }
      // root check
      if(lhs == 0 && root >= 0) {
        boolean skipped = false;
        for(int j: cands) {
          if(j == root) continue;
          if(!graph[root][j]) {
            skipped = true;
            break;
          }
        }
        if(!skipped) {
          lhs = 1;
        }
      }
    }
    int rhs = 0;
    Set<Integer> unmatched = new HashSet<>();
    for(int curr: postorder) {
      int can = 2;
      if(curr == root) can--;
      for(int out: edges[curr]) {
        if(!used[out] && unmatched.remove(out)) {
          rhs++;
          if(--can == 0) break;
        }
      }
      if(can > 0) {
        unmatched.add(curr);
      }
    }
    return new int[]{lhs, rhs};
  }
  static boolean[] used;
  static ArrayList<Integer> cands, postorder;
  static int numNodes;
  static boolean[][] graph;
  static Set<Integer>[] edges;
}
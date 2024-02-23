import java.util.*;
import java.util.regex.*;
import java.io.*;

public class RSRBadSplitDecisions {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    int n = Integer.parseInt(in.readLine());
    String w[] = new String[n];
    for (int i = 0; i < n; i++) {
      w[i] = in.readLine();
    }

    // Sort strings by length:
    Arrays.sort(w,Comparator.comparing(s->s.length()));

    // Note where each length group begins and ends):
    ArrayList<Integer> breakpt = new ArrayList<Integer>();
    int l = w[0].length();
    breakpt.add(0);
    for (int i = 1; i < n; i++) { 
      if (w[i].length() > l) {
        breakpt.add(i);
        l = w[i].length();
      }
    }
    breakpt.add(n);

    int count = 0;
    HashSet<String> hs = new HashSet<String>();
    HashSet<String> bad = new HashSet<String>();
    

    for (int i = 0; i < breakpt.size()-1; i++) {
      int bp1 = breakpt.get(i);
      int bp2 = breakpt.get(i+1);

      for (int start = 0; start < w[bp1].length()-1; start++) {
        // for each location of the two-element difference, start a new set
        hs.clear();
        bad.clear();
        for (int j = bp1; j < bp2-1; j++) {
          Pattern p = Pattern.compile(w[j].substring(0,start)+".."+w[j].substring(start+2));
          for (int k = j+1; k < bp2; k++) {
            Matcher m = p.matcher(w[k]);
            boolean found = m.find();

/** ERROR: should NOT check for pairs of identical characters; omit last
    two conditions
**/
            if (found && w[j].charAt(start) != w[k].charAt(start) && w[j].charAt(start+1) != w[k].charAt(start+1) && w[j].charAt(start) != w[j].charAt(start+1) && w[k].charAt(start) != w[k].charAt(start+1)) {
              String p1 = w[j].substring(start,start+2);
              String p2 = w[k].substring(start,start+2);
              if (p1.compareTo(p2) > 0) {String temp = p1; p1 = p2; p2 = temp;}
              String f = ""+start+p1+p2;
              if (!hs.contains(f)) {
                hs.add(f);
              }
              else {
		bad.add(f);
              }
            }
          }
        }
        count += (hs.size() - bad.size());
      }
    }
    System.out.println(count);
  }
}

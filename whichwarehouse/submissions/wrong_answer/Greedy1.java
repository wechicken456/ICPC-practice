import java.io.*;
import java.util.*;

/**
 * This Wrong Answer submission uses a greedy approach to decide which product
 * to send to which warehouse.
 *
 * Choose the remaining (product, warehouse) pair that minimises the cost to send
 * all of a remaining product to a remaining warehouse.
 *
 * @author Finn Lidbetter
 */

public class Greedy1 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] s = br.readLine().split(" ");
        int w = Integer.parseInt(s[0]);
        int p = Integer.parseInt(s[1]);
        long[][] products = new long[w][p];
        for (int i=0; i<w; i++) {
            s = br.readLine().split(" ");
            for (int j=0; j<p; j++) {
                products[i][j] = Integer.parseInt(s[j]);
            }
        }
        double[][] adj = new double[w][w];
        for (int i=0; i<w; i++) {
            s = br.readLine().split(" ");
            for (int j=0; j<w; j++) {
                int dist = Integer.parseInt(s[j]);
                if (dist == -1) {
                    adj[i][j] = Double.POSITIVE_INFINITY;
                } else {
                    adj[i][j] = dist;
                }
            }
        }
        for (int k=0; k<w; k++) {
            for (int i=0; i<w; i++) {
                for (int j=0; j<w; j++) {
                    double sum = adj[i][k] + adj[k][j];
                    if (sum < adj[i][j]) {
                        adj[i][j] = sum;
                    }
                }
            }
        }
        long[][] apsp = new long[w][w];
        for (int i=0; i<w; i++) {
            for (int j=0; j<w; j++) {
                apsp[i][j] = (long) adj[i][j];
            }
        }
        // movingCost[i][j] is the cost to move all of product i to warehouse j.
        long[][] movingCost = new long[p][w];
        for (int prod=0; prod<p; prod++) {
            for (int i=0; i<w; i++) {
                for (int j=0; j<w; j++) {
                    movingCost[prod][i] += apsp[j][i] * products[j][prod];
                }
            }
        }
        long total = 0;
        ArrayList<TreeSet<WarehouseCost>> sortedCosts = new ArrayList<>();
        for (int i=0; i<p; i++) {
            TreeSet<WarehouseCost> costs = new TreeSet<>();
            for (int j=0; j<w; j++) {
                costs.add(new WarehouseCost(j, movingCost[i][j]));
            }
            sortedCosts.add(costs);
        }
        int numChosen = 0;
        boolean[] chosen = new boolean[p];
        while (numChosen<p) {
            int bestProduct = -1;
            WarehouseCost best = null;
            for (int i=0; i<p; i++) {
                if (!chosen[i]) {
                    WarehouseCost currBest = sortedCosts.get(i).first();
                    if (best == null || currBest.cost < best.cost) {
                        bestProduct = i;
                        best = currBest;
                    }
                }
            }
            total += best.cost;
            chosen[bestProduct] = true;
            for (int i=0; i<p; i++) {
                WarehouseCost toRemove = null;
                for (WarehouseCost wc: sortedCosts.get(i)) {
                    if (wc.warehouseNumber == best.warehouseNumber) {
                        toRemove = wc;
                        break;
                    }
                }
                sortedCosts.get(i).remove(toRemove);
            }
            numChosen++;
        }
        System.out.println(total);
    }
}
class WarehouseCost implements Comparable<WarehouseCost> {
    int warehouseNumber;
    long cost;
    public WarehouseCost(int id, long c) {
        warehouseNumber = id;
        cost = c;
    }
    public int compareTo(WarehouseCost w2) {
        if (cost == w2.cost) {
            return warehouseNumber - w2.warehouseNumber;
        }
        return Long.compare(cost, w2.cost);
    }
}

import java.io.*;
import java.util.*;

/**
 * Use a min-cost max flow algorithm.
 * First, use the Floyd-Warshall algorithm to get all pairs shortest paths between
 * the warehouse locations. 
 * Then, compute the cost to move all of each product i to each warehouse j.
 * Then, set up a bipartite graph with vertices corresponding to the products in one 
 * partite set and vertices corrsponding to the warehouses in the other. Give capacity 
 * 1 (and 0 cost) to edges between a source vertex and the product vertices and 
 * capacity 1 (and 0 cost) to edges between warehouse vertices and the sink vertex.
 * Add a capacity 1 edge from each product i to each warehouse j with a cost equal to
 * the cost to move all of product i to warehouse j.
 * Run a min-cost max-flow algorithm on the resulting graph.
 *
 * @author Finn Lidbetter
 */

public class WhichWarehouse_Finn {
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
        // The first p indices correspond to nodes for the products.
        // The next w indices correspond to nodes for the warehouses.
        // Index p+w is the source.
        // Index p+w+1 is the sink.
        long[][] capacities = new long[p+w+2][p+w+2];
        long[][] graphCosts = new long[p+w+2][p+w+2];
        // One capacity for each product to go to one warehouse.
        for (int i=0; i<p; i++) {
            capacities[p+w][i] = 1;
            graphCosts[p+w][i] = 0;
        }
        // Each warehouse can be used by at most one product.
        for (int i=0; i<w; i++) {
            capacities[p+i][p+w+1] = 1;
            graphCosts[p+i][p+w+1] = 0;
        }
        // Set the cost for sending product i to warehouse j.
        for (int i=0; i<p; i++) {
            for (int j=0; j<w; j++) {
                capacities[i][p+j] = 1;
                graphCosts[i][p+j] = movingCost[i][j];
            }
        }
        long[] flowCost = MinCostFlow.getFlowCost(capacities, graphCosts, p+w, p+w+1);
        if (flowCost[0] != p) {
            throw new NullPointerException();
        }
        System.out.println(flowCost[1]);

    }
}
class MinCostFlow {
    static final long INF = Long.MAX_VALUE / 2 - 1;
    static boolean found[];
    static int N, dad[];
    static long flow[][], dist[], pi[];
    static long[] getFlowCost(long cap[][], long cost[][], int s, int t) {
        N = cap.length; 
        found = new boolean[N]; 
        dad = new int[N];
        flow = new long[N][N]; 
        dist = new long[N + 1]; 
        pi = new long[N];
        long totflow = 0, totcost = 0;
        while (search(cap, cost, s, t)) {
            long amt = INF;
            for (int x = t; x != s; x = dad[x]) {
                amt = Math.min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]);
            }
            for (int x = t; x != s; x = dad[x]) {
                if (flow[x][dad[x]] != 0) {
                    flow[x][dad[x]] -= amt;
                    totcost -= amt * cost[x][dad[x]];
                } else {
                    flow[dad[x]][x] += amt;
                    totcost += amt * cost[dad[x]][x]; 
                } 
            }
            totflow += amt; 
        }
        return new long[] { totflow, totcost }; 
    }
    static boolean search(long cap[][], long cost[][], int s, int t) {
        Arrays.fill(found, false); Arrays.fill(dist, INF);
        dist[s] = 0;
        while (s != N) {
            int best = N; found[s] = true;
            for (int k = 0; k < N; k++) {
                if (found[k]) {
                    continue;
                }
                if (flow[k][s] != 0) {
                    long val = dist[s] + pi[s] - pi[k] - cost[k][s];
                    if (dist[k] > val) { 
                        dist[k] = val; 
                        dad[k] = s; 
                    } 
                }
                if (flow[s][k] < cap[s][k]) {
                    long val = dist[s] + pi[s] - pi[k] + cost[s][k];
                    if (dist[k] > val) { 
                        dist[k] = val; 
                        dad[k] = s; 
                    } 
                }
                if (dist[k] < dist[best]) {
                    best = k;
                }
            }
            s = best; 
        }
        for (int k = 0; k < N; k++) {
            pi[k] = Math.min(pi[k] + dist[k], INF);
        }
        return found[t]; 
    } 
}


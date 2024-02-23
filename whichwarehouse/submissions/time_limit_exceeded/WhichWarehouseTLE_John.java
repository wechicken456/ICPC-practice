import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class WhichWarehouseTLE_John {


	public static final int MAX_NODES = 100;
	public static final int MAX_WEIGHT = 1000;
	public static final int INFINITY = MAX_NODES*MAX_WEIGHT + 1;
	public static int [][] inventory;
	public static int [][] dist;
	public static int lowestCost = Integer.MAX_VALUE;

	public static void main(String [] args)
	{
		int w, p;
		Scanner in = new Scanner(System.in);

		w = in.nextInt();
		p = in.nextInt();
		inventory = new int[w][p];
		dist = new int[w][w];
		for(int i=0; i<w; i++) {
			for(int j=0; j<p; j++) {
				inventory[i][j] = in.nextInt();
			}
		}
		for(int i=0; i<w; i++) {
			for(int j=0; j<w; j++) {
				int val = in.nextInt();
				dist[i][j] = val == -1 ? INFINITY : val;
			}
		}
		// run Floyd-Warshall algorithm
		for (int k = 0; k < w; k++) {
			for (int i = 0; i < w; i++) {
				for (int j = 0; j < w; j++) {
					if (dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}

		int[] assignments = new int[w];
		for(int i=0; i<assignments.length; i++)
			assignments[i] = -1;
		assignProducts(assignments, 0, p);
		System.out.println(lowestCost);

	}
	
	public static void assignProducts(int [] assignment, int val, int p)
	{
		if (val == p) {
			int cost = 0;
//for(int value : assignment) System.out.print(value + " ");
//System.out.println();
			for(int i=0; i<assignment.length; i++) {
				if (assignment[i] == -1)
					continue;
				int prod = assignment[i];
				for(int j=0; j<assignment.length; j++) {
//System.out.println("  " + i + "," + j + "," + prod);
					cost += inventory[j][prod]*dist[j][i];
				}			
			}
			if (cost < lowestCost)
				lowestCost = cost;
			return;
		}
		else {
			for(int i=0; i<assignment.length; i++) {
				if (assignment[i] == -1) {
					assignment[i] = val;
					assignProducts(assignment, val+1, p);
					assignment[i] = -1;
				}
			}
		}
	}
}


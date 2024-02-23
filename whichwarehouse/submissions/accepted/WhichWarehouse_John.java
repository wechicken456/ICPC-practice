import java.util.*;

public class WhichWarehouse_John
{
	public static final int MAX_NODES = 100;
	public static final int MAX_WEIGHT = 1000;
	public static final int INFINITY = MAX_NODES*MAX_WEIGHT + 1;
	
	public static void main(String [] args)
	{
		int w, p;
		Scanner in = new Scanner(System.in);
		int [][] dist;
		int [][] inventory;

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
/*
		System.out.println("Min distances");
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < w; j++) {
                    System.out.println(i + "--> " + j + ": " + dist[i][j]);
            }
        }
*/
  
								// setup bipartite graph
		BiGraph g = new BiGraph(w, w);
		int [][] table = new int[p][w];				// table[p][w] = cost to move item p to warehouse w
		for(int i=0; i<p; i++) {
			for(int j=w; j<2*w; j++) {
				int val = 0;
				for(int k=0; k<w; k++) {
					val += dist[k][j-w]*inventory[k][i];
				}
				g.addEdge(i, j, val);
				table[i][j-w] = val;
//				System.out.println(i + " --> " + (j-w) + ": " + val+" ");
			}
		}
		for(int i=p; i<w; i++) {
			for(int j=w; j<2*w; j++) {
				g.addEdge(i, j, 0);
//				System.out.println(i + " --> " + j + ": " + val+" ");
			}
		} 

		int [] matching = g.findMinCostMatching();
		int cost = 0;
		for(int i=0; i<p; i++) {
//			System.out.println(i + "->" + (matching[i]-w));
			cost += table[i][matching[i]-w];
		}
		System.out.println(cost);

		
	}
}

class BiGraph
{
	private static final int INF = 100000000;

	private ArrayList<Vertex> vertices = new ArrayList<Vertex>();
	private int n, m;

	public BiGraph(int nn, int mm)
	{
		n=nn; m = mm;
		vertices = new ArrayList<Vertex>();
		for(int i=0; i<n+m; i++)
			vertices.add(new Vertex("", i));
	}

	public void addEdge(int v, int w, int cost)
	{
		vertices.get(v).addEdge(new Edge(v, w, cost));
	}

	public int[] findMinCostMatching()
	{
		Vertex s = new Vertex("s", n+m);
		vertices.add(s);
		Iterator<Vertex> itr = vertices.iterator();
		for(int i=0; i<n; i++)
			s.addEdge(new Edge(n+m, i, 0));
		vertices.add(new Vertex("t", n+m+1));
		for(int i=n; i<n+m; i++)
			vertices.get(i).addEdge(new Edge(i, n+m+1, 0));
		for(int i=0; i<n+m+2; i++) {
			ArrayList<Edge> path = findMinCostPath();
			if (path == null)
				break;
			addPath(path);
		}
		int [] matching = new int[n];
		itr = vertices.iterator();
		for(int i=0; i<n; i++)
			itr.next();
		for(int i=0; i<m; i++) {
			Edge e = itr.next().edges.get(0);
			matching[e.w] = e.v;
		}
		return matching;
	}

	private void addPath(ArrayList<Edge> path)
	{
		for(Iterator<Edge> itr = path.iterator() ; itr.hasNext() ; ) {
			Edge e = itr.next();
			vertices.get(e.v).edges.remove(e);
			vertices.get(e.w).edges.add(new Edge(e.w, e.v, -e.cost));
		}
	}

	private ArrayList<Edge> findMinCostPath()
	{
		int nVert = n + m + 2;
		TableEntry [][] table = new TableEntry[nVert][nVert];
		for(int i=0; i<nVert; i++) {
			table[0][i] = new TableEntry(INF, null);
		}
		table[0][n+m] = new TableEntry(0, null);
		int pass;
		for(pass=1; pass < nVert; pass++) {
			if (vertices.get(n+m).edges.size() == 0)
				break;					// no more edges leaving s
			//System.out.println("Pass = " + pass);
			for(int i=0; i<nVert; i++) {
				//System.out.println("  i = " + i + ", cost = " + table[pass-1][i].cost);
				table[pass][i] = new TableEntry(table[pass-1][i].cost, table[pass-1][i].prev);
			}
			for(int i=0; i<nVert; i++) {
				for(Iterator<Edge> itr = vertices.get(i).edges.iterator(); itr.hasNext(); ) {
					Edge e = itr.next();
					if (table[pass-1][i].cost != INF && table[pass-1][i].cost + e.cost < table[pass][e.w].cost) {
						table[pass][e.w].cost = table[pass-1][i].cost+e.cost;
						table[pass][e.w].prev = e;
					}
				}
			}
		}
		return buildPath(table, pass, n+m+1);
	}

	private ArrayList<Edge> buildPath(TableEntry [][] table, int size, int dest)
	{
		if (table[size-1][dest].prev == null)
			return new ArrayList<Edge>();
		else {
			ArrayList<Edge> ans = buildPath(table, size, table[size-1][dest].prev.v);
			ans.add(table[size-1][dest].prev);
			return ans;
		}
	}

	public static void main(String [] args)
	{
		int size = 5;
		if (args.length > 0)
			size = Integer.parseInt(args[0]);
		Random rnd = new Random();
		for(int ntrials = 1; ntrials <= 1; ntrials++) {
			BiGraph g = new BiGraph(size, size);
			for(int i=0; i<size; i++) {
				for(int j=size; j<2*size; j++) {
					int val = rnd.nextInt(1000);
					g.addEdge(i, j, val);
					System.out.println(i + " --> " + j + ": " + val+" ");
				}
				//				System.out.println();
			}

			int [] matching = g.findMinCostMatching();
			boolean [] matched = new boolean[2*size];
			for(int i=0; i<matching.length; i++) {
				System.out.println(i + "->" + matching[i]);
				if (matching[i] < size || matching[i] >= 2*size)
					System.out.println("ERROR: matching for " + i + " out of bounds");
				else if (matched[matching[i]])
					System.out.println("ERROR: matching for " + i + " already matched");
				else
					matched[matching[i]] = true;
			}
		}
	}
}

class TableEntry
{
	int cost;
	Edge prev;

	public TableEntry(int c, Edge p)
	{
		cost = c;
		prev = p;
	}
}

class Vertex
{
	String name;
	int [] products;					// used to store amount of each product in initial graph
	int num;
	ArrayList<Edge> edges;

	public Vertex(String n, int nm)
	{
		name = n;
		num = nm;
		edges = new ArrayList<Edge>();
	}

	public void addEdge(Edge e)
	{
		edges.add(e);
	}
}

class Edge
{
	int v, w;
	int cost;

	public Edge(int vv, int ww, int c)
	{
		v = vv;
		w = ww;
		cost = c;
	}
}
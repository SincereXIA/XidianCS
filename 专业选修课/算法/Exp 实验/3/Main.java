import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int pointnum = in.nextInt();
        int edgenum = in.nextInt();
        Point[] points = new Point[pointnum];
        for (int i = 0; i < points.length; i++) {
            int idx = in.nextInt();
            points[idx] = new Point(in.nextDouble(), in.nextDouble());
        }
        EdgeWeightedDigraph graph = new EdgeWeightedDigraph(pointnum);
        for (int i = 0; i < edgenum; i++) {
            int v = in.nextInt();
            int w = in.nextInt();
            double d = points[v].distance(points[w]);
            DirectedEdge edge = new DirectedEdge(v, w, d);
            graph.addEdge(edge);
            edge = new DirectedEdge(w, v, d);
            graph.addEdge(edge);
        }

        int from = 0;
        int to = 5;

        DijkstraSP r = new DijkstraSP(graph, from);
        System.out.println(r.hasPathTo(to));
        Stack<DirectedEdge> st = r.pathTo(to);
        double distance = 0;
        while (st.size() > 0) {
            DirectedEdge e = st.pop();
            System.out.println(e.from() + "->" + e.to());
            distance += points[e.from()].distance(points[e.to()]);
        }
        System.out.println(distance);
    }
}

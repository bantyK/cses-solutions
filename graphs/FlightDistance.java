import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class FlightDistance {
    final long INF = (long) 9e17;
    // represent the prices to reach a node when we have used the coupon
    long[] discountedPrice;

    // represent the prices to reach a node when we have not used the coupon
    long[] fullprice;
    Map<Integer, List<Edge>> graph;
    PriorityQueue<Node> pq;
    BufferedReader reader;
    int n, m;
    String[] line;

    public static void main(String[] args) throws IOException {
        new FlightDistance().solve();
    }

    private void solve() throws IOException {
        reader = new BufferedReader(new InputStreamReader(System.in));
        line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        graph = new HashMap<>();
        discountedPrice = new long[n + 1];
        fullprice = new long[n + 1];

        for (int i = 1; i <= n; i++) {
            graph.put(i, new ArrayList<>());
        }

        // input and setup step
        int src, dest;
        long distance;
        for (int i = 0; i < m; i++) {
            line = reader.readLine().split(" ");
            src = Integer.parseInt(line[0]);
            dest = Integer.parseInt(line[1]);
            distance = Long.parseLong(line[2]);
            graph.get(src).add(new Edge(dest, distance));
        }
        Arrays.fill(discountedPrice, INF);
        Arrays.fill(fullprice, INF);

        discountedPrice[1] = 0;
        fullprice[1] = 0;

        pq = new PriorityQueue<>(Comparator.comparingLong(n -> n.cost));

        shortestDistance();

        System.out.println(discountedPrice[n]);
    }

    private void shortestDistance() {
        pq.offer(new Node(0, 1, false));

        while (!pq.isEmpty()) {
            Node curr = pq.poll();

            long cost = curr.cost;
            int vertex = curr.vertex;
            boolean couponAlreadyUsed = curr.couponUsed;

            if (couponAlreadyUsed) {
                // coupon is used, so look into the discounted vector.
                // if the current node's cost is worse than discounted price seen so far,
                // dont consider that entry
                if (discountedPrice[vertex] < cost) {
                    continue;
                }
            } else {
                // same logic as above for full price vector
                if (fullprice[vertex] < cost) {
                    continue;
                }
            }

            for (Edge edge : graph.get(vertex)) {
                if (couponAlreadyUsed) {
                    //coupon is already used. In this case I have only 1 option,
                    if (discountedPrice[edge.dest] > cost + edge.distance) {
                        discountedPrice[edge.dest] = cost + edge.distance;
                        pq.offer(new Node(discountedPrice[edge.dest], edge.dest, true));
                    }
                } else {
                    // coupon is not used
                    // 2 options per edge
                    // 1. go to next point with coupon
                    // 2. go to next point without the coupon, i.e, use the coupon here

                    // going to next with the coupon(don't use the coupon here)
                    if (fullprice[edge.dest] > cost + edge.distance) {
                        fullprice[edge.dest] = cost + edge.distance;
                        pq.offer(new Node(fullprice[edge.dest], edge.dest, false));
                    }

                    // use the coupon here
                    if (discountedPrice[edge.dest] > cost + edge.distance / 2) {
                        discountedPrice[edge.dest] = cost + edge.distance / 2;
                        pq.offer(new Node(discountedPrice[edge.dest], edge.dest, true));
                    }
                }
            }

        }
    }

    private static class Edge {
        int dest;
        long distance;

        public Edge(int dest, long distance) {
            this.dest = dest;
            this.distance = distance;
        }
    }

    private static class Node {
        long cost;
        int vertex;
        boolean couponUsed;

        public Node(long cost, int vertex, boolean couponUsed) {
            this.cost = cost;
            this.vertex = vertex;
            this.couponUsed = couponUsed;
        }
    }
}